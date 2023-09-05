/*
    @author Karry 
    @date on 2023/9/5.
    @comment Day 36
    @note 核心是选权最小的边，组合成最小生成树；时间复杂度比较低，能够处理点数较多的稠密图
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int N = 2e5 + 10; // 边的数量上限
int p[N]; // 并查集中的 p[N] 概念，表示点 i 指向的上一个节点
int n, m; // n 个点，m 条边
int res; // 全局变量存储最小生成树的权重之和
// 这个地方用一个边的结构体来封装边；因为后续需要用到排序，所以就不能用邻接矩阵或者邻接表了
struct Edge {
    int a, b, w;

    bool operator<(Edge &E) const { // 结构体符号重载
        return w < E.w;
    }
} edges[N];

// 并查集中的找点 + 压缩概念
int find_root(int x) {
    if (p[x] != x) p[x] = find_root(p[x]);
    return p[x];
}

// kruskal 算法求解最小生成树
int kruskal() {
    // ---- step 1. 对有向图中的边的权重排序 ---- //
    sort(edges, edges + m);

    // ---- step 2. 并查集的初始化 ---- //
    for (int i = 0; i < m; i++) p[i] = i;

    // ---- step 3. 从小到大遍历所有边，进行最小生成树的构造 ---- //
    int cnt_m = 0; // 记录当前放入了多少条边 （如果全部的边都遍历完了，但是放入的边数小于 n - 1 说明存在未被连通的点）
    for (int i = 0; i < m; i++) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w; // 取出该边对应的顶点和权重
        if (find_root(a) != find_root(b)) { // 如果二者不在一个集合中
            p[find_root(a)] = find_root(b); // 归到一个集合中
            cnt_m++;
            res += w;
        }
    }

    return cnt_m;
}

int main() {
    cin >> n >> m;

    // ---- step 1. 构建初始边的集合 ---- //
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i] = {a, b, c};
    }

    if (kruskal() < n - 1) cout << "impossible";
    else cout << res;

    return 0;
}