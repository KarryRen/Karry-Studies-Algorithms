/*
    @author Karry 
    @date on 2023/9/2.
    @comment Day 33. 使用 spfa 判断有向图中是否存在负环
    @note 当然，对于这个题而言，如果我们想要让所有的点都当起点，可以再在外面套一层循环，暴力解决，十分简单，但是下面这种方法更是 elegant，复杂度稍微低一点
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1e5 + 10; // 点数和边数的限制
int n, m; // n 个点，m 条边
int h[N], e[N], w[N], ne[N], idx; // 邻接表表示有向图
/*
 * spfa 判断负环三件套 这个地方 dist 的含义与之前的题目中完全不同了，这也是这道题的核心
 * dist 只是代表存在负边时的一种更新器，不再有任何距离的含义，只有遇到负边才有可能更新（因此初始化为 0 即可，没必要初始化为正无穷）
 * cnt 与 dit 一一对应，其表达的是在更新 dist 的时候走了多少条负边，如果负边的数量大于 n（所有边的数量肯定也大于 n 了）
 * st 含义不变
 */
int dist[N], cnt[N], st[N];
/*
 * 除了上面的理解方法，也可以用下面这位大佬的思路，这样 dist 的含义就是一脉相承的了 【参考该题下的第一条评论】
 * 我觉得可以这样理解：
 * 1. 构造一个虚拟节点 x，单向指向所有的节点，且到所有节点距离为0；
 * 2. 新图是否有负环等价于原始的图。
 * 3. dist数组一开始为 0，没有违背算法过程，可以理解为根据算法已经从 x 更新到了各个节点，接下来的代码就是顺理成章。
 * 所以 dist 数组从所有为0的状态开始是有对应意义的。就是先走一步。
 */
queue<int> q; // 存储待更新点的点号
int ans;

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
    // ---- step 1. 状态初始化 ---- //
    for (int i = 1; i <= n; i++) {
        q.push(i); // 把所有的点都放入队列，表示每个点都可以当起点
        st[i] = true;
        // dist[i] = xx; 完全不需要对 dist 进行任何的初始化，直接全部为 0
    }

    // ---- step 2. 围绕队列展开更新 ---- //
    while (q.size()) {
        int t = q.front(); // 取出之前有过更新的点，出队列 + 调状态
        q.pop();
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i]; // 取出 t 所能到达的点，只有这些点的 dist 才有可能被更新
            if (dist[j] > dist[t] + w[i]) { // 如果可以被 t 更新，才进行更新，注意只有 w[i] < 0 也就是负边出现的时候才有可能出现更新（变相只记录负边的数量）
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1; // 表示到达该点需要经历的负边数 = 到该点起点所需要经历的负边数 + 1
                if (cnt[j] >= n) return true;
                if (!st[j]) { // 如果没在队列中才将其放入，否则不用 care
                    q.push(j);
                    st[j] = true;
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