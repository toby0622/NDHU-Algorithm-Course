// Traveling Salesman Problem (TSP) Using Dynamic Programming

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 999999;
const int N = 20;

// attributes for each city
class city {
public:
    int cityNumber;
    int xCoordinate;
    int yCoordinate;
};

int main() {
    vector<city> cities(N);

    // input all of the cities data
    for (int i = 0; i < N; i++) {
        cin >> cities[i].cityNumber;
        cin >> cities[i].xCoordinate;
        cin >> cities[i].yCoordinate;
    }

    vector<vector<double>> distance(N, vector<double>(N));

    // calculate the distance between cities
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // special condition: go to the city itself
            if (i == j) {
                distance[i][j] = 0;
                continue;
            }

            int xDiff = abs(cities[i].xCoordinate - cities[j].xCoordinate);
            int yDiff = abs(cities[i].yCoordinate - cities[j].yCoordinate);

            // distance formula using 'Pythagorean theorem'
            double calculationResult = sqrt(pow(xDiff, 2) + pow(yDiff, 2));

            // store the result into the vector array (undirected, or both direction possible)
            distance[i][j] = calculationResult;
            distance[j][i] = calculationResult;
        }
    }

    /*
     * idea for dynamic programming:
     *
     * dp[i][j] : the shortest path start from city 'i', pass 'j' cities (only once), and back to the beginning
     *
     * range for 'j' : 0 -> (2 ^ (n - 1) - 1) == 0 -> ((1 << (n - 1)) - 1)
     *
     * j : cities set excluding 'i', eg. {0, 1, 2, 3}, start {0}, j will be {1, 2, 3}
     *
     * dp[0][7] = dp[0]{1, 2, 3} : binary digit 111 shows that city 1, 2, and 3 are all in 'j'
     */

    vector<vector<double>> dp(N, vector<double>(1 << (N - 1)));

    // initialize the first column of the dp vector array
    for (int i = 0; i < N; i++) {
        dp[i][0] = distance[i][0];
    }

    // fill in the leftover values of the dp vector array
    for (int j = 1; j < (1 << (N - 1)); j++) {
        for (int i = 0; i < N; i++) {
            // initialize the array to the maximum
            dp[i][j] = MAX;

            // if city 'i' is in the cities set 'j', skip it
            if (((j >> (i - 1)) & 1) == 1) {
                continue;
            }

            // if city 'i' is not in the cities set 'j'
            // dp[i]{v} = min(dis[i][k] + dp[k]{v - k})
            // which 'i' does not belong to 'v', 'k' belongs to 'v'
            if (((j >> (i - 1)) & 1) == 0) {
                for (int k = 1; k < N; k++) {
                    // for all the cities in 'j' except the specific city 'i'
                    if ((j >> (k - 1)) & 1 == 1) {
                        // get city 'k'
                        if (dp[i][j]>distance[i][k] + dp[k][j ^ (1 << (k - 1))]) {
                            // take the smaller value
                            dp[i][j] = distance[i][k] + dp[k][j ^ (1 << (k - 1))];
                        }
                    }
                }
            }
        }
    }

    // final result from the dp vector array
    double answer = dp[0][(1 << (N - 1)) - 1];

    // output the result
    cout << answer << endl;

    return 0;
}