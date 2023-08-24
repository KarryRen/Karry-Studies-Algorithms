/*
    @author Karry 
    @date on 2023/8/23.
    @comment Day 23. n 皇后问题：全排列的过程中，进行条件检验（对角线判断）依据先验知识，每行只放一个，因此只用 care 列
*/

#include<iostream>

using namespace std;

const int N = 20; // 因为对角线是行数的 2n - 1 倍，所以开 2 倍肯定够了
int n;
char queen[N][N]; // n rows and n cols.
int col[N], dg[N], ndg[N]; // 标识列、正对角线和反对角线是否被用过了

// 和基本的 dfs 如出一辙，此处 u 标识期盼的第 u 行（从 0 开始）
void dfs_n_queen(int u) {
    if (u == n) { // 到了最后一行就把数组全部输出
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cout << queen[i][j];
            cout << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) { // 指针 i 始终前进
        if (!col[i] && !dg[u + i] && !ndg[u - i + n]) { // 如果列没被用过，正反对角线都没被用过，说明符合规则
            queen[u][i] = 'Q'; // 全排列赋值
            col[i] = dg[u + i] = ndg[u - i + n] = true; // 标识被用过了
            dfs_n_queen(u + 1); // 到达下一行
            col[i] = dg[u + i] = ndg[u - i + n] = false; // 回溯清空所有的状态
            queen[u][i] = '.'; // 回溯清空第 i 列的皇后
        }
    }
};

int main() {
    cin >> n;

    // 初始化 queen 数组
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            queen[i][j] = '.';

    // dfs 条件性全排列 解决 n_queen （从第 0 行开始走）
    dfs_n_queen(0);

    return 0;
}