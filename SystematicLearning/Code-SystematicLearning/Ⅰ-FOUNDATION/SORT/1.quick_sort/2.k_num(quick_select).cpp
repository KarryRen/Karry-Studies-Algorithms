/*
 * @Time    : 2024/10/27 12:16
 * @Author  : Karry Ren
 * @Comment : Select the k^th (smallest or biggest) number by quick sort.
 * @LeetCode: 215
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10;
int n, k;
int q[N];

int quick_k_num(int q[], int l, int r, int k) {
    // 如果只有一个数，那这个数一定是第 k 小的
    if (l == r) return q[l];

    // 找中心做排序
    int x = q[l + r >> 1];
    int i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while (q[i] < x);
        do j--; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }

    // 左右两侧分而治之
    int sl = j - l + 1;
    if (k <= sl) {
        return quick_k_num(q, l, j, k); // 在左边继续找
    } else {
        return quick_k_num(q, j + 1, r, k - sl); // 在右边继续找
    }
}

int main() {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) scanf("%d", &q[i]);

    printf("%d", quick_k_num(q, 0, n - 1, k));

    return 0;
}
