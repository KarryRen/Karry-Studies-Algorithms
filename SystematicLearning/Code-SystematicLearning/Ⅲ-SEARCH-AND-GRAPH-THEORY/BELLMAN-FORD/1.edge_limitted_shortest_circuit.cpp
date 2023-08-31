/*
    @author Karry 
    @date on 2023/8/31.
    @comment Day 31. 寻找有负权边的有向图中在 k 条边的限制下的最短路径问题。一般只能采用 bf 算法进行求解
    @note 坚持了 31 天，就算拔牙也是至少刷一道题。现在基本保持每天一道题目 1 个小时学习 + 反思的时间，坚持下去！
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 510;
const int M = 1e5 + 10; // 点数的限制和边数的限制
int n, m, k; // n 个点；m 条边；在 k 条边限制下的最短路径
int dist[N], backup[N]; // dist 的还是 i 号点到起点的最短距离，backup 是为了防止串联出现对 dist 数组的备份数组，保留初始状态
struct Edge {
    // 存储边的结构体，表示 a => b 这条边的权重为 w
    int a, b, w;
} edge[M]; // 共有 m 条边
int ans; // 全局变量存储答案

// bf 算法，求解从 r 号点 到 t 号点在 k 条边限制下的最短路径
bool bellman_ford(int r, int t, int k) {
    // ---- step 1. 进行状态初始化 ---- //
    memset(dist, 0x3f, sizeof(dist));
    dist[r] = 0;

    // ---- step 2. 进行 k 次循环，表示最多走 k 条边 ---- //
    for (int i = 0; i < k; i++) {
        /*
         * 为了防止【串联】更新的发生必须要把 dist 中的值存储到 backup 中
         * 什么是串联问题 ？
         * 首先我们要明确 bf 算法有效的前提是每次更新 dist[b] 时 dist[a] 应该是进行本次外层循环是的值，而不是进行内层循环更新后的值
         * 举个例子 对于图 1 => 2 (1)；2 => 3(1)；1 => 3(3)
         * 设定 dist[1] = 0 后，会首先将 dist[2] 从正无穷更新为 1 此时如果直接用 dist 进行更新的话，dist[3] 会从正无穷更新为 1 + 1 = 2 这就发生了【串联】问题
         * 正确的解决方法，是将本次外层循环的值先 copy 到 backup 中也就是说 dist[2] 在进行更新时，始终参考的都是之前未更新点的值！
         * 对于这个例子本次外循环的值为 dist[1] = 0；dist[2] = 正无穷；dist[3] = 正无穷，将其 copy 到 backup 中
         * 这样在进行循环内的更新时 dist[1] = 0; dist[2] = min{正无穷，0 + 1}; dist[3] = min{正无穷，正无穷 + 1} = 正无穷
         */
        memcpy(backup, dist, sizeof(dist));
        for (int j = 0; j < m; j++) { // 遍历 n 条边
            int a = edge[j].a, b = edge[j].b, w = edge[j].w;
            dist[b] = min(dist[b], backup[a] + w);
        }
    }

    // ---- step 3. 进行结果判断 ---- //
    // 如果可能是正无穷那就说明到达不了。这个地方因为存在负权边，加以考虑数据范围，所以判断正无穷的方式是大于正无穷加负数后可能出现的下界
    if (dist[t] > 0x3f3f3f3f / 2) return false;
    else {
        ans = dist[t];
        return true;
    }
}

int main() {
    // ---- step 1. 初始化有向图 ---- //
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) { // 构建 m 条边
        int a, b, w;
        cin >> a >> b >> w;
        edge[i] = {a, b, w};
    }

    // ---- step 2. 使用 bellman ford 算法求解 1 号点到 n 号点在 k 条边限制下的最短路径 ---- //
    if (bellman_ford(1, n, k)) cout << ans;
    else cout << "impossible";

    return 0;
}