/*
    @author Karry 
    @date on 2023/9/4.
    @comment Day 35. 最小生成树算法 1 prim 算法，完全参考 Dijkstra
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 510; // 边数上界
const int INF = 0x3f3f3f3f; // 正无穷
int g[N][N]; // 因为边的数量 > 点数^2 所以是稠密图因此采用邻接矩阵来求解
int dist[N], s[N]; // dist 指的不再是点 i 到起点的最短距离，而是点 i 到已经就位的点的集合的最短距离; s 表示已经就位的所有点
int n, m; // 点数和边数

// prim 算最短生成树
int prim() {
    memset(dist, 0x3f, sizeof(dist)); // 初始化 dist 数组
    int res = 0; // 最小生成树中路径的长度

    for (int i = 1; i <= n; i++) { // 计数器记录 n 次
        int t = -1; // t = -1 鉴别是否为第一个点，这个思路和 Dijkstra 是完全一样的，t 始终表示的是不在 s 中的第一个点！
        for (int j = 1; j <= n; j++)  // 从 1 号点开始遍历
            if (!s[j] && (t == -1 || dist[j] < dist[t])) // 求出来当前不在 s 中且距离 s 最近的点
                t = j;

        if (i != 1 && dist[t] == INF) return INF; // 出现了中断点，证明没有最小生成树 （排除第一次，这个地方是为了排除特殊的边界情况）

        s[t] = true; // 将点 t 放入 s 中
        if (i != 1) res += dist[t]; // res 中加上路径的长度 (第一次不用加)

        for (int j = 1; j <= n; j++) dist[j] = min(dist[j], g[t][j]); // 用新的加入的点 t 来更新 dist
    }

    return res;
}

int main() {
    cin >> n >> m;

    // ---- step 1. 初始化图 ---- //
    memset(g, 0x3f, sizeof(g));
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c); // 无向图的边的初始化，一是对称，二是是需要保留最小边
    }

    // ---- step 2. 求解最小生成树 ---- //
    int r = prim();

    // ---- step 3. 判断 ---- //
    if (r == INF) cout << "impossible";
    else cout << r;

    return 0;
}
