/*
    @author Karry 
    @date on 2023/9/3.
    @comment Day 34. spfa 解决多源最短路径问题
    @note 直接把 spfa 拿过来，但是这样搞肯定会比较慢，对于这个题目而言是会超时的
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1e5 + 10; // 点数和变数的限制
int n, m, k; // n 个点，m 条边
int h[N], e[N], w[N], ne[N], idx; // 邻接表表示有向图
int dist[N], st[N]; // 常规两件套，dist 表示 i 号点到起点的最短距离；st 表示 i 号点的状态
int ans;

// 邻接表加带权边操作
void add_edge(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// spfa 算法从起点 r 号点到终点 t 号点的最短路径
bool spfa(int r, int t) {
    // ---- step 1. 状态初始化 ---- //
    memset(dist, 0x3f, sizeof(dist));
    dist[r] = 0;

    queue<int> q; // 存储待更新点的点号
    q.push(r);
    st[r] = true;

    // ---- step 2. 围绕队列展开更新 ---- //
    while (q.size()) {
        int t = q.front(); // 取出之前有过更新的点，出队列 + 调状态
        q.pop();
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i]; // 取出 t 所能到达的点，只有这些点的 dist 才有可能被更新
            if (dist[j] > dist[t] + w[i]) { // 如果可以被 t 更新，才进行更新
                dist[j] = dist[t] + w[i];
                if (!st[j]) { // 如果没在队列中才将其放入，否则不用 care
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    // ---- step 3. 对终点编号做出判断 ---- //
    if (dist[t] > 0x3f3f3f3f / 2) return false;
    else {
        ans = dist[t];
        return true;
    }
}

int main() {
    cin >> n >> m >> k;

    // ---- step 1. 初始化有向图 ---- //
    memset(h, -1, sizeof(h));
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
    }

    // ---- step 2. spfa 寻找最短路径 k times ---- //
    while (k--) {
        memset(dist, 0, sizeof(dist)); // dist 初始化 （每次查询的时候都必须是全新状态）
        memset(st, false, sizeof(st)); // st 初始化 （每次查询的时候点都没有被用过）

        int r, t;
        cin >> r >> t; // 输入起点和终点

        if (!spfa(r, t)) cout << "impossible" << endl;
        else cout << ans << endl;
    }


    return 0;
}
