/*
    @author Karry 
    @date on 2023/8/14.
    @comment 凌晨所做，发现自己的思路行不通，下标从 0 开始，记住下面的做法
*/
#include <iostream>

using namespace std;

const int N = 1000010;

int n, m;
char s[N], p[N];
int ne[N];

int main() {
    cin >> m >> p >> n >> s;

    // step 1 求解 next 数组
    ne[0] = -1; // 因为子串开头有着自己的特殊性，必须要定义成 -1，就算后面的 next[j] 名义上是指第下标 0，实质上也是 0
    // 这样就可以将实际上的开头和 next[j] 指向的开头区分开，就可以跳出循环了！
    for (int i = 1, j = -1; i < m; i++) {
        while (j >= 0 && p[j + 1] != p[i]) j = ne[j];
        if (p[j + 1] == p[i]) j++;
        ne[i] = j;
    }

    // step 2 使用 next 数组进行求解
    for (int i = 0, j = -1; i < n; i++) {
        while (j != -1 && s[i] != p[j + 1]) j = ne[j];
        if (s[i] == p[j + 1]) j++;
        if (j == m - 1) {
            cout << i - j << ' ';
            j = ne[j];
        }
    }

    return 0;
}

