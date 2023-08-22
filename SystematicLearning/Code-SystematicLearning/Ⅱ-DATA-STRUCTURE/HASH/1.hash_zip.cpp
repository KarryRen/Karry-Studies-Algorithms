/*
    @author Karry 
    @date on 2023/8/20.
    @comment Day 20 拉链法实现实现 hash 表
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 100003; // 大于 1e5 的第一个质数

int h[N]; // hash 表数组 （每个元素存储的是链表的表头）
int e[N], ne[N], idx; // 单个数组表示多维度链表（这个是很神奇的事情，只需要通过表头访问即可）

// 向 hash 表中插入元素（模仿在单链表表头插入）
void insert(int x) {
    // 将数映射到 0 ~ 10^5 上，之所以不能直接取 mod 是因为要防止负数出现
    int k = (x % N + N) % N;

    // 将数 x 进行插入链表头中
    e[idx] = x;
    ne[idx] = h[k]; // h[k] 标识的是 head
    h[k] = idx; // head 指向头 idx
    idx++; // idx 后移动
}

// 在 hash 表中找到数 x
bool find(int x) {
    // 先求出来映射值
    int k = (x % N + N) % N;

    // 从头开始在单链表中进行寻找
    for (int i = h[k]; i != -1; i = ne[i])
        if (e[i] == x) return true;
    return false;
}

int main() {
    int n;
    cin >> n;

    // 初始化哈希表。因为哈希表的每一个元素代表的是链表表头，所以初始化为 -1 就很自然了！
    memset(h, -1, sizeof(h));

    string op; // 操作符
    int x; // 操作数
    while (n--) {
        cin >> op >> x;
        if (op == "I") insert(x); // 插入头部的操作
        else if (op == "Q") {
            if (find(x)) cout << "Yes" << endl;
            else cout << "No" << endl;
        } else cout << "Wrong Input" << endl;
    }

    return 0;
}
