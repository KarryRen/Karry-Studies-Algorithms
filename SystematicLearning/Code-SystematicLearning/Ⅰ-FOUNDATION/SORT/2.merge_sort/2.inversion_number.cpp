/*
 * @Time    : 2024/10/27 12:33
 * @Author  : Karry Ren
 * @Comment : The number of inversion.
 * @LeetCode: LCR 170
*/

#include<iostream>

using namespace std;

typedef long long LL; // because the result will boom the int, we should use the long-long to define the result

const int N = 1e6 + 10;
int n;
int q[N], tmp[N]; // as same as the merge sort

LL inversion_number(int q[], int l, int r) {
    if (l >= r) return 0;

    // Step 1. set mid
    int mid = l + r >> 1;

    // Step 2. separate
    LL res = inversion_number(q, l, mid) + inversion_number(q, mid + 1, r);

    // Step 3. do the operation
    int k = 0;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (q[i] <= q[j]) {
            tmp[k++] = q[i++];
        } else {
            tmp[k++] = q[j++];
            res += mid - i + 1;
        }
    }
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    for (i = l, j = 0; i <= r; i++, j++) q[i] = tmp[j];
    // 如果此处出现一个逆序的数，根据数组分区有序性（就是说前、后半区的数字都是有序的）
    // 因此如果不排序就得不到该结果，这就是采用归并排序的原因所在
    // 那么逆序对的数量就要考虑到前半区一旦出现一个，其后面的数字也都大于后半区的数字，进而得到这一个结果

    return res;

}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%d", &q[i]);

    printf("%ld", inversion_number(q, 0, n - 1));

    return 0;
}


