/*
 * @Time    : 2024/12/22 15:27
 * @Author  : Karry Ren
 * @Comment : The single linked list.
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10; // 数据范围定义

/*
 * 最为重要的四个定义
 * 1. head 表示名义上的“头”，是表示链表起始点的下标是多少（因为经历过增删，所以链表头的下标不一定是 0）
 *    head 的本质就是链表中逻辑上第一个节点的下标，如果没有节点，那就是 -1
 *    一个比较好理解的方式是，不断的 insert_to_head 相当于不断建头，尽管下标一直往后走，但是后面构建的始终是逻辑上链表的头
 *    所以更加具象的表示形式应该是 head 始终指向头部节点（在图上画成竖着的，而不是横着的）
 * 2. e[N] 指每一个节点的值是多少（通过下标访问）
 * 3. ne[N] 指每一个节点的下一指向的下标是多少（通过下标访问）
 * 4. idx 表示插入点的下标 （不断向前推进）
*/

int head, e[N], ne[N], idx;

// 链表初始化
void init_single_list() {
    head = -1; // 没有任何节点
    idx = 0; // 初始可以插入点的下标为 0
}

// 构建头节点 函数（x 为头节点的值）
void insert_to_head(int x) {
    e[idx] = x; // 构建这一节点的值
    ne[idx] = head; // 该节点指向原本的 head 节点
    head = idx; // head 标记该节点，表示此节点为链表的头
    idx++; // idx++ 操作的下标后移
}

// 将节点插入到【下标】为 k 的后面 函数（x 为该插入节点的值）
void insert_node(int k, int x) {
    e[idx] = x; // 始终是 idx 维护构建新的节点的下标
    ne[idx] = ne[k]; // 新节点的 ne 为下标为 k 的节点的 ne
    ne[k] = idx; // 下标为 k 的 ne 变为 idx
    idx++;
}

// 删除【下标】为 k 的节点后的的节点
void delete_node(int k) {
    ne[k] = ne[ne[k]]; // 下标为 k 的节点指向其原本指向的节点的下一个节点
    // idx 不需要做任何的操作，因为这是算法题目，不用考虑内存的维护
}

// 删除头节点
void delete_head_node() {
    head = ne[head]; // 类似于上述删除操作，只不过此处直接找到 head 即可，因为千万别忘了 head 标识的就是头节点的下标
}

int main() {
    int m; // 操作次数
    cin >> m;

    // - 初始化
    init_single_list();

    // - 完成操作
    while (m--) {
        char op; // 操作符
        int k, x; // 操作数

        cin >> op; // 输入操作符

        if (op == 'H') {
            // 构建链表头
            cin >> x; // 输入待插入的节点的值
            insert_to_head(x);
        } else if (op == 'I') {
            // 在第 k 个插入的节点后，插入新的节点
            cin >> k >> x; // k : 第 k 个插入的节点
            insert_node(k - 1, x); // 第 k 个插入的节点的下标为 k - 1
        } else if (op == 'D') {
            // 删除第 k 个插入的节点后面的节点
            cin >> k; // k : 第 k 个插入的节点
            if (k == 0) delete_head_node(); // 如果 k = 0 表示删除头节点
            else delete_node(k - 1); // k != 0 表示删除第 k 个插入的节点，其下标为 k - 1
        } else {
            cout << "wrong op !";
        }
    }

    // - 输出链表
    for (int i = head; i != -1; i = ne[i]) cout << e[i] << " ";
    cout << endl;

    return 0;
}