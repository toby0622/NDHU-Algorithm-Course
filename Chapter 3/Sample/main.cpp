#include <iostream>
using namespace std;

void floyd (int n, const int W[8][8], int D[8][8], int P[8][8]) {
    int i;
    int j;
    int k;

    for (i = 0; i <= n; i ++) {
        for (j = 1; j <= n; j++) {
            P[i][j] = 0;
            D[i][j] = W[i][j];
        }
    }

    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    P[i][j] = k;
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}

void path (int q, int r) {
    if (P[q][r] != 0) {
        path(q, P[q][r]);
        cout << "v" << P[q][r];
        path(P[q][r], r);
    }
}

int main() {
    int W[8][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 4, 10000, 10000, 10000, 10, 10000},
            {0, 3, 0, 10000, 18, 10000, 10000, 10000},
            {0, 10000, 6, 0, 10000, 10000, 10000, 10000},
            {0, 10000, 5, 15, 0, 2, 19, 5},
            {0, 10000, 10000, 12, 1, 0, 10000, 10000},
            {0, 10000, 10000, 10000, 10000, 10000, 0, 10},
            {0, 10000, 10000, 10000, 8, 10000, 10000, 0},
    };

    int D[8][8];
    int P[8][8];

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            D[i][j] = 0;
            P[i][j] = 0;
        }
    }

    floyd(7, W, D, P);



    return 0;
}
