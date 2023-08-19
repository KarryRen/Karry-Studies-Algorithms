/*
    @author Karry 
    @date on 2023/8/11.
    @comment Day 11 using array to make stack
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10; // the boundary of input m

/*
 * 对于栈来讲，只需要两个内容
 * 1. stk[N] 中存储所放入的值
 * 2. idx 记录栈顶的下标，idx 从 0 or 1 开始都可以，在这个地方为了保持和前面的链表一致，
 *    我选择从 0 开始（这样的话栈顶元素就需要是 idx - 1 了）也就是说 idx 标识的是栈顶下标 + 1
 */
int stk[N], idx;

// 初始化操作
void init() {
    idx = 0;
}

// push 操作
void push(int x) {
    stk[idx] = x;
    idx++;
}

// pop 操作
void pop() {
    idx--;
}

// 查找栈顶元素操作
int find_top() {
    return stk[idx - 1];
}

// 判断栈是否为空
void empty() {
    if (idx <= 0) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main() {
    int n;
    cin >> n;

    string op; // 操作符
    int x; // 操作

    // - 初始化 stk
    init();

    // - 进行操作
    while (n--) {
        cin >> op;
        if (op == "push") {
            cin >> x;
            push(x);
        } else if (op == "pop") {
            pop();
        } else if (op == "empty") {
            empty();
        } else if (op == "query") {
            cout << find_top() << endl;
        } else {
            cout << "wrong input" << endl;
        }
    }

    return 0;
}