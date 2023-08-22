/*
    @author Karry 
    @date on 2023/8/18.
    @comment Day 18 用并查集解决食物链问题，在 union set 的基础上开一个表示到根节点距离的数组，维护附加关系
*/

#include<iostream>

using namespace std;

const int N = 5e5 + 10;


/*
 * p[N] 表示并查集底层的树（存储节点 n 的父节点为 p[n]
 * d[N] 数组始终表示点 n 到其到父节点 p[n] 的距离 || 深刻理解 d数组的含义是理解本题的核心
 */
int p[N], d[N];


int find_root(int x) { // 找根节点 + 路径压缩 + 距离维护
    if (p[x] != x) {
        /*
         * 一定是先进行递归，因为递归不仅是求解根节点的过程，还是进行压缩的过程
         * 一方面，这样压缩后 x 父节点 p[x] 的父节点就是 root 了
         * 另一方面，d[p[x]] 所表示的就是父节点到根的距离了
         */
        int root = find_root(p[x]);

        d[x] += d[p[x]]; // x 到父节点的距离 = x 到的父节点的距离 + 父节点到其父节点（根）的距离 （先递归后算本质是一种自 root 向下算的方法，才是对的！）
        p[x] = root; // x 指向根

        // 可以看出此时 d[N] 仍然维护着 点 n 到其到父节点 p[n] 的距离，只不过此时 p[x] 为 root，因此也是 x 到根的距离
    }

    return p[x];
}

int main() {
    int n, m; // n 表示输入数的范围 | m 表示操作次数
    cin >> n >> m;

    for (int i = 1; i <= n; i++) p[i] = i; // 初始化并查集

    int false_res = 0; // 初始化假话的数量

    while (m--) {
        int op, x, y; // 操作符 和 操作数
        cin >> op >> x >> y;

        if (x > n || y > n) false_res++;
        else {
            int x_root = find_root(x); // x 所在树的根节点
            int y_root = find_root(y); // y 所在树的根节点

            if (op == 1) { // x y 为同类 判断
                if (x_root == y_root && (d[x] - d[y]) % 3 != 0) false_res++; // 两个节点在同一棵树上了，就说明这句话是判断，不满足同类条件=>是假话
                else if (x_root != y_root) { // 两个节点不在同一颗树上，就说明这句话不是判断，需要操作
                    p[x_root] = y_root; // 树的合并，将 x_root 合并到 y_root 下
                    d[x_root] = d[y] - d[x]; // 合并前 d[x_root] = 0，合并后需要满足 (d[x] + d[x_root] - d[y]) mod 3 == 0
                }
            } else if (op == 2) { // x 吃 y 判断
                // ！！！！ 注意 这个地方的判定条件不能写成 (d[x] - d[y]) % 3 != 1 因为二者之差可能为负数 ！！！！ //
                if (x_root == y_root && (d[x] - d[y] - 1) % 3 != 0) false_res++; // 两个节点在同一棵树上了，就说明这句话是判断，不满足同类条件=>是假话
                else if (x_root != y_root) { // 两个节点不在同一颗树上，就说明这句话不是判断，需要操作
                    p[x_root] = y_root; // 树的合并，将 x_root 合并到 y_root 下
                    d[x_root] = d[y] - d[x] + 1; // 合并前 d[x_root] = 0，合并后需要满足 (d[x] + d[x_root] - d[y]) mod 3 == 1
                }
            }

        }

    }

    cout << false_res << endl;
    return 0;
}