/*
    @author Karry 
    @date on 2023/8/28.
    @comment Day 28. 使用数组模拟队列完成拓扑排序
    @note 由于数组模拟队列中的数组能够存储很多的历史信息，因此可以不需要开多余的空间对数据进行存储
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 1e5 + 10;
int n, m; // n 个点 m 条边
int h[N], e[N], ne[N], idx; // 图
int d[N]; // 图中每个节点的状态
int q[N], hh, tt; // 数组模拟的队列

void add_edge(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

bool topo_sort() {
    hh = tt = 0; // 队列初始化

    for (int i = 1; i <= n; i++)
        if (d[i] == 0)
            q[tt++] = i; // 入度为 0 的点入队列

    while (hh < tt) { // 如果队列不为空
        int p = q[hh++]; // 将队头元素取出，同时队头元素出队列
        for (int i = h[p]; i != -1; i = ne[i]) {
            int j = e[i];
            d[j]--;
            if (d[j] == 0) q[tt++] = j; // 如果 j 号点的入度为 0，j 入队列
        }
    }

    return tt == n;
}

int main() {
    cin >> n >> m;

    memset(h, -1, sizeof(h));
    while (m--) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b);
        d[b]++;
    }

    if (topo_sort())
        for (int i = 0; i < n; i++)
            cout << q[i] << " "; // 入队的顺序就是拓扑排序（十分巧妙！）
    else cout << "-1";

    return 0;
}

