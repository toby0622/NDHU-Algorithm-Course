#include <iostream>
using namespace std;

int Case;
int Object;
int Price;
int Weight;
int People;
int MW;
int f[1050];

int main() {
    // input the number of total cases
    cin >> Case;

    // each case round
    while (Case--) {
        // input the number of total objects
        cin >> Object;

        // initialize the array using range base for loop
        for (int & i : f) {
            i = 0;
        }

        // each object
        for (int i = 1; i <= Object; i++) {
            // input the value and weight of the object
            cin >> Price >> Weight;

            // knapsack calculation
            for (int j = 30; j >= 0; j--) {
                if (j >= Weight) {
                    f[j] = max(f[j], f[j - Weight] + Price);
                }
            }
        }

        // final result initialization
        int max_value = 0;

        // input the number of people
        cin >> People;

        // each people
        for (int i = 1; i <= People; ++i) {
            // maximum bag capacity for each person
            cin >> MW;
            // add up the values for each person
            max_value = max_value + f[MW];
        }

        // output the final result
        cout << max_value << endl;
    }

    return 0;
}