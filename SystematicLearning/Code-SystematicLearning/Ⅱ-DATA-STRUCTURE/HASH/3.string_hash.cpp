/*
    @author Karry 
    @date on 2023/8/21.
    @comment Day 21. 字符串哈希算法，理解如何将字符串转存到一个散列表中，并借助此解决字符串相关问题
*/

#include<iostream>

using namespace std;

typedef unsigned long long ULL; // 用 ULL 这一数据类型，可以免去取余的过程
const int N = 1e5 + 10; // 注意这个地方所求的的 hash 值表证的含义不是下标，而是字符串对应值，因此 N 就是数组长度，千万别搞混了
const int P = 131; // 按照经验值进行设定
ULL h[N], p[N]; // 使用 p[N] 来存储 p^x 次方(p[x] = p^x)，进而方便运算
char str[N];

// 找到从 [l, r] 这个区间的子串对应的 hash 值
ULL find_str_hash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    int n, m;

    scanf("%d%d%s", &n, &m, str + 1); // 字符串下标从 1 开始，都选用这种输入方法

    p[0] = 1; // p^0
    for (int i = 1; i <= n; i++) {
        p[i] = P * p[i - 1]; // p ^ i 直接存储到 p[i] 中，方便后续直接调用计算
        h[i] = h[i - 1] * P + str[i]; // 遍历前缀构造 hash 表
    }

    int l1, r1, l2, r2;
    while (m--) {
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if (find_str_hash(l1, r1) == find_str_hash(l2, r2)) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}
