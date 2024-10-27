/*
 * @Time    : 2024/10/27 12:33
 * @Author  : Karry Ren
 * @Comment : The merge sort.
 * @LeetCode: 912
*/

#include<iostream>

using namespace std;

const int N = 1e6 + 10;
int n;
int q[N], tmp[N]; // using a temp array to store num

void merge_sort(int q[], int l, int r) {
    if (l >= r) return;

    // Step 1. get the mid
    int mid = l + r >> 1;

    // Step 2. process the detail question
    merge_sort(q, l, mid), merge_sort(q, mid + 1, r);

    // Step 3. do the operation
    int k = 0; // k is a temp number
    int i = l, j = mid + 1; // the i and j are pointers, separately.
    while (i <= mid && j <= r) {
        if (q[i] <= q[j]) {
            tmp[k++] = q[i++];
        } else {
            tmp[k++] = q[j++];
        }
    }
    // if there are some number not ready
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    for (i = l, j = 0; i <= r; i++, j++) q[i] = tmp[j];
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%d", &q[i]);

    merge_sort(q, 0, n - 1);

    for (int i = 0; i < n; i++) printf("%d ", q[i]);

    return 0;
}
