#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

int dx[4] = {(-1), 1, 0, 0};
int dy[4] = {0, 0, (-1), 1};

int maxMinefield(vector<vector<int>> &Map) {
    int n = Map.size();
    int m = Map[0].size();

    vector<vector<int>> vis(n, vector<int> (m, 0));

    int res = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (Map[i][j] == 1 && vis[i][j] == 0) {
                int count = 0;

                stack<pair<int, int>> s;

                s.push({i, j});

                vis[i][j] = 1;

                while (!s.empty()) {
                    count++;

                    int x = s.top().first;
                    int y = s.top().second;

                    s.pop();

                    for (int l = 0; l < 4; l++) {
                        int u = x + dx[l];
                        int v = y + dy[l];

                        if (u >= 0 && u < n && v >= 0 && v < m && Map[u][v] == 1 && vis[u][v] == 0) {
                            vis[u][v] = 1;
                            s.push({u, v});
                        }
                    }
                }

                res = max(res, count);
            }
        }
    }

    return res;
}

int main() {
    int n;
    int m;

    vector<char> mapSize;

    string indicator;

    cin >> indicator;

    for (char & i : indicator) {
        if (i == 'm' ||
            i == 'a' ||
            i == 'p' ||
            i == '[' ||
            i == ']') {
            continue;
        }

        mapSize.push_back(i);
    }

    n = mapSize[0] - '0';
    m = mapSize[1] - '0';

    char equal;
    char bracket;

    cin >> equal >> bracket;

    vector<int> value;
    string valueRow;

    for (int i = 0; i < n; i++) {
        valueRow.clear();
        cin >> valueRow;
//        cout << valueRow << endl;

        stringstream ss(valueRow);

        for (int j; ss >> j;) {
            value.push_back(j);

            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
    }

    vector<vector<int>> Map(n, vector<int> (m, 0));

    int counter = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Map[i][j] = value[counter];
            counter = counter + 1;
        }
    }

    cout << maxMinefield(Map) << endl;

    return 0;
}