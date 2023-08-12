/*
    @author Karry 
    @date on 2023/8/12.
    @comment Day 12 using array to do the queue
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10;

/*
 * 对于队列而言需要维护三个内容
 * 1. q[N] 用于存储队列中的值
 * 2. hh 表示头指针，表示队头（可以输出的地方）初始化为 0
 * 3. tt 表示尾指针，表示队尾（可以输入的地方）初始化为 0 （当然也可以初始化为 -1，那样访问队尾就不用减 1 了）
 *    但是为了和之前的链表以及栈保持一致，我在此处还是将 tt 初始化为了 0
 */

int q[N], hh, tt;

// 初始化函数
void init() {
    hh = 0;
    tt = 0;
}

// 向队尾插入一个数
void push(int x) {
    q[tt] = x; // 向队尾插入该数
    tt++; // 队尾指针后移动，因此可以看到 tt 的值是【队尾元素下标 + 1】，而不是队尾元素下标
}

// 从队头弹出一个数
void pop() {
    hh++; // 头指针只需要向后移动一个即可，因此可以看到 hh 的值就是队头元素的下标
    // 这个地方和链表一样不需要考虑空间的维护,实际上只有 stack 能充分利用数组的空间，只要有两个指针，就都不可能充分利用。
}

// 判断是否为空
void empty() {
    // 这个地方是否能取到等号也是和指针的初始化有关，一定要注意判别
    if (hh < tt) cout << "NO" << endl;
    else cout << "YES" << endl;
}

// 查询队头元素
void find_head() {
    cout << q[hh] << endl;
}

int main() {
    int m;
    cin >> m;

    // - 进行初始化
    init();

    // - 进行详细的操作
    string op; // 定义操作符
    int x; // 定义操作数
    while (m--) {
        cin >> op;
        if (op == "push") {
            cin >> x;
            push(x);
        } else if (op == "pop") {
            pop();
        } else if (op == "query") {
            find_head();
        } else if (op == "empty") {
            empty();
        } else {
            cout << "wrong input !" << endl;
        }
    }

    return 0;
}