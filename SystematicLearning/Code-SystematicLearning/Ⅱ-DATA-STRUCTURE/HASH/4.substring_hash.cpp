/*
    @author Karry 
    @date on 2023/8/21.
    @comment Day 21 用字符串 hash 的方法解决找子串的问题（等效于 kmp 算法）
*/


#include<iostream>

using namespace std;

typedef unsigned long long ULL; // 用 ULL 这一数据类型，可以免去取余的过程
const int NS = 1e5 + 10, NP = 1e6 + 10;
const int P = 131; // 按照经验值进行设定
ULL h[NP], p[NP], h_s;
int n, m;
char str_s[NS], str_p[NP];

// 找到从 [l, r] 这个区间的子串对应的 hash 值
ULL find_str_hash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    scanf("%d%s", &n, str_s + 1); // 字符串下标从 1 开始，都选用这种输入方法
    scanf("%d%s", &m, str_p + 1); // 字符串下标从 1 开始，都选用这种输入方法

    // step 1. 求解模式串对应的 hash 表
    p[0] = 1; // p^0
    for (int i = 1; i <= m; i++) {
        p[i] = P * p[i - 1]; // p ^ i 直接存储到 p[i] 中，方便后续直接调用计算
        h[i] = h[i - 1] * P + str_p[i]; // 遍历前缀构造 hash 表
    }

    // step 2. 求解子串对应的 hash 值
    for (int i = 1; i <= n; i++) h_s += str_s[i] * p[n - i];

    // step 3. 遍历母串求解 O(n) 的时间复杂度
    for (int i = 1; i <= m - n + 1; i++) if (find_str_hash(i, i + n - 1) == h_s) printf("%d ", i - 1);

    return 0;
}
