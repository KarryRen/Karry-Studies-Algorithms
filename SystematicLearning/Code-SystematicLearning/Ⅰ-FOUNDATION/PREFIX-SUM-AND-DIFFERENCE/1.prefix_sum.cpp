/*
 * @Time    : 2024/11/16 23:13
 * @Author  : Karry Ren
 * @Comment : Compute the pre sum.
 * @LeetCode: 415、303、643
 *            724、LCR012、1991
*/

#include<iostream>

using namespace std;

const int N = 1e6 + 10; // the boundary

int q[N], s[N]; // the raw array and the sum array

int main() {
    int m, n; // the input num
    scanf("%d %d", &n, &m);

    // input the array
    for (int i = 1; i <= n; i++) scanf("%d", &q[i]);

    // compute the sum using equation (attention => s[0] = 0)
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + q[i];

    while (m--) {
        int l, r; // the began l and the end r
        scanf("%d %d", &l, &r);

        printf("%d\n", s[r] - s[l - 1]); // the important equation
    }

    return 0;
}