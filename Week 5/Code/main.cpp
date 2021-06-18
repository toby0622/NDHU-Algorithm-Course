/*
 * Question Idea:
 *
 * Find a longest subsequence that the first half
 * is ascending and the second half is descending,
 * the length for both halves also need to be the same
 */

/*
 * Solution Idea:
 *
 * Go through the given sequence from the start
 * Find the longest increasing subsequence (for start)
 * Go through the given sequence from the end
 * Find the longest increasing subsequence (from end)
 * Find the biggest possible answer
 */

#include <iostream>
using namespace std;

const int N = 10010;
const int INFINITE = 999999;

int input[N];
int ls[N];
int rs[N];
int f[N];

int main() {
    int n;
    int ans;

    // Load in the amount of elements in a case
    while (cin >> n) {
        // Load in the element data and initialize the array
        for (int i = 1; i <= n; i++) {
            cin >> input[i];
            f[i] = INFINITE;
        }

        f[0] = 0;

        // Find the LIS from the start (ascending)
        for (int i = 1; i <= n; i++) {
            int p;

            // lower_bound(vector.begin(), vector.end(), value)
            // 'lower_bound' returns index of the smallest result that is bigger or equal to value
            p = lower_bound(f, f + 1 + n, input[i]) - f;
            ls[i] = p;
            f[p] = input[i];
        }

        // Reinitialize the function for later use
        for (int i = 1; i <= n; i++) {
            f[i] = INFINITE;
            f[0] = 0;
        }

        // Find the LIS from the end (descending)
        for (int i = n; i >= 1; i--) {
            int p;
            p = lower_bound(f, f + 1 + n, input[i]) - f;
            rs[i] = p;
            f[p] = input[i];
        }

        // Initialize the answer (the length for half of the sequence)
        ans = 0;

        // Find the biggest possible length for the half sequence
        for (int i = 1; i <= n; i++) {
            /*
             * 'min' to find the smaller length because smaller
             * one will be included by the bigger one, yet bigger
             * one can't be included in the smaller one, which might
             * cause the result to be a un-even halves
             */
            /*
             * With the restriction mentioned above, using 'max'
             * we can find the biggest possible length for each
             * of the halves
             */
            ans = max(ans, min(ls[i], rs[i]));
        }

        // Calculate the total length of the sequence
        ans = ans * 2 - 1;
        // Output the final result
        cout << ans << endl;
    }
}