/*
    @author Karry
    @date on 2023/9/2.
    @comment Day 33. 使用 spfa 判断有向图中是否存在负环
    @note 直接暴力求解，多套一圈循环即可，十分 simple
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1e5 + 10; // 点数和变数的限制
int n, m; // n 个点，m 条边
int h[N], e[N], w[N], ne[N], idx; // 邻接表表示有向图
int dist[N], st[N]; // 常规两件套，dist 表示 i 号点到起点的最短距离；st 表示 i 号点的状态
int cnt[N]; // cnt 和 dist 一一对应，表示 i 号点到起点最短距离需要经历的路径长度
queue<int> q; // 存储待更新点的点号

// 邻接表加带权边操作
void add_edge(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// spfa 算法判断图中是否存在负环
bool spfa() {
    // 把所有可能的起点都来一次
    for (int r = 1; r <= n; r++) {
        // ---- step 1. 状态初始化 ---- //
        memset(dist, 0x3f, sizeof(dist));
        memset(cnt, 0, sizeof(cnt));
        dist[r] = 0;
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
                    cnt[j] = cnt[t] + 1; // 更新 cnt
                    if (cnt[j] >= n) return true;
                    if (!st[j]) { // 如果没在队列中才将其放入，否则不用 care
                        q.push(j);
                        st[j] = true;
                    }
                }
            }
        }

    }


    return false;
}

int main() {
    // ---- step 1. 初始化有向图 ---- //
    cin >> n >> m;
    memset(h, -1, sizeof(h));
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
    }

    // ---- step 2. spfa 图中是否存在负环 ---- //
    if (spfa()) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}
