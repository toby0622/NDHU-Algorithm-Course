/*
 * Question's Main Idea:
 * Find the smallest distance between any arbitrary two points
 *
 * Design Algorithm:
 * 1. Sort all of the points in the two-dimensional space by the x-axis value
 * 2. Keep dividing the points into half and establishing two subgroups
 * 3. As soon as the subgroup has the elements smaller or equal to three,
 *    find all distance between each point using method of exhaustion
 * 4. With the smaller distance found in the left subgroup & right subgroup,
 *    compare left smaller and the right smaller in order to find the minimum.
 * 5. Check the cross-domain points' distance within two times the minimum
 *    with the divide line to be in the middle
 * 6. Compare between the smaller cross-domain point distance and the minimum
 *    to find the merge minimum and combine these two calculated subgroups
 *
 * Hint:
 * Sort the points by x-axis first for easier comparison
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#define MAX 10000
using namespace std;

// Class 'Point'
class Point {
public:
    // 'x' value of the point
    double x;
    // 'y' value of the point
    double y;

    // Calculate the distance between two points
    double Distance(Point point) {
        double result;
        result = sqrt((point.x - x)*(point.x - x) + (point.y - y)*(point.y - y));
        return result;
    }
};

// Initial an array with Point attribute
Point point[MAX];

//  Comparing function for C++ sort using x-axis of the point
bool compareXaxis (Point a, Point b) {
    if (a.x < b.x) {
        return true;
    }
    else {
        return false;
    }
}

// Comparing function for C++ sort using y-axis of the point
bool compareYaxis (Point a, Point b) {
    if (a.y < b.y) {
        return true;
    }
    else {
        return false;
    }
}

// Algorithm 'Divide & Conquer'
double divideNconquer(int L, int R) {
    int i;
    int j;

    // Only one point
    if (L >= R) {
        return MAX;
    }
    // Two or three points
    else if (R - L < 3) {
        double d = MAX;

        // Exhaustion method
        for (i = L; i < R; i++) {
            for (j = i + 1; j <= R; j++) {
                d = min(d, point[i].Distance(point[j]));
            }
        }

        return d;
    }

    int M = (L + R) / 2;

    // Find the smallest distance for each subgroup
    double d = min(divideNconquer(L, M), divideNconquer(M + 1, R));

    if (d == 0) {
        return 0;
    }

    int n = 0;
    Point strip[MAX];

    // Find those points closer to mid (with the distance smaller than current minimum d)
    // Left side
    for (i = M; i >= L && point[M].x - point[i].x < d; i--) {
        strip[n++] = point[i];
    }
    // Right side
    for (i = M + 1; i <= R && point[i].x - point[M].x < d; i++) {
        strip[n++] = point[i];
    }

    // Sort by y-axis
    sort(strip, strip + n, compareYaxis);

    // Find the smallest distance across subgroups
    for (i = 0; i < n; i++) {
        for (j = 1; j <= 3 && i + j < n; j++) {
            d = min(d, strip[i].Distance(strip[i + j]));
        }
    }

    return d;
}

int main()
{
    int n;
    int i;

    // Load in all the points needed
    while (cin >> n && n > 0) {
        // Load in the x & y value of the point
        for (i = 0; i < n; i++) {
            cin >> point[i].x >> point[i].y;
        }

        // Sort by x-axis
        sort(point, point + n, compareXaxis);

        // Execute the algorithm
        double answer = divideNconquer(0, n - 1);

        // Output the answer
        if (answer == 10000) {
            cout << "INFINITY" << endl;
        }
        else {
            cout << fixed;
            cout << setprecision(4);
            cout << answer << endl;
        }
    }

    return 0;
}
