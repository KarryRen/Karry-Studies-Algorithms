/*
    @author Karry 
    @date on 2023/8/27.
    @comment Day 27. 将 bfs 应用到图的搜索中
    @note bfs 是有标准模版的，无非就是遍历形式会跟随数据存储的载体而改变
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

int n, m; // 从 1 号节点到 n 号节点； 总共有 m 条边
const int N = 1e5 + 10; // 数据范围
int h[N], e[N], ne[N], idx; // 因为这个地方说明了最多有 m 条边，所以不需要开点的二倍大小
queue<int> q; // 存储等待访问的点的队列，以完成状态转移
int dist[N]; // 存储 1 号点到 i 号点的最短距离（distance），顺带着辅助进行存储状态

// 往图中添加 a -> b 这条边 （一定要熟练背住！）
void add_edge(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// 从 u 号点开始搜索
int bfs(int u) {
    // ---- step 1. 配置初始状态 ---- //
    memset(dist, -1, sizeof(dist)); // 初始化 dist 数组，表示从 u 号点到所有点的最短距离都是 -1 这也说明每个点都还没被访问过
    dist[u] = 0; // 作为搜索的起点，u 号点到 u 号点的距离为 0
    q.push(u); // u 号点入队列，作为后续状态转移的抓手

    // ---- step 2. 按照套路开始一层层向下访问 ---- //
    while (q.size()) { // 只要队列不空说明还可以继续往下拓展
        int p = q.front(); // 取出队头元素 p 号顶点
        q.pop(); // 队头元素队列

        for (int i = h[p]; i != -1; i = ne[i]) { // 访问 p 号点所能到达的所有点
            int j = e[i]; // 取出其能到达顶点的编号 j （新状态）
            if (dist[j] == -1) { // 该顶点之前从来没有到达过
                dist[j] = dist[p] + 1; // u 到 j 号点的最近距离 = u 到 p 号点的最近距离 + 1
                q.push(j); // 将 j 号顶点放入队列，方便后续状态拓展
            }
        }
    }

    // ---- step 3. 返回最终结果 ---- //
    return dist[n]; // u 号点到 n 号点的距离，如果无法到达就是初始值 -1 （从来没有更新过）
}


int main() {
    cin >> n >> m;

    // ---- step 1. 输入 n 条边 ---- //
    memset(h, -1, sizeof(h)); // 所有的单链表头设定为 -1
    while (m--) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b); // add the edge a -> b;
    }

    // ---- step 2. 从 1 号点开始搜索即可 ---- //
    cout << bfs(1) << endl;

    return 0;
}
