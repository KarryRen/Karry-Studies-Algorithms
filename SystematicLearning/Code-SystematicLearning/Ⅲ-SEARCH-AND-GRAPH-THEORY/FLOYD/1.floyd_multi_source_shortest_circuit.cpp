/*
    @author Karry 
    @date on 2023/9/3.
    @comment Day 34. Floyd 求解多源汇最短路径问题
    @note 这个算法写起来比较简单，其背后的原理是动态规划哈！现在先记住，后面再推导
*/

#include<iostream>

using namespace std;

const int N = 210, INF = 0x3f3f3f3f; // 定义点的数量和正无穷
int d[N][N]; // floyd 中最重要的数组，初始化的时候表示邻接矩阵存储图，经过 floyd 算法后 d[i][j] 就变成了点 i 到点 j 的最短距离
int n, m, q; // n 个点，m 条边，q 次询问

// floyd 算法求解多源最短路问题
void floyd() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); // base dp
}

int main() {
    cin >> n >> m >> q;

    // ---- step 1. 初始化图 ---- //
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            /*
             * 这个地方之所以没像 Dijkstra 那样直接把图中所有点都初始化为正无穷，是因为 d 在变换后的含义不再是图了
             * 而是两点之间的距离，所以需要提前把对角线初始化为 0
             */
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;
        }
    }

    // ---- step 2. 构造边 ---- //
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        d[a][b] = min(d[a][b], c);
    }

    // ---- step 3. 调用 floyd ---- //
    floyd();

    // ---- step 4. 进行 1 次询问 ---- //
    while (q--) {
        int r, t; // r 号点是起始点，t 号点是终点
        cin >> r >> t;
        // 经典无穷判断
        if (d[r][t] > INF / 2) cout << "impossible" << endl;
        else cout << d[r][t] << endl;
    }

    return 0;
}


