/*
    @author Karry 
    @date on 2023/8/6.
    @comment the difference is actually the minus operation of prefix
*/

#include<iostream>

using namespace std;

// define the boundary
const int N = 1e6 + 10;
// define the raw array and the difference array
int raw[N], dif[N];
// define the length of array and the input times
int n, m;

void insert_dif(int l, int r, int c) {
    // the insert function : using raw array to construct the difference array
    dif[l] += c;
    dif[r + 1] -= c;
}

int main() {
    scanf("%d %d", &n, &m);

    // input the raw array
    for (int i = 1; i <= n; i++) scanf("%d", &raw[i]);

    // get the difference array
    for (int i = 1; i <= n; i++) insert_dif(i, i, raw[i]);

    // input the operation
    while (m--) {
        int l, r, c;
        scanf("%d %d %d", &l, &r, &c);
        insert_dif(l, r, c);
    }

    // get back the raw array
    for (int i = 1; i <= n; i++) {
        // the same way as the prefix_sum
        raw[i] = raw[i - 1] + dif[i];
        printf("%d ", raw[i]);
    }

    return 0;
}
