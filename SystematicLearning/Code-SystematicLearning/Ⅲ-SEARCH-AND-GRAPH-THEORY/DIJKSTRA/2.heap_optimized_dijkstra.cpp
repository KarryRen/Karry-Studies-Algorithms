/*
    @author Karry 
    @date on 2023/8/30.
    @comment Day 30. 用堆优化的 Dijkstra 算法，其核心点在于优化了寻找每次不在 s 中，且到起点最短距离最小的点 （堆排序算法）
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1e6 + 10; // 点的数量扩大了一个量级
typedef pair<int, int> PII;
int n, m; // n 个点 m 条边
int h[N], e[N], w[N], ne[N], idx; // 带权重的有向图，其他的都一样，新加的 w[N] 表示权重
/*
 * dijkstra 中最核心的两个数组
 * dist 表示 i 号节点到起始节点的【最短距离】
 * st 表示 i 号节点是否已经确定了到起始节点的最短路径【就位点池】
 */
int dist[N], st[N];

// 有向图中带权重的加边 【 a -> b 权重为 c 】
void add_edge(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c; // 唯一标识权重的数组
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// 从 r 号点到 t 号点的最短距离
int dijkstra(int r, int t) {
    // 内置的小顶堆排序（每次插入一个新点后都自动进行堆调整）【按照 pair 的第一个元素按照从小到大进行排序】
    // 其存储的内容是 {当前该点到起始点（r 号点）的最短距离，点的编号}
    // 按照到起点的最短距离排序，我们就能得到此时不在就位点池中到达起点最短距离最小的点
    priority_queue<PII, vector<PII>, greater<PII>> heap;

    // ---- step 1. 初始化起始状态 ---- //
    memset(dist, 0x3f, sizeof(dist)); // 初始化所有点到起点的【最短距离】都是无穷大
    dist[r] = 0; // 起始点到起始点的【最短距离】为 0
    heap.push({0, r}); // 将 {0, r} 放入堆中

    // ---- step 2. 每次都选取不在就位点池中到达起点最短距离最小的点（会遍历 n 次） ---- //
    while (heap.size()) { // heap 为空就表示 n 个点选完了
        // --- step 2.1 寻找此时不在 s 中且 dist 最小的节点
        auto t = heap.top(); // 取到此时到达起点最短距离最小的点
        heap.pop(); // 该点出队列
        int distance = t.first, p = t.second; // 拿出该点到起点的最短距离以及该点的编号
        /*
         * 这里判断一下之前是不是已经将这个点判断过了 如果是就找下一个heap最短的边
         * 为什么会有重复的点被判断呢 比如说再加入后要更新相关距离的时候 有a->x  还有 b->x 当我们将 a,b都纳入s当中之后
         * 如果a,b到x 的距离都更新成功了 也就是意味着 我们将{dis1,x},{dis2,x}都加入了heap当中  假设有dis1>dis2
         * 那么就会先取出dis2 这个时候x还没有被纳入s当中 那么我们就可以将s纳入进来
         * 等到后续 取出 dis1的时候 就会因为 这个判断 而直接忽略这个{dis1,x} 而考虑其他边
         * 但是 事实上 如果不加这个判断也是可以 (这个判断其实就像是一个剪枝 对算法的一个小优化)
         * 因为 在取出{dis2,x}之后 我们会对x的邻接结点进行更新 这个时候的更新的结果一定要比 {dis2,x}要来的小
         * 那么后续的判断{dis1,x}相当于只是做了一遍无用功  并没有改变什么 (时间复杂度会过不去！！)
         * 作者：yxc
         * 链接：https://www.acwing.com/video/282/
         * 来源：AcWing
         * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
         */
        if (st[p]) continue; // 如果该点之前已经被取到过了就直接跳过
        st[p] = true; // 将该点选入【就位点池】

        // --- step 2.2 因为 s 发生了改变，基于新加入的点，更新 dist
        for (int i = h[p]; i != -1; i = ne[i]) { // 这个地方使用邻接表存储，就可以直接访问临边，不用遍历所有点了
            int j = e[i]; // 将 i 能到达的点的点号 j 取出来
            if (distance + w[i] < dist[j]) { // w[i] 的含义是 i -> j 的权重
                dist[j] = distance + w[i]; // 找到更短的到起点的距离，就对 dist 进行更新
                heap.push({dist[j], j}); // 该点可能是候选点，所以放入 heap 中
            }
        }

    }

    // ---- step 3. 将终点取出 ---- //
    if (dist[t] == 0x3f3f3f3f) return -1;
    return dist[t];
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

    // ---- step 2. 返回 1 号点到 n 号点的最短距离
    cout << dijkstra(1, n) << endl;

    return 0;
}
