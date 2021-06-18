/*
 * General Idea :
 * (f + 1) people share (n) pie, and everyone should
 * get a complete piece of pie without combining with multiple
 * pieces, which the area should be the same. Find the biggest
 * possibility area for everyone (no need to be a circle).
 */

/*
 * Analysis :
 * Exchange the question to "whether we can get everyone a piece of
 * pie with the area of 'x'" and check the contradiction of it,
 * which is the value of 'x' be too big and couldn't match the
 * requirement that everyone get the same size of the pie.
 */

/*
 * Clue :
 * A pie with radius 'r' can only form (PI * r * r / x) pieces.
 */

#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

const int MAXN = 15000;
const double PI = acos(-1.0);

int times;
int n;
int f;
double a[MAXN];
double Max;

bool checkpie(double x) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum = sum + a[i] / x;
    }

    if (sum >= f + 1) {
        return true;
    }

    return false;
}

int main() {
    cin >> times;

    while (times--) {
        cin >> n >> f;

        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i] = PI * a[i] * a[i];
            Max = max(Max, a[i]);
        }

        double low = 0;
        double mid;

        while (Max - low > 0.00001) {
            mid = low + (Max - low) / 2;

            if (checkpie(mid)) {
                low = mid;
            }

            else {
                Max = mid;
            }
        }
        cout << std::fixed;
        cout << std::setprecision(4);
        cout << low << endl;
    }
    return 0;
}