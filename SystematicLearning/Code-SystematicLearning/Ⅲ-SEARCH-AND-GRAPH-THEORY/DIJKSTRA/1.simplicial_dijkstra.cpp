/*
    @author Karry 
    @date on 2023/8/29.
    @comment Day 29. 朴素的 Dijkstra 算法，时间复杂度 O(n^2)
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 510; // 数据范围，图中最多 500 个节点，开 510 简便边界处的思考
int n, m; // n 个点，m 条边
int g[N][N]; // 邻接矩阵表示图
/*
 * dijkstra 中最核心的两个数组
 * dist 表示 i 号节点到起始节点的【最短距离】
 * st 表示 i 号节点是否已经确定了到起始节点的最短路径【就位点池】
 */
int dist[N];
bool st[N];

// dijkstra 算法，求图中 r 号点（起点）到 t 号点（终点）的最短距离
int dijkstra(int r, int t) {
    // ---- step 1. 初始化起始状态 ---- //
    memset(dist, 0x3f, sizeof(dist)); // 初始化所有点到起点的【最短距离】都是无穷大
    dist[r] = 0; // 起始点到起始点的【最短距离】为 0

    // ---- step 2. 将 n 个点一个个地进行确定最短路径【放到就位点池中】 ---- //
    for (int i = 0; i < n; i++) { // i 只是计数功能，每一次都只能确定一个点，总共要确定 n 次
        // --- step 2.1 寻找此时不在 s 中且 dist 最小的节点
        int t = -1; // t 就是目标点号，初始为 -1 表示起点，以 -1 为一个起点标注
        for (int j = 1; j <= n; j++) // 对 1 ～ n 号点进行遍历寻找，遍历完成后确定一个点 t 这就是 i 循环中确定的唯一一个点，将其选入【就位点池】
            if (!st[j] && (t == -1 || dist[j] < dist[t])) // 遍历寻找的 j 号点必须还没有就位。
                /* 此处 t 的设置很精妙，必须展开说一下。这样做可以保证 t 的初始值都是第一个不在 s 中的点，这样的比较才意义
                 * 刚开始有个很天真的想法，那就是为什么不直接让 t = 1; 然后把 t == -1 这个条件直接去掉呢 ？
                 * 这样想就是忽略了前提条件，能够被比较的点一定都是不在 s 中的，如果你设置 t = 1，那么就都会进行一次和 1 号点的比较，这显然是矛盾的 */
                t = j;
        st[t] = true; // 将其选入【就位点池】

        // --- step 2.2 因为 s 发生了改变，基于新加入的点，更新 dist
        for (int j = 1; j <= n; j++) // 同样还是对 1 ～ n 号点进行遍历更新
            dist[j] = min(dist[j], dist[t] + g[t][j]); // j 号点到起点的距离至少可以有两种路 1. 直接到起点； 2. 先到 t 号点，再去起点
    }

    // ---- step 3. 将终点取出 ---- //
    if (dist[t] == 0x3f3f3f3f) return -1;
    return dist[t];
}

int main() {
    // ---- step 1. 构造图 ---- #
    memset(g, 0x3f, sizeof(g)); // 初始化邻接矩阵，让点与点之间的初始距离都是无穷大
    cin >> n >> m;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c); // 由于是求最短路问题，所以出现重边时，只用存下来最短的那条边
    }

    // ---- step 2. dijkstra 找到 n 号点到 1 号点的最短距离 ---- //
    cout << dijkstra(1, n) << endl;

    return 0;
}
