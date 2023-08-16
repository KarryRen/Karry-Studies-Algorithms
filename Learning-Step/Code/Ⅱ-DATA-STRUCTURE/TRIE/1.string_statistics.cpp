/*
    @author Karry 
    @date on 2023/8/15.
    @comment Day 15 用 trie 解决字符串统计问题（实质是 trie 树的插入和查询）
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 1e5 + 10; // 数据范围

int trie[N][26]; // trie 树 （一维表示节点 idx ，二维表示子节点字符）
int idx = 0; // 树节点标识，初始化为 0 表示根节点为 0
int cnt[N]; // 以某个节点为结尾的字符串的数量

// trie 树的插入操作
void insert_trie(string str) {
    int p = 0; // 从根节点开始查询

    // 遍历整个字符串
    for (int i = 0; str[i]; i++) {
        int u = str[i] - 'a'; // transfer 'a ~ z' to '0 ~ 25'
        if (trie[p][u] == 0) trie[p][u] = ++idx; // 如果不存在该子节点就构建一个（标识符为 idx）
        p = trie[p][u]; // 节点下移
    }

    // 到达终点后进行记录，以该节点为终点的字符串 + 1
    cnt[p]++;
}

// trie 树的查询操作，本质是找到字符串的路径，拿到字符串对应结尾节点的 idx （思路和插入完全一样）
int find_trie(string str) {
    int p = 0;

    for (int i = 0; str[i]; i++) {
        int u = str[i] - 'a';
        if (trie[p][u] == 0) return 0; // 说明根本不存在这条路径，当然也就不存在这个字符串了
        p = trie[p][u];
    }

    // 访问到终点
    return cnt[p];
}

int main() {
    int n;
    cin >> n;

    string op, str;
    while (n--) {
        cin >> op >> str;
        if (op == "I") insert_trie(str);
        if (op == "Q") cout << find_trie(str) << endl;
    }

    return 0;
}
