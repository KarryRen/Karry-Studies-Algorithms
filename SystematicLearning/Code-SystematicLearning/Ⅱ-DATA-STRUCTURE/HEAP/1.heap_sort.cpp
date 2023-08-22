/*
    @author Karry 
    @date on 2023/8/19.
    @comment Day 19 堆排序（使用堆结构的特性来进行数组的排序）
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1e5 + 10; // 数值范围
int heap[N], h_size; // 堆 和 堆的尾节点下标

// 对堆中下标为 idx 的数进行 down 操作
void heap_down(int idx) {
    // 三个节点中的最小节点【下标】初始化为顶部节点
    int min_idx = idx;

    // 找出三个节点中的最小值下标
    if (idx * 2 <= h_size && heap[idx * 2] < heap[min_idx]) min_idx = idx * 2;
    if (idx * 2 + 1 <= h_size && heap[idx * 2 + 1] < heap[min_idx]) min_idx = idx * 2 + 1;

    // 如果顶部节点的值不是最小的，就要交换 + 继续往下走
    if (min_idx != idx) {
        swap(heap[idx], heap[min_idx]);
        // 此时顶部节点对应数的下标变为了 min_idx， 之后继续进行 down 操作下去即可
        heap_down(min_idx);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> heap[i]; // 输入数组

    // ---- step 1 构建初始堆 ---- //
    h_size = n; // 尾节点下标就是数字个数
    for (int i = h_size / 2; i; i--) heap_down(i); // 初始堆构建算法

    // ---- step 2 使用取值和删值操作求出排序 ---- //
    while (m--) {
        cout << heap[1] << " "; // 每次都输出根节点的值（当前的最小值）
        // 三步操作实现删除最小值
        heap[1] = heap[h_size];
        h_size--;
        heap_down(1);
    }

    return 0;
}