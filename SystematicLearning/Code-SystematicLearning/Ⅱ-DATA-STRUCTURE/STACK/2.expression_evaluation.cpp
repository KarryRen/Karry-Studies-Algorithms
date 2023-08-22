/*
    @author Karry 
    @date on 2023/8/11.
    @comment Day 11 表达式值的计算（采用栈进行求解）
*/

#include<iostream>
#include<cstring> // 后续会用到字符串
#include<stack> // 引入栈
#include<algorithm>
#include <unordered_map> // 存储运算符的优先级需要用 map 来表示

using namespace std;

/*
 * 两个最为重要的结构
 * 1. 操作数栈，存储所有的操作数
 * 2. 操作符栈，存储所有的操作符
 */
stack<int> num;
stack<char> op;

// 满足条件时的计算操作
void eval() {
    // 取出操作数栈栈顶的两个操作数 （注意后进先出的顺序）
    int b = num.top();
    num.pop();
    int a = num.top();
    num.pop();
    // 取出操作符栈栈顶一个操作符
    char c = op.top();
    op.pop();

    int x; // 运算结果（根据不同的运算）
    if (c == '+') x = a + b;
    else if (c == '-') x = a - b;
    else if (c == '*') x = a * b;
    else x = a / b;
    num.push(x); // 将运算结果压入 num 栈栈顶
}

int main() {
    // 定义操作符的优先级
    unordered_map<char, int> pr{{'+', 1},
                                {'-', 1},
                                {'*', 2},
                                {'/', 2}};

    // ---- step 1. 输入中缀表达式运算符 ---- //
    string str;
    cin >> str;

    // ---- step 2. 从左到右进行扫描 ---- //
    for (int i = 0; i < str.size(); i++) {
        // - 对扫描到的字符进行判断
        char c = str[i];

        if (isdigit(c)) {
            // case 1. 如果是数字那就需要不断的往后扫描，直至把数字全部扣出来
            int x = 0, j = i;
            while (j < str.size() && isdigit(str[j])) x = x * 10 + (str[j] - '0'), j++;
            // 该数字扣完后需要进行两个操作
            i = j - 1;   // 1. 扫描字符串的指针前移（移动到最后一个数字那）
            num.push(x); // 2. 将该数字压到数字栈中
        } else if (c == '(') {
            // case 2. 如果是左括号就直接压入操作符栈中
            op.push(c);
        } else if (c == ')') {
            // case 3. 如果是右括号，就需要进行计算操作，直至遇到左括号，然后将左括号弹出
            while (op.top() != '(') eval();
            op.pop();
        } else {
            // case 4. 正常的操作符 符合以下三个条件就进行计算操作，如果不符合就不做
            // - op 栈不为空
            // - op 的栈顶不是左括号
            // - 操作符的优先级小于等于操作符栈顶操作符的优先级
            while (op.size() && op.top() != '(' && pr[c] <= pr[op.top()]) eval();
            // 将该操作符放入操作符栈中
            op.push(c);
        }
    }

    // ---- step 3. 扫描完毕后，进行收尾工作 ---- //
    while (op.size()) eval();

    // ---- step 4. 输出计算结果 ---- //
    cout << num.top() << endl;

    return 0;
}
