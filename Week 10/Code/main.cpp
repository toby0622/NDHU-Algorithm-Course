/*
 * main idea:
 *
 * given a directed graph with specific weight,
 * find whether the negative judgement exists or not
 */

/*
 * input:
 *
 * total cases, n dots, m edges
 * u vertex -> v vertex, w weight
 *
 * output:
 *
 * negative judgement exists -> possible
 * negative judgement non-exists -> not possible
 */

/*
 * reference:
 * difference between Bellman-Ford & Floyd-Warshall algorithm
 *
 * The Bellman–Ford algorithm is an algorithm that computes
 * shortest paths from a single source vertex to all of the
 * other vertices in a weighted digraph whereas Floyd-Warshall
 * computes shortest paths from each node to every other node.
 * (from stackoverflow)
 */

#include <iostream>
using namespace std;

const int INFINITY = 999999;

// every elements that need for creating an edge (directed & weighted)
class Edge {
public:
    int from;
    int to;
    int distance;
};

int main() {
    // total cases
    int cn;

    cin >> cn;

    // condition for each case
    for (int k = 0; k < cn; k++) {
        // dots of amount 'n'
        int n;
        // edges of amount 'm'
        int m;

        cin >> n >> m;

        Edge edges[2005];

        // input the needed elements for forming an edge (start, end, weight)
        for (int i = 0; i < m; i++) {
            cin >> edges[i].from >> edges[i].to >> edges[i].distance;
        }

        int sourceDistance[1005] = {};

        // initialize the source distance between starting and ending to infinity
        for (int i = 1; i < n; i++) {
            sourceDistance[i] = INFINITY;
        }

        // function for 'Bellman-Ford Algorithm'
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < m; j++) {
                sourceDistance[edges[j].to] = min (
                        sourceDistance[edges[j].from] + edges[j].distance,
                        sourceDistance[edges[j].to] );
            }
        }

        // one more to find negative cycle
        bool negativeCycle = false;

        // condition: negative cycle exist
        for (int j = 0; j < m; j++) {
            if (sourceDistance[edges[j].from] + edges[j].distance
                    < sourceDistance[edges[j].to]) {
                cout << "possible" << endl;
                negativeCycle = true;
                break;
            }
        }

        // condition: negative cycle non-exist
        if(!negativeCycle){
            cout << "not possible" << endl;
        }
    }
    return 0;
}