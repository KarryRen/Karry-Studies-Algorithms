/*
    @author Karry 
    @date on 2023/8/16.
    @comment Day 16 最大异或对 MDP
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10, M = 31 * N; // N 是数的个数范围，M 表示 Trie 树的节点数范围（每个节点是 1 位，每个数的位数范围是 0 - 31）
int a[N]; // 输入的数组
int trie[M][2], idx; // MDP 问题的 trie 树，因为每个子节点只有可能是 0 or 1，idx 是节点标识

// 插入输入的数
void insert_trie(int x) {
    int p = 0; // 从根节点开始

    // 从高位到低位把数的每一位都扣出来
    for (int i = 30; i >= 0; i--) {
        int u = x >> i & 1; // 取出数的第 i 位
        if (trie[p][u] == 0) trie[p][u] = ++idx; // 将数的第 i 位插到 trie 树中
        p = trie[p][u]; // 访问到下一位
    }

    // 一个数就成功插入其中了
}

// 查找目前的 Trie 树中与 x 异或最大的树
int fine_trie(int x) {
    int p = 0, target_num = 0; // 从根节点开始，target_num 初始化为 0

    // 从高位到低位把数的每一位扣出来
    for (int i = 30; i >= 0; i--) {
        int u = x >> i & 1; // 取出数的第 i 位
        if (trie[p][!u] != 0) {
            p = trie[p][!u]; // 如果和该位不同的数存在（异或值更大）就往该方向移动
            target_num = target_num * 2 + !u; // 每移动一次算一次 num 值
        } else {
            p = trie[p][u]; // 否则只能退而求其次
            target_num = target_num * 2 + u; // 每移动一次算一次 num 值
        }
    }

    return target_num;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i]; // 输入数组

    // mdp
    int res = 0;
    for (int i = 0; i < n; i++) {
        insert_trie(a[i]); // 先插入
        res = max(res, a[i] ^ fine_trie(a[i])); // 再查找
    }

    cout << res;
}