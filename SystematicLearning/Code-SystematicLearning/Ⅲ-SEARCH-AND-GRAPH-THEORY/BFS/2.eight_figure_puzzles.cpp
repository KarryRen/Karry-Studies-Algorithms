/*
    @author Karry 
    @date on 2023/8/25.
    @comment Day 25. 八字码问题，又一个典型的 bfs 找最短路径，通过这个题目，我们更加能 get 到 bfs 本质所在（由于走迷宫太简单，因此我们 code 的书写有些随意）
    @note bfs 的核心点有三个
        - 状态的存储
        - 状态的转移
        - 最短距离的存储
        以后所有的 bfs 相关问题都可以看着一个，堪称经典！
*/

#include<iostream>
#include<queue>
#include<algorithm>
#include<unordered_map>

using namespace std;

// 八字码问题的 dfs 搜索过程
int dfs(string start_st) {
    // ---- step 0. 数据结构的设定 ---- //
    string end_st = "12345678x"; // 设定好 bfs 寻找的最终状态
    queue<string> q; // 存储可能到达的临时状态的序列
    unordered_map<string, int> st_dist; // 记录下某状态到初始状态的距离

    // ---- step 1. 初始状态的赋值 ---- //
    st_dist[start_st] = 0; // 初始状态距离设定
    q.push(start_st); // 将初始状态放入队列中

    // ---- step 2. 从初始状态开始进行搜索 ---- //
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1}; // 同样用两个一维度数组标识可能搜索的方向
    while (q.size()) {
        auto now_st = q.front(); // 将临时状态队列的对头取出来，作为当前状态
        q.pop();

        // - 如果已经搜索到了终点状态，就直接返回该状态到起点状态的距离即可
        if (now_st == end_st) return st_dist[now_st];

        // - 否则就要老老实实地进行搜索
        int blank_idx = now_st.find('x'); // 先找到空白位置的 string 下标（一维）
        int blank_x = blank_idx / 3, blank_y = blank_idx % 3; // 将当前状态中空白所在的一维下标转化为二维坐标 x - 行, y - 列
        int now_dist = st_dist[now_st];
        for (int i = 0; i < 4; i++) {
            int new_x = blank_x + dx[i], new_y = blank_y + dy[i]; // 上下左右四个方向可能的新坐标点

            if (new_x >= 0 && new_x < 3 && new_y >= 0 && new_y < 3) {// 新坐标位置需要满足条件：在棋盘以内，如果满足就可以更新状态
                int new_blank_idx = new_x * 3 + new_y; // 得到新状态下空白的下标

                swap(now_st[blank_idx], now_st[new_blank_idx]); // 通过交换得到新的状态

                if (!st_dist.count(now_st)) { // 如果这个新状态之前没有被寻找到过，自然也就不会出现在状态记录表中（防止形成环）
                    st_dist[now_st] = now_dist + 1; // 更新新状态到初始状态的位置
                    q.push(now_st); // 将该状态入队列，以方便后续在此基础上继续搜索
                }

                swap(now_st[blank_idx], now_st[new_blank_idx]); // 还原到原本的状态，以实现往其他方向寻找
            }
        }
    }

    return -1;
}

int main() {
    // 输入初始状态 必须这么做才能消除空格
    char c[2];
    string start_st;
    for (int i = 0; i < 9; i++) {
        cin >> c;
        start_st += c;
    }

    // 从初始状态开始进行 bfs 搜索
    cout << dfs(start_st) << endl;

    return 0;
}