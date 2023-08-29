/*
    @author Karry 
    @date on 2023/8/24.
    @comment Day 24 BFS 算法实践 => 走迷宫 ｜ 核心在于用队列存储所有的可能点，每次都进行逐个访问，寻找最急的后续点
    @note 这一份是用数组模拟队列
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 110; // 因为迷宫的宽度最大为 100，多开 10 个是足够的
typedef pair<int, int> PLL; // 记录坐标的元素

int n, m; // 行高，列宽

// 表示迷宫的两个重要数组
int maze[N][N]; // 迷宫数组
int maze_dist[N][N]; // 表示迷宫每个点到起点的距离 (distance) 的数组

// 数组模拟的队列：队列中的元素是点，所以需要设置点坐标的队列
PLL q[N * N];
int hh, tt;

// bfs 搜索，从 [0, 0] 点开始，如果要从其他点开始也是很容易的
int bfs() {
    hh = 0, tt = 0; // 初始化队列为空
    memset(maze_dist, -1, sizeof(maze_dist)); // 初始化迷宫所有点的初始状态，刚开始所有点到起点的距离都是 -1

    // step 1. 从起点开始搜索
    q[tt++] = {0, 0}; // 起点入队列
    maze_dist[0][0] = 0; // 迷宫起点的状态更新 （初始距离设定）

    // step 2. 开始逐层搜索
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1}; // 两个一维数组组合称四个方向，0-上[-1, 0], 1-下[1, 0], 2-左[0, -1], 3-右[0, 1];
    while (hh < tt) { // 只要队列不为空，就说明新的区域中有点还没有往下走
        auto p = q[hh++]; // 把队头元素（立足点）取出来，可能转移的状态

        for (int i = 0; i < 4; i++) { // 走遍四个方向
            int x = p.first + dx[i], y = p.second + dy[i]; // 从立足点往四个方向走的坐标点 (x, y)

            // 新状态点 (x, y) 必须满足条件：在迷宫范围内，该点还不是墙，且该点之前没有被访问过
            if (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && maze_dist[x][y] == -1) {
                maze_dist[x][y] = maze_dist[p.first][p.second] + 1; // 该点到起点的距离 = 立足点到起点的距离 + 1
                q[tt++] = {x, y}; // 该点入队尾
            }
        }
    }

    return maze_dist[n - 1][m - 1]; // 终点到起点的距离
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

