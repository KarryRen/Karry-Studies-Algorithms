/*
    @author Karry 
    @date on 2023/9/7.
    @comment Day 38. 判断二分图的经典方法 （dfs 的应用）
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 100010, M = 200010; // 点数和边数的上限，因为是无向图所以有二倍关系

int n, m; // 点数 和 边数
int h[N], e[M], ne[M], idx; // 经典邻接表存储图
int color[N]; // 标识点是否被染色

// 邻接表存储无向图
void add_edge(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx ++ ;
}

// dfs 进行染色
bool dfs(int u, int c) {
    // ---- step 1. 对 u 号点。染上 c 颜色 ---- //
    color[u] = c;

    // ---- step 2. 访问 u 号点所能到达的所有点 ---- //
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i]; // 取出点的编号
        if (!color[j]) { // 如果该点没有被染色，那么就将其染为 3 - c
            if (!dfs(j, 3 - c)) return false;
        }
        else if (color[j] == c) return false; // 如果出现矛盾，说明不是二分图
    }

    return true;
}

int main() {
    // ---- step 1. 初始化无向图 ---- //
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m -- ) {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b), add_edge(b, a);
    }
    
    // ---- step 2. 进行染色并判断 ---- //
    bool flag = true;
    for (int i = 1; i <= n; i ++ ) {
        if (!color[i]) { // 如果该点没被染过色，就进行染色
            if (!dfs(i, 1)) { // 从 1 号颜色开始染色
                flag = false;
                break;
            }
        }
    }
    if (flag) cout << "Yes";
    else cout << "No";

    return 0;
}