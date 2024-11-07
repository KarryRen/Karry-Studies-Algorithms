/*
 * @Time    : 2024/10/27 13:06
 * @Author  : Karry Ren
 * @Comment : Compute the range of duplicate number.
 * @LeetCode: 704
*/

#include<iostream>

using namespace std;

const int N = 1e6 + 10;
int n, m; // n is the number of array ; m is the number of finding times;
int q[N];

int main() {
    scanf("%d %d", &n, &m);

    // input array
    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i]);
    }

    // finding m times
    while (m--) {
        int num; // the target number
        scanf("%d", &num);

        // DICHOTOMY finding
        int l = 0, r = n - 1; // the boundary

        // - find the left beginning
        while (l < r) {
            // -- step 1 set mid
            int mid = (l + r) >> 1;
            // -- step 2 check and adjust the l and r
            if (q[mid] >= num) r = mid;
            else l = mid + 1;
        }

        // - judge the answer
        if (q[l] != num) {
            printf("-1 -1 \n");
        } else {
            printf("%d ", l);
            // - find the right ending
            int l = 0, r = n - 1; // the boundary
            while (l < r) {
                // -- step 1 set mid
                int mid = (l + r + 1) >> 1;
                // -- step 2 check and adjust the l and r
                if (q[mid] <= num) l = mid;
                else r = mid - 1;
            }
            printf("%d \n", l);
        }
    }

    return 0;
}
