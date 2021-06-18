// maximum preference sum using dynamic programming

#include <iostream>
using namespace std;

// find the bigger integer between the two
int Maximum(int a, int b) {
    if (a > b) {
        return a;
    }

    else {
        return b;
    }
}

// find the maximum value of preference that can be accomplished under the budget
int Preference(int budget, int item_price[], int item_preference[], int items) {
    int i;
    int j;
    int K[items + 1][budget + 1];

    for(i = 0; i <= items; i++) {
        for(j = 0; j <= budget; j++) {
            if (i == 0 || j == 0) {
                K[i][j] = 0;
            }

            else if (item_price[i - 1] <= j) {
                K[i][j] = Maximum(item_preference[i - 1] + K[i - 1][j - item_price[i - 1]], K[i - 1][j]);
            }

            else {
                K[i][j] = K[i - 1][j];
            }
        }
    }

    return K[items][budget];
}

int main() {
    // sample item preference list
    int item_preference[] = {80, 28, 70, 55, 43};
    // sample item price list
    int item_price[] = {40, 20, 60, 75, 59};
    // sample budget
    int budget = 150;
    // amount of items
    int items = sizeof (item_preference) / sizeof (item_preference[0]);

    cout << Preference(budget, item_price, item_preference, items);

    return 0;
}