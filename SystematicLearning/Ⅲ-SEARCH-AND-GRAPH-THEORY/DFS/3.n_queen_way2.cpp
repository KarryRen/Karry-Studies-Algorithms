/*
    @author Karry 
    @date on 2023/8/23.
    @comment Day 23. n 皇后问题：全排列的过程中，进行条件检验（对角线判断）按照格子搜索，每一个格子往后移动
*/

#include<iostream>

using namespace std;

const int N = 20; // 因为对角线是行数的 2n - 1 倍，所以开 2 倍肯定够了
int n;
char queen[N][N]; // n rows and n cols.
int row[N], col[N], dg[N], ndg[N]; // 标识行、列、正对角线和反对角线是否被用过了

// 和基本的 dfs 如出一辙，此处 (x, y, n_q) 标识期盼的第 x 行, y 列, 皇后的数量为 n_q
void dfs_n_queen(int x, int y, int n_q) {

    if (y == n) y = 0, x++; // 列到结尾了，直接转移到行头

    if (x == n) { // 到了最后一行
        if (n_q == n) { // 并且皇后的数量为 n 了，就把皇后输出出来
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) cout << queen[i][j];
                cout << endl;
            }
            cout << endl;
        }
        return;
    }

    // 在该格子上不放皇后
    dfs_n_queen(x, y + 1, n_q);

    // 在该格子上放皇后
    if (!row[x] && !col[y] && !dg[x + y] && !ndg[x - y + n]) { // 符合规则
        queen[x][y] = 'Q'; // 全排列赋值
        row[x] = col[y] = dg[x + y] = ndg[x - y + n] = true; // 标识被用过了
        dfs_n_queen(x, y + 1, n_q + 1); // 到达下一个格子，且皇后数量 + 1
        row[x] = col[y] = dg[x + y] = ndg[x - y + n] = false; // 回溯清空所有的状态
        queen[x][y] = '.'; // 回溯清空第 i 列的皇后
    }
}


int main() {
    cin >> n;

    // 初始化 queen 数组
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            queen[i][j] = '.';

    // dfs 条件性全排列 解决 n_queen （从第 0 行开始走）
    dfs_n_queen(0, 0, 0);

    return 0;
}