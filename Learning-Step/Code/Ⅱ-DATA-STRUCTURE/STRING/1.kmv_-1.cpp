/*
    @author Karry 
    @date on 2023/8/14.
    @comment 凌晨所做，发现自己的思路行不通，下标从 0 开始，记住下面的做法
*/
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000010;

int n, m;
char s[N], p[N];
int ne[N];

int main() {
    cin >> m >> p >> n >> s;

    ne[0] = -1;
    for (int i = 1, j = -1; i < m; i++) {
        while (j >= 0 && p[j + 1] != p[i]) j = ne[j];
        if (p[j + 1] == p[i]) j++;
        ne[i] = j;
    }

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

