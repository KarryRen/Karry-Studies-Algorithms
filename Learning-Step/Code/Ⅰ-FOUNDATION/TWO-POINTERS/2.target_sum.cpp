/*
    @author Karry 
    @date on 2023/8/7.
    @Day 7 target sum
*/

#include<iostream>

using namespace std;

typedef long long LL; // because the boundary of the num in array is out of int. so we set long long
const int N = 1e5 + 10; // the boundary of the length
LL A[N], B[N];

int main() {
    int n, m;
    LL x;
    scanf("%d %d %lld", &n, &m, &x);

    for (int i = 0; i < n; i++) scanf("%lld", &A[i]);
    for (int i = 0; i < m; i++) scanf("%lld", &B[i]);

    for (int i = 0, j = m - 1; i < n; i++) {
        while (j >= 0 && A[i] + B[j] > x) j--; // j will never right move
        if (A[i] + B[j] == x) {
            printf("%d %d", i, j);
            break; // must break
        }
    }

    return 0;
}
