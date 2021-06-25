#include<iostream>
#include<cmath>
#include<ctime>
using namespace std;

// number of city nodes
#define N 20
// x, y coordinates for the cities
double C[N][2] = {};
// number of ants
#define M 20
// maximum loop amount
int NcMax = 200;
// info factor, expected factor, global info factor, local info factor, transition factor
double alpha = 2, beta = 3, rou = 0.1, alpha1 = 0.1,  qzero = 0.01;
// constant for local update
double Lnn;
// array for recording the distance between the cities
double allDistance[N][N];

// calculate the distance between the two cities
double calculateDistance(int i, int j) {
    return sqrt(pow((C[i][0] - C[j][0]), 2.0) + pow((C[i][1] - C[j][1]), 2.0));
}

// using array to record the distance between each cities
void calculateAllDistance() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                allDistance[i][j] = calculateDistance(i, j);
                allDistance[j][i] = allDistance[i][j];
            }
        }
    }
}

// the total distance for the tour going through all of the cities
double calculateSumOfDistance(int* tour) {
    double sum = 0;

    for (int i = 0; i < N; i++) {
        int row = *(tour + 2 * i);
        int col = *(tour + 2 * i + 1);
        sum += allDistance[row][col];
    }

    return sum;
}

class ACSAnt;

class AntColonySystem {
private:
    // information weight between each nodes
    double info[N][N]{};
    // the visibility between each nodes
    double visible[N][N]{};

public:
    AntColonySystem() = default;
    // calculate the transition possibility from the current node to the next node
    double Transition(int i, int j);
    // update the information for the local path
    void UpdateLocalPathRule(int i, int j);
    // Initialization
    void InitParameter(double value);
    // update the information for the global path
    void UpdateGlobalPathRule(int* bestTour, int globalBestLength);
};

// calculate the transition possibility from the current node to the next node
double AntColonySystem::Transition(int i, int j) {
    if (i != j) {
        return (pow(info[i][j], ::alpha) * pow(visible[i][j], ::beta));
    }

    else {
        return 0.0;
    }
}

// update the information for the local path
void AntColonySystem::UpdateLocalPathRule(int i, int j) {
    info[i][j] = (1.0 - ::alpha1) * info[i][j] + ::alpha1 * (1.0 / (N * Lnn));
    info[j][i] = info[i][j];
}

// Initialization
void AntColonySystem::InitParameter(double value) {
    // initialize the path information weight
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            info[i][j] = value;
            info[j][i] = value;

            if (i != j) {
                visible[i][j] = 1.0 / allDistance[i][j];
                visible[j][i] = visible[i][j];
            }
        }
    }
}

// update the information for the global path
void AntColonySystem::UpdateGlobalPathRule(int* bestTour, int globalBestLength) {
    for (int i = 0; i < N; i++) {
        int row = *(bestTour + 2 * i);
        int col = *(bestTour + 2 * i + 1);
        info[row][col] = (1.0 - ::rou) * info[row][col] + ::rou * (1.0 / globalBestLength);
        info[col][row] = info[row][col];
    }
}

class ACSAnt {
private:
    AntColonySystem* antColony;

protected:
    // index value for the starting city
    int startCity;
    // index value for the current city
    int cururentCity;
    // tabu list
    int allowed[N];
    // current path
    int Tour[N][2];
    // index for the current path, start from zero, record the cities which have been visited by the ants
    int currentTourIndex;

public:
    ACSAnt(AntColonySystem* acs, int start) {
        antColony = acs;
        startCity = start;
    }

    // start the searching progress
    int* Search();
    // select the following node
    int Choose();
    // move to the next node
    void MoveToNextCity(int nextCity);
};

// start the searching progress
int* ACSAnt::Search() {
    cururentCity = startCity;
    int toCity;
    currentTourIndex = 0;

    for (int & i : allowed) {
        i = 1;
    }

    allowed[cururentCity] = 0;
    int endCity;
    int count = 0;

    do {
        count++;
        endCity = cururentCity;
        toCity = Choose();

        if (toCity >= 0) {
            MoveToNextCity(toCity);
            antColony -> UpdateLocalPathRule(endCity, toCity);
            cururentCity = toCity;
        }
    } while (toCity >= 0);

    MoveToNextCity(startCity);
    antColony -> UpdateLocalPathRule(endCity, startCity);

    return *Tour;
}

// select the next node (city)
int ACSAnt::Choose() {
    int nextCity = (-1);
    double q = rand() / (double)RAND_MAX;

    // if 'q' is smaller or equal to 'qzero', use 'priori', otherwise use 'transition probability'
    if (q <= ::qzero) {
        // the probability for moving to the next node
        double probability = (-1.0);

        for (int i = 0; i < N; i++) {
            // delete the visited node, find the maximum possible node in the leftovers
            if (1 == allowed[i]) {
                double prob = antColony -> Transition(cururentCity, i);

                if (prob  > probability) {
                    nextCity = i;
                    probability = prob;
                }
            }
        }
    }

    else {
        // otherwise condition: transition probability

        // create an random value to check which section it has been
        double p = rand() / (double)RAND_MAX;
        double sum = 0.0;
        // section point for probability, where 'p' is, the point should be the transition direction
        double probability = 0.0;

        // calculate the denominator value of the probability formula
        for (int i = 0; i < N; i++) {
            if (1 == allowed[i]) {
                sum += antColony -> Transition(cururentCity, i);
            }
        }

        for (int j = 0; j < N; j++) {
            if (1 == allowed[j] && sum > 0) {
                probability += antColony -> Transition(cururentCity, j) / sum;

                if (probability >= p || (p > 0.9999 && probability > 0.9999)) {
                    nextCity = j;
                    break;
                }
            }
        }
    }

    return nextCity;
}

// move to the next node (city)
void ACSAnt::MoveToNextCity(int nextCity) {
    allowed[nextCity] = 0;
    Tour[currentTourIndex][0] = cururentCity;
    Tour[currentTourIndex][1] = nextCity;
    currentTourIndex++;
    cururentCity = nextCity;
}

// select next node and use the function to calculate the distance
int ChooseNextNode(int currentNode, int visitedNode[]) {
    int nextNode = (-1);
    double shortDistance = 0.0;

    for (int i = 0; i < N; i++) {
        // delete the visited node, and select the closest node from the leftovers
        if (1 == visitedNode[i]) {
            if (shortDistance == 0.0) {
                shortDistance = allDistance[currentNode][i];
                nextNode = i;
            }

            if (shortDistance < allDistance[currentNode][i]) {
                nextNode = i;
            }
        }
    }

    return nextNode;
}

// function that calculates the adjacent distance from the specific node
double CalAdjacentDistance(int node) {
    double sum = 0.0;
    int visitedNode[N];

    for (int & j : visitedNode) {
        j = 1;
    }

    visitedNode[node] = 0;
    int currentNode = node;
    int nextNode;

    do {
        nextNode = ChooseNextNode(currentNode, visitedNode);

        if (nextNode >= 0) {
            sum += allDistance[currentNode][nextNode];
            currentNode = nextNode;
            visitedNode[currentNode] = 0;
        }
    } while (nextNode >= 0);

    sum += allDistance[currentNode][node];

    return sum;
}

int main() {
    int cityNumber;
    double xCoordinate;
    double yCoordinate;

    for (int i = 0; i < N; i++) {
        cin >> cityNumber >> xCoordinate >> yCoordinate;

        ::C[i][0] = xCoordinate;
        ::C[i][1] = yCoordinate;
    }

    srand(time(0));

    // using array to record the distance between two cities
    calculateAllDistance();

    // ACO system object
    AntColonySystem* acs = new AntColonySystem();
    ACSAnt* ants[M];

    // ant are evenly distributed in the cities
    for (int k = 0; k < M; k++) {
        ants[k] = new ACSAnt(acs, (int)(k % N));
    }

    calculateAllDistance();

    // randomly select a node and find the distance using closest adjacent method
    int node = rand() % N;
    Lnn = CalAdjacentDistance(node);

    // initialize the path info for each path
    double initInfo = 1 / (N * Lnn);
    acs -> InitParameter(initInfo);

    // best possible tour (global)
    int globalTour[N][2];

    // best possible tour length (global)
    double globalBestLength = 0.0;

    for (int i = 0; i < NcMax; i++) {
        // best possible tour (local)
        int localTour[N][2];

        // best possible tour length (local)
        double localBestLength = 0.0;

        // current tour length
        double tourLength;

        for (int j = 0; j < M; j++) {
            int* tourPath = ants[j] -> Search();
            tourLength = calculateSumOfDistance(tourPath);

            // local comparison, record the path and length
            if (tourLength < localBestLength || abs(localBestLength - 0.0) < 0.000001) {
                for (int m = 0; m < N; m++) {
                    int row = *(tourPath + 2 * m);
                    int col = *(tourPath + 2 * m + 1);
                    localTour[m][0] = row;
                    localTour[m][1] = col;
                }

                localBestLength = tourLength;
            }
        }

        // global comparison, record the path and length
        if (localBestLength < globalBestLength || abs(globalBestLength - 0.0) < 0.000001) {
            for (int m = 0; m < N; m++) {
                globalTour[m][0] = localTour[m][0];
                globalTour[m][1] = localTour[m][1];
            }

            globalBestLength = localBestLength;
        }

        acs -> UpdateGlobalPathRule(*globalTour, globalBestLength);
    }

    // output the best possible tour length (global)
    cout << globalBestLength << endl;

    return 0;
}