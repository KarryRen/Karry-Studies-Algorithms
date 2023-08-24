/*
    @author Karry 
    @date on 2023/8/22.
    @comment Day 22. 进入第三章搜索与图论（离散数学的重要意义所在）
*/

#include<iostream>

using namespace std;

const int N = 10; // 因为这道题最多只有可能有 7 个数字，稍微多开几个即可
int n;
int path[N]; // 存储路径的数组
int st[N]; // 存储 0 ~ n 之间每个数字状态的数组，被用着（在路径里面）就是 true 否则就是 false

// dfs function 从 u 开始寻找 （u 就是深度）
void dfs(int u) {
    if (u == n) { // u = n; 说明找到树的最后一级了，也就说明路径到头了
        for (int i = 0; i < n; i++) cout << path[i] << " "; // 输出路径结果
        cout << endl;
        return; // 返回上一级
    }

    for (int i = 1; i <= n; i++) // i 指针从前往后走直到遍历完整，可以保证前后顺序，数字从 1 开始所以 i 从 1 开始
        if (!st[i]) {
            path[u] = i; // 将数字 i 放到路径中
            st[i] = true; // 数字 i 已经被用过了
            dfs(u + 1); // 往下走一级
            st[i] = false; // 一旦跳出就需要进行向上回溯，刚被用过的数就自动弹出不再被用
        }

    // return; // 这个 return 是系统自带的，可以不写！

}

int main() {
    cin >> n;
    dfs(0); // 从 0 开始找 （树根部）
    return 0;
}