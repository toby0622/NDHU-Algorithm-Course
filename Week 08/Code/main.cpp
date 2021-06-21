/*
 * Main Idea:
 *
 * Rectangle lawn with 'n' sprinklers, the sprinkler sprinkles in circle area,
 * try to find the smallest amount of sprinklers use to cover the rectangle lawn.
 */

/*
 * Solution:
 *
 * Exchange every sprinkler into the corresponding coverage section
 * (calculate the right & left point intersection), greedy with left intersection.
 * By using the left intersection point, find the maximum distance from
 * the previous end point (the biggest right intersection point)
*/

#include <iostream>
#include <cmath>
using namespace std;

// sprinklers with their sprinkle area (left end & right end)
class Segment {
public:
    double l;
    double r;
};

// possible number of total sprinklers
Segment S[10500];

// self-made comparing method
int Compare(const void *a, const void *b) {
    auto *p = (Segment *)a;
    auto *q = (Segment *)b;

    if (p -> l < q -> l) {
        return (-1);
    }
    else {
        return 1;
    }
}

int main() {
    int n; // amount of sprinklers
    int l; // long of rectangle
    int w; // wide of rectangle
    int p; // position of the sprinkler
    int r; // radius of the sprinkler

    // each test case
    while (cin >> n >> l >> w) {
        int size = 0;

        // each sprinkler
        for (int i = 0; i < n; i++) {
            cin >> p >> r;

            if (2 * r > w) {
                // overflow will happen if purely using square as condition
                S[size].l = p - sqrt(1.0 * r * r - 0.25 * w * w);
                S[size].r = p + sqrt(1.0 * r * r - 0.25 * w * w);

                size++;
            }
        }

        // sort the segment using self-made comparing method
        qsort(S, size, sizeof(Segment), Compare);

        int index;
        int now = 0;
        int count = 0;
        double l_bound = 0;
        double r_bound = 0;

        // execute the solution method mentioned at the beginning
        while (l_bound < l && now < size) {
            index = now;

            while (S[index].l <= l_bound && index < size) {
                if (r_bound < S[index].r) {
                    r_bound = S[index].r;
                }

                index++;
            }

            if (index == now) {
                break;
            }
            else {
                count++;
                now = index;
                l_bound = r_bound;
            }
        }

        // output the result as question required
        if (S[0].l > 0 || l_bound < l) {
            cout << (-1) << endl;
        }
        else {
            cout << count << endl;
        }
    }
    return 0;
}