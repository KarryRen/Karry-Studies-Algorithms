/*
    @author Karry 
    @date on 2023/8/10.
    @comment Day 10 采用数组实现双链表（数据结构第一课）
*/


#include<iostream>
#include<string>

using namespace std;

const int N = 1e5 + 10; // 数据范围定义

/*
 * 最为重要的四个定义
 * 0. head 因为过于繁琐，在双链表实现的时候我们就不再采用单链表的方式进行处理（包括 tail）
 * 1. e[N] 指每一个节点的值是多少（通过下标访问）
 * 2. r[N] 指每一个节点的右指向节点的下标是多少（通过下标访问）
 * 3. l[N] 指每一个节点的左指向节点的下标是多少（通过下标访问）
 * 4. idx 表示插入点的下标 （不断向前推进）
*/
int e[N], r[N], l[N], idx;

// 初始化双链表
void init_double_linked_list() {
    // 和单链表初始化不同，双链表将下标 0 直接当作头节点， 下标 1 直接当作尾巴节点
    r[0] = 1; // 下标 0 的右节点为 1
    l[1] = 0; // 下标 1 的左节点为 0
    idx = 2; // 由于 0 和 1 已经被用，所以 init 之后 idx = 2
}

// 后续的功能实现，其实归结到底只有两个，就是在【下标】k 的节点右边插入一个点，以及删除【下标】为 k 的节点
// 1. 实现在【下标】 k 的节点右边插入一个节点
void insert_right_node(int k, int x) {
    e[idx] = x; // 构建一个新的节点
    l[idx] = k; // 新的节点左边应该指向下标 k
    r[idx] = r[k]; // 新的节点右边应该指向下标 k 的节点的右指向下标
    l[r[idx]] = idx; // idx 的右边的左指向应该是 idx
    r[l[idx]] = idx; // idx 的左边的右指向应该是 idx
    idx++; // idx 右移动
    // 当然上面还可以写成更为常规的写法
    // l[r[k]] = idx;
    // r[k] = idx;
    // 如果这么写的话，那这个地方的顺序必须要保证，否则就会出错
}

// 2. 实现删除【下标】k 的节点
void delete_node(int k) {
    // 无非就是直接将 k 节点架空
    r[l[k]] = r[k]; // k 左边的右边指向 k 的右边
    l[r[k]] = l[k]; // k 右边的左边指向 k 的左边
}

int main() {
    int m; // 操作的次数
    cin >> m;

    // - 初始化
    init_double_linked_list();

    // - 进行操作
    while (m--) {
        string op; // 操作符
        int k, x; // 操作数

        cin >> op;
        if (op == "R") {
            // 在双链表的最右边插入一个节点
            cin >> x;
            insert_right_node(l[1], x); // 无非就是在 【尾节点】的【左边点】的【右边】插入一个节点
        } else if (op == "L") {
            // 在双链表的最左边插入一个节点
            cin >> x;
            insert_right_node(0, x); // 无非就是在【头节点】的【右边】插入一个节点
        } else if (op == "IR") {
            // 在第 k 个插入的数右边插入一个数
            cin >> k >> x;
            insert_right_node(k + 1, x); // 一定要搞清楚第 k 个插入的数的下标是多少！(因为 idx 是从 2 开始的)
        } else if (op == "IL") {
            // 在第 k 个插入的数左边插入一个数
            cin >> k >> x;
            insert_right_node(l[k + 1], x); // 在第 k 个插入的数的左边的数插入
        } else if (op == "D") {
            // 删除第 k 个插入的数
            cin >> k;
            delete_node(k + 1); // 同样是搞清楚第 k 个插入的数的下标是多少
        } else {
            cout << "wrong op !";
        }
    }

    // - 输出链表
    for (int i = r[0]; i != 1; i = r[i]) cout << e[i] << " ";

    return 0;
}