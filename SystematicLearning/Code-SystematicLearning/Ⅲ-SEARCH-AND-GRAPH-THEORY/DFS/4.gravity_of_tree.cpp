/*
    @author Karry 
    @date on 2023/8/26.
    @comment Day 26. 树的重心 对 bfs 进行深入理解，研究其在树中的核心应用
    @note 理解如何用单链表存储树
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 1e5 + 10, M = N * 2;
int n; // n 个顶点
int h[N]; // 存储树的每一个顶点，顶点同时也是每个单链表的表头
bool st[N]; // 存储每一个节点的使用状态
// 注意：因为顶点输入可能重复，因此链表大小要开到顶点数量的 2 倍
int e[M], ne[M], idx; // 单链表的三件套 （尽管形式上是单链表，但是逻辑上是多个链表共用这一个区间）

int ans = N; // 题解，在这设定为一个全局变量，便于对去掉每一个节点后得到的答案进行更新

// 在图中加一条 a -> b 的边 （类似与 hash 表的思路，底层就是在单链表表头插入数）
void add_edge(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// 此处 dfs 的抓手是返回以 u 这个顶点，为根节点的子树的节点总数（子树大小），这样就可以完成连通块大小的比较
int dfs(int u) {
    // ---- step 1. 修改节点的状态 ---- //
    st[u] = true; // 顶点 u 被使用过了

    // ---- step 2. 开始找该顶点为根节点的子树的节点总数 ---- //
    int sum = 1; // sum 存储的就是以该节点为根节点的子树大小，因为有个根节点，所以初始化为 1
    int res = 0; // res 表示的是去掉该节点后连通块大小的最大值
    for (int i = h[u]; i != -1; i = ne[i]) { // 对该节点所有的子节点进行遍历
        int s_point = e[i]; // 取出子顶点的值
        if (!st[s_point]) {
            int s = dfs(s_point); // 求该以子节点为根节点的子树大小 （这个地方用到递归的思想，也是此题使用 dfs 的核心所在）
            res = max(res, s); // 更新 res 的值，取到最大子树大小
            sum += s;  // 把子树的大小加到原顶点上
            // （这个地方在初始思考的时候，总觉得是把一棵子树的每个点重复算了一下，但仔细想一想 bfs 的过程中状态会改变，不会重复的！）
        }
    }

    // ---- step 3, 求该节点父节点所在子树的大小，并完成更新 ---- //
    res = max(res, n - sum); // 至此我们既得到了去掉该节点后每一个连通块大小的最大值

    // ---- step 4. 依据这个节点的结果，对总解答进行更新 ---- //
    ans = min(ans, res);

    return sum;
}

int main() {
    cin >> n;

    // ---- step 1. 构建无向树 ---- //
    memset(h, -1, sizeof(h)); // 初始化每一个单链表的表头为 -1

    for (int i = 0; i < n - 1; i++) { // 输入 n - 1 条边
        int a, b; // a <-> b
        cin >> a >> b;
        // 在 a 和 b 之间同时加上 a -> b 的边 和 b -> a 的边
        add_edge(a, b), add_edge(b, a);
    }

    // ---- step 2. 从起点开始 dfs 找答案，是在 dfs 的过程中对答案完成的更新 ---- //
    dfs(1); // 此处起点是 1

    // ---- step 3. 输出结果 ---- //
    cout << ans << endl;

    return 0;
}
