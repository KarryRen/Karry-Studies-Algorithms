/*
    @author Karry 
    @date on 2023/8/5.
    @comment Day5
*/

#include<iostream>

using namespace std;

const int N = 1e3 + 10; // the boundary

int q[N][N], s[N][N]; // the raw array and the sum array

int main() {
    int n, m, t;

    scanf("%d %d %d", &n, &m, &t);

    // input the raw array
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &q[i][j]);

    // step 1. compute the sum array
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + q[i][j];

    // step 2. compute the result one by one
    while (t--) {
        int x1, y1, x2, y2;

        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        printf("%d\n", s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1]);
    }

    return 0;
}
