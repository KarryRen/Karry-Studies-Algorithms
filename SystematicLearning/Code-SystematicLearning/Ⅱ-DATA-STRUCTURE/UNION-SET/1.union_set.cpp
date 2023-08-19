/*
    @author Karry 
    @date on 2023/8/17.
    @comment Day 17 并查集数据结构的应用 - 合并集合（很巧妙的优化思想，以后肯定也能用到）
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 1e5 + 10; // 数据范围
int p[N]; // 存储父节点的数组（以数组的形式来构建树）
int n, m;

// 找到数 x 的集合编号
int find_root(int x) {
    // 不进行优化（很简单）
//    while (x != p[x]) x = p[x];
//    return x;

    // 进行优化（路径压缩 - 采用递归的形式对 p[x] 进行修改）
    if (p[x] != x) p[x] = find_root(p[x]); // 如果 x 不是根节点，就让其父节点为根节点
    return p[x];
}

int main() {
    cin >> n >> m;

    // step 1. 初始化：让范围内的每一个点都单独成为一个集合 (每一个节点都是根节点)
    for (int i = 1; i <= n; i++) p[i] = i; // 范围是 [1, n]

    // step 2. 合并 or 查找
    string op;
    int a, b; // 两个操作数
    while (m--) {
        cin >> op >> a >> b;

        // 注意在合并与查找的过程中都可以进行路径压缩
        if (op == "M") p[find_root(a)] = find_root(b); // 其中一个数的根节点的父节点指向另一个树的根节点
        else if (op == "Q") {
            if (find_root(a) == find_root(b)) cout << "Yes" << endl; // 如果两个元素的根节点相同就输出 yes
            else cout << "No" << endl;
        } else cout << "wrong input !" << endl;
    }

    return 0;
}