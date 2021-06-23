#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#define N 20
#define MAX 10000
using namespace std;

class city {
public:
    int cityNumber;
    int xCoordinate;
    int yCoordinate;
};

// Function to find the minimum
// cost path for all the paths
void findMinRoute(vector<vector<double>> &distance) {
    double sum = 0;
    int counter = 0;
    int i = 0;
    int j = 0;
    double min = MAX;
    map<int, int> visitedRouteList;

    // Starting from the 0th indexed
    // city i.e., the first city
    visitedRouteList[0] = 1;

    int route[distance.size()];

    // Traverse the adjacency matrix
    while (i < distance.size() && j < distance[i].size()) {
        // Corner of the Matrix
        if (counter >= distance[i].size() - 1) {
            break;
        }

        // If this path is unvisited then
        // and if the cost is less then
        // update the cost
        if (j != i && (visitedRouteList[j] == 0)) {
            if (distance[i][j] < min) {
                min = distance[i][j];
                route[counter] = j + 1;
            }
        }

        j++;

        // Check all paths from the
        // ith indexed city
        if (j == distance[i].size()) {
            sum = sum + min;
            min = MAX;
            visitedRouteList[route[counter] - 1] = 1;
            j = 0;
            i = route[counter] - 1;
            counter++;
        }
    }

    // Update the ending city in array
    // from city which was last visited
    i = route[counter - 1] - 1;

    for (j = 0; j < distance.size(); j++) {

        if ((i != j) && distance[i][j] < min) {
            min = distance[i][j];
            route[counter] = j + 1;
        }
    }

    sum = sum + min;

    // Started from the node where
    // we finished as well.
    cout << sum << endl;
}

// Driver Code
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
                distance[i][j] = (-1);
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

    // Function Call
    findMinRoute(distance);

    return 0;
}