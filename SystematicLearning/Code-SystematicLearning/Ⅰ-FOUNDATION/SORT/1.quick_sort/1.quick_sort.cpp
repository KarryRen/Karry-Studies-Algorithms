/*
 * @Time    : 2024/10/27 11:44
 * @Author  : Karry Ren
 * @Comment : The quick sort.
 * @LeetCode: 912
*/

#include<iostream>

using namespace std;

const int N = 1e6 + 10;
int n;
int q[N];

void quick_sort(int q[], int l, int r) {
    // 边界条件
    if (l >= r) return;

    // 分成子问题, 分成子问题切忌 0, N 和 N, 0 这两种情况
    // 此处的 x 就是一个 pivot
    // 注意此处是取了一个数字, 而不是下标, 这是和归并的本质区别
    int x = q[l + r >> 1];
    int i = l - 1;
    int j = r + 1;

    // 移动交换
    while (i < j) {
        do i++; while (q[i] < x); // 不断往后移动
        do j--; while (q[j] > x); // 不断往前移动
        if (i < j) swap(q[i], q[j]);
    }

    // 递归解决子问题
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%d", &q[i]);

    quick_sort(q, 0, n - 1);

    for (int i = 0; i < n; i++) printf("%d ", q[i]);

    return 0;
}
