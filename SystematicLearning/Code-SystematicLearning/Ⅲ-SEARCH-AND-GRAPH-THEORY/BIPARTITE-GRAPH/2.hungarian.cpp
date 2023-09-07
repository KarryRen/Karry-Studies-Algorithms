/*
    @author Karry 
    @date on 2023/9/8.
    @comment Day 39. 匈牙利算法解决二分图的最大匹配问题
*/
#include<iostream>
#include<cstring>

using namespace std;

const int N = 510, M = 1e5 + 10; // 点数的上界和边数的上界
int n1, n2, m; // 集合 1（男生）中的点的数量，集合 2（女生）中的点的数量，边的数量
int h[N], e[M], ne[M], idx; // 常规的用邻接表存储图
int match[N]; // 集合 2（女生）中匹配集合 1（男生）的点号
bool st[N]; // 集合 2 （女生）是否被找过，避免重复查找
int res; // 结果：最大匹配边数

// 邻接表存储无向图加边
void add_edge(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx ++ ;
}

// 对集合 1 中的 r 号点进行匹配
bool find(int r){
  for(int i = h[r]; i != -1; i = ne[i]){ // 对 r 号点所能匹配到的点进行遍历
    int j = e[i]; // 找到匹配的点号
    if(!st[j]){ // 如果对于 r 来说 j 号点还没被找过
      st[j] = true; // 标记 j 点是 r 号点的目标点之一了，别的已经匹配的都不可以再寻找
      // 如果 j 号点从没匹配过，或者与之之前匹配的男生还可以找到其他的匹配点。那么就可以让 j 号点与 r 匹配
      if(match[j] == 0 || find(match[j])){
        match[j] = r;
        return true; 
      }
    }
  }  
  return false;
}

int main(){
  cin >> n1 >> n2 >> m;
  
  // ---- step 1. 初始化图 ---- //
  memset(h, -1, sizeof(h));
  while(m--) {
    int a, b;
    cin >> a >> b;
    add_edge(a, b); // 虽然是无向图，但是对于该匹配题目而言只需要添加 a => b 这样一条边
  }
  
  // ---- step 2. 遍历集合 1. 中的所有点，进行匹配 ---- //
  for(int i = 1; i <= n1; i++) { // 集合 1. 中 1 ～ n1 号点
    memset(st, false, sizeof(st)); // 对于 i 号点来说每个集合 2 都还没被匹配过
    if(find(i)) res ++;
  }
  
  cout << res << endl;
  
  return 0;
}