// Algorithm Lab Week 11: Crime Wave - The Sequel

/*
 * main idea:
 *
 * m policeman choose n of them to go to the robbed bank,
 * find the minimum average time to the bank
 */

/*
 * algorithm design:
 *
 * the police is the index 1 to m,
 * the bank is the index (m + 1) to (m + n),
 * find  the minimum cost and maximum flow from point 0 to (m + n + 1)
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define INFINITY 999999
#define MAXN 50
using namespace std;

class Edge {
public:
    int from;
    int to;
    int cap;
    int flow;
    double cost;

    Edge(int u, int v, int c, int f, double w) {
        from = u;
        to = v;
        cap = c;
        flow = f;
        cost = w;
    }
};

class MinCostMaxFlow {
public:
    int n{};
    int m{};

    vector<Edge> edges;
    vector<int> G[MAXN];

    // is in the queue
    int inq[MAXN]{};
    // Bellman-Ford
    double d[MAXN]{};
    // previous arc
    int p[MAXN]{};
    // improved amount
    int a[MAXN]{};

    void initialize(int number) {
        this -> n = number;

        for (int i = 0; i < number; i++) {
            G[i].clear();
        }

        edges.clear();
    }

    void addEdge(int from, int to, int cap, double cost) {
        edges.emplace_back(from, to, cap, 0, cost);
        edges.emplace_back(to, from, 0, 0, -cost);
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool BellmanFord(int s, int t, int &flow, double &cost) {
        for (int i = 0; i < n; i++) {
            d[i] = INFINITY;
        }

        memset(inq, 0, sizeof(inq));
        d[s] = 0;
        inq[s] = 1;
        p[s] = 0;
        a[s] = INFINITY;

        queue<int> Q;
        Q.push(s);

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u] = 0;

            for (int i = 0; i < G[u].size(); i++) {
                Edge & e = edges[G[u][i]];

                if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);

                    if (!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }

        if (d[t] == INFINITY) {
            return false;
        }

        flow = flow + a[t];
        cost = cost + d[t] * a[t];

        for (int u = t; u != s; u = edges[p[u]].from) {
            edges[p[u]].flow = edges[p[u]].flow + a[t];
            edges[p[u] ^ 1].flow = edges[p[u] ^ 1].flow - a[t];
        }

        return true;
    }

    // no negative weighted circle is there in the initial network
    int mincostMaxflow(int s, int t, double & cost) {
        int flow = 0;
        cost = 0;

        while (BellmanFord(s, t, flow, cost));

        return flow;
    }
};

MinCostMaxFlow g;

int main() {
    int n;
    int m;

    while (cin >> n >> m && n != 0 && m != 0) {
        g.initialize(n + m + 2);

        /*
         * group of vertices:
         *
         * 0 : source
         * (1 - m) : cruiser vertices
         * (m + 1) - (m + n) : bank vertices
         * (m + n + 1) : sink
         */

        // append the edges between cruiser vertices and bank vertices
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                double d;
                cin >> d;
                g.addEdge(j, m + i, 1, d);
            }

        // append the edges between the source and cruiser vertices
        for (int i = 1; i <= m; i++) {
            g.addEdge(0, i, 1, 0);
        }

        // append the edges between bank vertices and the sink
        for (int i = 1; i <= n; i++) {
            g.addEdge(m + i, m + n + 1, 1, 0);
        }

        double cost;

        g.mincostMaxflow(0, m + n + 1, cost);

        double answer = cost / n + 1e-8;

        cout << fixed << setprecision(2) << answer << endl;
    }

    return 0;
}