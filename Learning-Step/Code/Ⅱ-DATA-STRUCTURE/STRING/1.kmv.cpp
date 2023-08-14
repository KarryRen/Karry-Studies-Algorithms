/*
    @author Karry 
    @date on 2023/8/14.
    @comment Day 14 kmv for string
*/

#include<iostream>

using namespace std;

const int N = 1e6 + 10;


char str_s[N], str_p[N]; // 定义 子串 和 母串
int n, m; // 子串和母串的长度
int kmv_next[N]; // KMP 算法最为关键的 kmv_next 数组，存储下标

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> str_s[i]; // 输入子串，下标从 0 开始
    cin >> m;
    for (int i = 0; i < m; i++) cin >> str_p[i]; // 输入母串，下标从 0 开始

    // step 1 求解子串的 kmv_next 数组，定义：str_s[0, kmv_next[j]] = str[j - kmv_next[j] + 1 , j], 注意 j != next[j] (aaaa 前后缀是要掐头去尾的)
    kmv_next[0] = 0; // 第一个元素的 kmv_next 设置为 0
    for (int i = 1, j = 0; i < n; i++) { // i 从 1 开始
        while (j != 0 && str_s[i] != str_s[j]) { // 不匹配就回退
            if (kmv_next[j - 1] != 0) j = kmv_next[j - 1] + 1; // 这个地方就陷入死局了 比如 aabaaaa
//            else if (str_s[j - 1] == str_s[0] && str_p[i] == str_s[1]) j = 1;
            else j = 0;
        }

        if (str_s[i] == str_s[j]) j++; // 如果匹配，最长前缀向后延长

        if (j != 0) kmv_next[i] = j - 1;
        else kmv_next[i] = 0; // 直到上述操作完毕，既可以对 kmv_next 进行赋值

        cout << kmv_next[i] << " ";
        // 母串指针后移一位
    }
    cout << endl;
    // step 2 使用 kmv_next 完成 kmv
    for (int i = 0, j = 0; i < m; i++) { // i 从 0 开始遍历
        while (j != 0 && str_p[i] != str_s[j]) { // 不匹配就回退
            if (kmv_next[j - 1] != 0) j = kmv_next[j - 1] + 1; // 不在最前面的情况
            else if (str_s[j - 1] == str_s[0] && str_p[i] == str_s[1]) j = 1;
            else j = 0;
        }

        if (str_p[i] == str_s[j]) j++; // 子母串匹配，子串就向后移动

        if (j == n) {
            cout << i - n + 1 << " ";// 子串到了末尾，输出匹配点
            if (kmv_next[j - 1] == 0) j = 0;
            else j = kmv_next[j - 1] + 1;
        }

        // 母串指针后移一位
    }

    return 0;
}