/*
 * Question Idea:
 *
 * There are 'n' SMTP servers connected with 'm' cables,
 * each cable connects between two servers,
 * the latency exists by using cable to send email.
 * Assume that the server will not cause any additional latencies,
 * what is the best possible time (latency) to send email
 * from server S to server T?
 *
 * Solution:
 *
 * With no weight on the graph,
 * we calculate the shortest path using 'Dijkstra Algorithm'
 * to find the path of the graph and
 * implement priority queue to improve the efficiency.
 *
 */

#include <iostream>
#include <vector>
#include <queue>
#define INFINITE 999999
// pair = 'combine two data into one' or 'function need to return two data at once'
#define pair_integer pair<int, int>
using namespace std;

int latency[20010];
int n;
int m;
vector<vector<pair_integer>> adj;

void Dijkstra(int s) {
    // initialize the latency to infinite (not possible to reach)
    for (int i = 0; i < n; i++) {
        latency[i] = INFINITE;
    }

    // initialize the latency for the starting point
    latency[s] = 0;

    // ascending priority queue
    priority_queue<pair_integer, vector<pair_integer>, greater<>> apq;

    // insert the element to the queue
    apq.push(pair_integer(latency[s], s));

    pair_integer p;

    int t;
    int u;

    // condition: the queue is not empty
    while (!apq.empty()) {
        p = apq.top();
        apq.pop();
        t = p.first;
        u = p.second;

        // condition: if the latency is higher,
        // skip it and find the next one (or unreachable)
        if (t > latency[u]) {
            continue;
        }

        // go through the vector array and
        // find the shortest latency sum
        for (int i = 0; i < adj[u].size(); i++) {
            if (latency[adj[u][i].first] > latency[u] + adj[u][i].second) {
                latency[adj[u][i].first] = latency[u] + adj[u][i].second;
                apq.push(pair_integer(latency[adj[u][i].first], adj[u][i].first));
            }
        }
    }
}

int main() {
    int tc;

    // input the amount of total cases
    cin >> tc;

    int s;
    int t;

    // condition for each case
    for (int k = 1; k <= tc; k++) {
        // input all the prerequisites
        cin >> n >> m >> s >> t;

        // initialize the vector array
        adj.assign(n, vector<pair_integer>(0));

        int x;
        int y;
        int l;

        // wire up the servers and set up the latency
        for (int i = 0; i < m; i++) {
            cin >> x >> y >> l;

            // connected with bidirectional cable
            adj[x].push_back(pair_integer(y, l));
            adj[y].push_back(pair_integer(x, l));
        }

        // execute the 'Dijkstra Algorithm'
        Dijkstra(s);

        cout << "Case #" << k << ": ";

        // condition: find the shortest possible latency
        if (latency[t] != INFINITE) {
            cout << latency[t] << endl;
        }

        // condition: unable to link the server
        else {
            cout << "unreachable" << endl;
        }
    }
}