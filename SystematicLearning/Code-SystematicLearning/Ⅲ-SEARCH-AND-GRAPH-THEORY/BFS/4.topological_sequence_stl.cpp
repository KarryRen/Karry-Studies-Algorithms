/*
    @author Karry 
    @date on 2023/8/28.
    @comment Day 28. 有向图的拓扑序列是一个重要性质，判断一个有向图是否存在拓扑序列进而就可以判断一个图中是否存在环
    @note 仍然贯穿 bfs 的思想，无非是修改了队每一个节点状态的表示方法，此处为每一个节点的入度。
          这段是直接用 stl 中的 queue 来写的 （较比数组写的话可能要麻烦些）
            - 采用一个 push_time 记录点入队列的次数，进而对是否完成遍历做判断
            - 再开一个 topo_s[] 数组保存拓扑序列
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1e5 + 10; // 数据范围
int n, m; // n 个点； m 条边
int h[N], e[N], ne[N], idx; // 模拟有向图的单链表
queue<int> q; // bfs 中的队列，存储后续可能被依次访问到的点
int push_num; // 记录总共 push 到队列的点的熟练
int d[N]; // 记录每一个节点状态的数组，此处其含义为点的入度
int topo_s[N], s_idx; // 最终的拓扑序列

// 添加一条 a => b 的边
void add_edge(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// 对图进行拓扑排序
bool topo_sort() {
    // ---- step 1. 让图中所有入度为 0 的点入队列 ---- //
    for (int i = 1; i <= n; i++) { // 对 1 ～ n 号点进行遍历（因为题目要求点的编号只能是 1 ～ n）
        if (d[i] == 0) {
            q.push(i); // 如果 i 号点的入度为 0 就让他入队列
            push_num++; // push 的次数 + 1
        }
    }

    // ---- step 2. 对图中所有的点进行 bfs 搜索 ---- //
    while (q.size()) {
        int p = q.front(); // 取出队头元素
        topo_s[s_idx++] = p; // 取队头元素的顺序就是 topo 顺序
        q.pop();

        for (int i = h[p]; i != -1; i = ne[i]) { // 对 i 号点所能到达的点进行遍历
            int j = e[i]; // 取出该 i 号点指向点的号
            d[j]--; // 该点的入度 -1 （逻辑上等价于删除 i -> j 这条边）
            if (d[j] == 0) { // 如果入度为 0，就放入队列
                q.push(j);
                push_num++;
            }
        }
    }

    // ---- step 3. 对 push num 进行判断 ---- //
    return push_num == n;
}

int main() {
    cin >> n >> m;

    // ---- step 1. 对图进行初始化 ---- //
    memset(h, -1, sizeof(h));
    while (m--) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b);
        d[b]++; // b 的入度 + 1
    }

    // ---- step 2. 进行拓扑排序 ---- //
    if (topo_sort())
        for (int i = 0; i < s_idx; i++)
            cout << topo_s[i] << " ";
    else cout << "-1";

    return 0;
}


