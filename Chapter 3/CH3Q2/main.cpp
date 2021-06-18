#include <iostream>
using namespace std;

// find the larger value
int Maximum(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// find the maximum earnings for the government
// accomplished by the limited shore range
// bottom up method dynamic programming
int Earnings(int length, int section[], int price[], int amount) {
    int i;
    int j;
    int S[amount + 1][length + 1];

    for(i = 0; i <= amount; i++) {
        for(j = 0; j <= length; j++) {
            if (i == 0 || j == 0) {
                S[i][j] = 0;
            }

            else if (section[i - 1] <= j) {
                S[i][j] = Maximum(price[i - 1] +
                        S[i - 1][j - section[i - 1]],
                        S[i - 1][j]);
            }

            else {
                S[i][j] = S[i - 1][j];
            }
        }
    }

    return S[amount][length];
}

int main() {
    // price list for different shore section
    int price[] = {15, 25, 10, 20, 5};
    // partition for different shore section
    int section[] = {27, 22, 19, 15, 31};
    // total length of the shore
    int length = 50;
    // amount of the partitions
    int amount = sizeof (price) / sizeof (price[0]);

    cout << Earnings(length, section, price, amount);

    return 0;
}