/*
    @author Karry 
    @date on 2023/8/13.
    @comment Day 13 单调栈降低时间复杂度
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10;

int n;
int stk[N], tt; // 构建起一个栈

int main() {
    cin >> n;

    // 根本不需要提前构建一个数组
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x; // 输入新元素的值

        // 只要栈顶的元素大于输入的元素，那该元素就没有任何的意义了，直接出去即可。
        while (tt - 1 >= 0 && stk[tt - 1] >= x) tt--;

        // 如果在栈中找到一个元素 < x 的，那么该栈顶元素就是第一个小于 x 的值 （栈是有序的）
        if (tt - 1 >= 0) cout << stk[tt - 1] << " ";
        else cout << "-1 ";

        // 让新元素成为栈顶
        stk[tt++] = x;
    }

    return 0;
}
