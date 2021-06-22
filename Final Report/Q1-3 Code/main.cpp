#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int N = 20;
const float INF = 999999.0;

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
float final_res = INF;

// Function to find the minimum edge cost
// having an end at the vertex i
float firstMin(float adj[N][N], int i) {
    float min = INF;

    for (int k = 0; k < N; k++) {
        if (adj[i][k] < min && i != k)
            min = adj[i][k];
    }

    return min;
}

// function to find the second minimum edge cost
// having an end at the vertex i
int secondMin(float adj[N][N], int i) {
    int first = INT_MAX;
    int second = INT_MAX;

    for (int j = 0; j < N; j++) {
        if (i == j) {
            continue;
        }

        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        }

        else if (adj[i][j] <= second && adj[i][j] != first) {
            second = adj[i][j];
        }
    }

    return second;
}

void TSPRec(float adj[N][N], int curr_bound, int curr_weight, int level, int curr_path[]) {
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[curr_path[level-1]][curr_path[0]];

            if (curr_res < final_res) {
                final_res = curr_res;
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (adj[curr_path[level-1]][i] != 0 && visited[i] == false) {
            int temp = curr_bound;

            curr_weight = curr_weight + adj[curr_path[level - 1]][i];

            if (level == 1) {
                curr_bound -= ((firstMin(adj, curr_path[level-1]) + firstMin(adj, i))/2);
            }

            else {
                curr_bound -= ((secondMin(adj, curr_path[level-1]) + firstMin(adj, i))/2);
            }

            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;

                TSPRec(adj, curr_bound, curr_weight, level+1, curr_path);
            }

            curr_weight -= adj[curr_path[level-1]][i];
            curr_bound = temp;

            memset(visited, false, sizeof(visited));
            for (int j = 0; j <= level - 1; j++) {
                visited[curr_path[j]] = true;
            }
        }
    }
}

void TSP(float adj[N][N]) {
    int curr_path[N + 1];
    int curr_bound = 0;

    memset(curr_path, (-1), sizeof(curr_path));
    memset(visited, 0, sizeof(curr_path));

    for (int i = 0; i < N; i++) {
        curr_bound = curr_bound + (firstMin(adj, i) + secondMin(adj, i));
    }

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    visited[0] = true;
    curr_path[0] = 0;

    TSPRec(adj, curr_bound, 0, 1, curr_path);
}

int main() {
    vector<city> cities(N);

    for (int i = 0; i < N; i++) {
        cin >> cities[i].cityNumber;
        cin >> cities[i].xCoordinate;
        cin >> cities[i].yCoordinate;
    }

    float adj[N][N] = {};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                adj[i][j] = 0;
                continue;
            }

            float xDiff = abs(cities[i].xCoordinate - cities[j].xCoordinate);
            float yDiff = abs(cities[i].yCoordinate - cities[j].yCoordinate);

            float distance = sqrt(pow(xDiff, 2) + pow(yDiff, 2));

            adj[i][j] = distance;
            adj[j][i] = distance;
        }
    }

//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            cout << adj[i][j] << " ";
//        }
//        cout << endl;
//    }

    TSP(adj);

    cout << final_res << endl;

    return 0;
}