// Traveling Salesman Problem Using Branch & Bound
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#define N 20
#define MAX 999999
using namespace std;

class city {
public:
    int cityNumber;
    int xCoordinate;
    int yCoordinate;
};

// visited[] keeps track of the already visited nodes
// in a particular path
bool visited[N];

// Stores the final minimum weight of shortest tour.
double final_res = MAX;

// Function to find the minimum edge cost
// having an end at the vertex i
double firstMin(vector<vector<double>> &distance, int i) {
    double min = MAX;

    for (int k = 0; k < N; k++) {
        if (distance[i][k] < min && i != k) {
            min = distance[i][k];
        }
    }

    return min;
}

// function to find the second minimum edge cost
// having an end at the vertex i
double secondMin(vector<vector<double>> &distance, int i) {
    double first = MAX;
    double second = MAX;

    for (int j = 0; j < N; j++) {
        if (i == j) {
            continue;
        }

        if (distance[i][j] <= first) {
            second = first;
            first = distance[i][j];
        }

        else if (distance[i][j] <= second && distance[i][j] != first) {
            second = distance[i][j];
        }
    }

    return second;
}

// function that takes as arguments:
// curr_bound -> lower bound of the root node
// curr_weight-> stores the weight of the path so far
// level-> current level while moving in the search
//         space tree
// curr_path[] -> where the solution is being stored which
//                would later be copied to final_path[]
void TSPRec(vector<vector<double>> &distance, double curr_bound, double curr_weight, int level, int curr_path[]) {
    // base case is when we have reached level N which
    // means we have covered all the nodes once
    if (level == N) {
        // check if there is an edge from last vertex in
        // path back to the first vertex
        if (distance[curr_path[level - 1]][curr_path[0]] != 0) {
            // curr_res has the total weight of the
            // solution we got
            double curr_res = curr_weight + distance[curr_path[level - 1]][curr_path[0]];

            // Update final result and final path if
            // current result is better.
            if (curr_res < final_res) {
                final_res = curr_res;
            }
        }

        return;
    }

    // for any other level iterate for all vertices to
    // build the search space tree recursively
    for (int i = 0; i < N; i++) {
        // Consider next vertex if it is not same (diagonal
        // entry in adjacency matrix and not visited
        // already)
        if (distance[curr_path[level-1]][i] != 0 && !visited[i]) {
            double temp = curr_bound;

            curr_weight += distance[curr_path[level-1]][i];

            // different computation of curr_bound for
            // level 2 from the other levels
            if (level == 1) {
                curr_bound -= ((firstMin(distance, curr_path[level-1]) + firstMin(distance, i))/2);
            }

            else {
                curr_bound -= ((secondMin(distance, curr_path[level-1]) + firstMin(distance, i))/2);
            }

            // curr_bound + curr_weight is the actual lower bound
            // for the node that we have arrived on
            // If current lower bound < final_res, we need to explore
            // the node further
            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;

                // call TSPRec for the next level
                TSPRec(distance, curr_bound, curr_weight, level+1, curr_path);
            }

            // Else we have to prune the node by resetting
            // all changes to curr_weight and curr_bound
            curr_weight -= distance[curr_path[level - 1]][i];
            curr_bound = temp;

            // Also reset the visited array
            memset(visited, false, sizeof(visited));

            for (int j=0; j<=level-1; j++) {
                visited[curr_path[j]] = true;
            }
        }
    }
}

// This function sets up final_path[]
void TSP(vector<vector<double>> &distance) {
    int curr_path[N + 1];

    // Calculate initial lower bound for the root node
    // using the formula 1/2 * (sum of first min +
    // second min) for all edges.
    // Also initialize the curr_path and visited array
    double curr_bound = 0;

    memset(curr_path, (-1), sizeof(curr_path));
    memset(visited, 0, sizeof(visited));

    // Compute initial bound
    for (int i = 0; i < N; i++) {
        curr_bound += (firstMin(distance, i) + secondMin(distance, i));
    }

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
    visited[0] = true;
    curr_path[0] = 0;

    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    TSPRec(distance, curr_bound, 0, 1, curr_path);
}

int main()
{
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

    // TSP function using BnB
    TSP(distance);

    cout << final_res << endl;

    return 0;
}