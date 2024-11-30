/*
 * @Time    : 2024/11/30 22:36
 * @Author  : Karry Ren
 * @Comment : Do the sub-matrices difference.
 * @LeetCode: None
*/

#include<iostream>

using namespace std;

// define the boundary
const int N = 1010;

// define the raw array and difference array
int raw[N][N], dif[N][N];

// define the n rows, m cols and t times operations
int n, m, t;

void insert_dif(int x1, int y1, int x2, int y2, int c) {
    dif[x1][y1] += c;
    dif[x1][y2 + 1] -= c;
    dif[x2 + 1][y1] -= c;
    dif[x2 + 1][y2 + 1] += c;
}

int main() {
    scanf("%d %d %d", &n, &m, &t);

    // input the raw array
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &raw[i][j]);

    // get the difference array
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            insert_dif(i, j, i, j, raw[i][j]);

    // do t times operation
    while (t--) {
        int x1, y1, x2, y2, c;
        scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &c);
        insert_dif(x1, y1, x2, y2, c);
    }

    // get the raw array back
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // the same way as the prefix_sum
            raw[i][j] = raw[i - 1][j] + raw[i][j - 1] - raw[i - 1][j - 1] + dif[i][j];
            printf("%d ", raw[i][j]);
        }
        printf("\n");
    }

    return 0;
}

