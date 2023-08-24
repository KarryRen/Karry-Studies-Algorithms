/*
    @author Karry 
    @date on 2023/8/24.
    @comment Day 24 BFS 算法实践 => 走迷宫 ｜ 核心在于用队列存储所有的可能点，每次都进行逐个访问，寻找最急的后续点
    @note 这一份是用 stl 中的 queue 实现
*/

#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

const int N = 110; // 因为迷宫的宽度最大为 100，多开 10 个是足够的
typedef pair<int, int> PLL; // 记录坐标的元素

int n, m; // 行高，列宽

// 表示迷宫的两个重要数组
int maze[N][N]; // 迷宫数组
int maze_st[N][N]; // 表示迷宫每个点状态（到起点的距离）的数组

// stl 中的队列：队列中的元素是点，所以需要设置点坐标的队列
queue<PLL> q;

// bfs 搜索，从 [0, 0] 点开始
int bfs() {
    memset(maze_st, -1, sizeof(maze_st)); // 初始化迷宫所有点的初始状态，刚开始所有点到起点的距离都是 -1

    // step 1. 从起点开始搜索
    q.push({0, 0}); // 起点入队列
    maze_st[0][0] = 0; // 迷宫起点的状态更新

    // step 2. 开始逐层搜索
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1}; // 两个一维数组组合称四个方向，0-上[-1, 0], 1-下[1, 0], 2-左[0, -1], 3-右[0, 1];
    while (q.size()) { // 只要队列不为空，就说明新的区域中有点还没有往下走
        auto p = q.front(); // 把队头元素（立足点）取出来
        q.pop(); // 队头元素出队列

        for (int i = 0; i < 4; i++) { // 走遍四个方向
            int x = p.first + dx[i], y = p.second + dy[i]; // 从立足点往四个方向走的坐标点 (x, y)

            // (x, y) 必须在迷宫范围内，该点还不是墙，且该点之前没有被访问过
            if (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && maze_st[x][y] == -1) {
                maze_st[x][y] = maze_st[p.first][p.second] + 1; // 修改该点的状态：该点到起点的距离 = 立足点到起点的距离 + 1
                q.push({x, y}); // 该点入队尾
            }
        }
    }

    return maze_st[n - 1][m - 1]; // 终点到起点的距离
}

int main() {
    cin >> n >> m;

    // 输入迷宫
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    // 进行 bfs 搜索
    cout << bfs() << endl;

    return 0;
}

