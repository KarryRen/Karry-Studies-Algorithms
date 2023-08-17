/*
    @author Karry 
    @date on 2023/8/17.
    @comment Day 17 在 union set 的基础上增加一个数集合元素个数的操作
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 1e5 + 10;
int p[N], cnt_points[N]; // 增加了一个 cnt_points 数组来维护根节点所在集合的节点数量

int find_root(int x) {
    if (x != p[x]) p[x] = find_root(p[x]);
    return p[x];
}

int main() {
    int n, m;
    cin >> n >> m;

    // step 1. 初始化 union set
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        cnt_points[i] = 1;
    }

    // step 2.
    string op;
    int a, b; // 两个操作数
    while (m--) {
        cin >> op;
        if (op == "C") {
            // 集合合并
            cin >> a >> b;
            if (find_root(a) != find_root(b)) { // 如果已经在同一个集合中了，那就直接跳过即可
                // 注意这个地方的顺序，一定要先加，然后再修改树的连接
                cnt_points[find_root(b)] += cnt_points[find_root(a)]; // 元素个数的变化
                p[find_root(a)] = find_root(b); // 根节点变化
            }
        } else if (op == "Q1") {
            // 查询两个节点是否在同一个树内
            cin >> a >> b;
            if (find_root(a) == find_root(b)) cout << "Yes" << endl;
            else cout << "No" << endl;
        } else if (op == "Q2") {
            // 查询节点所在集合元素的个数
            cin >> a;
            cout << cnt_points[find_root(a)] << endl;
        } else cout << "wrong input !";
    }

    return 0;
}