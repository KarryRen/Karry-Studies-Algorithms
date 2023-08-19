/*
    @author Karry 
    @date on 2023/8/19.
    @comment Day 19 数组模拟堆（较难的堆，需要额外维护两个数组）
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1e5 + 10; // 数值范围
int heap[N], h_size; // 堆 和 堆的尾节点下标
int heap_idx_of_k[N], k_of_heap_idx[N]; // 相互映射的两个数组
int i_k; // 插入数的次数

// 复杂的交换维护 （这道问题的核心所在，始终维护着下标）
void heap_swap(int idx1, int idx2) {
    // 交换堆中的两个数，维护堆的正确性
    swap(heap[idx1], heap[idx2]);

    // 交换第 k 个数字对应的 idx
    swap(heap_idx_of_k[k_of_heap_idx[idx1]],
         heap_idx_of_k[k_of_heap_idx[idx2]]);

    // 交换 idx 对应的第 k 个数字
    swap(k_of_heap_idx[idx1], k_of_heap_idx[idx2]);
}

// 对堆中下标为 idx 的数进行 down 操作
void heap_down(int idx) {
    // 三个节点中的最小节点【下标】初始化为顶部节点
    int min_idx = idx;

    // 找出三个节点中的最小值下标
    if (idx * 2 <= h_size && heap[idx * 2] < heap[min_idx]) min_idx = idx * 2;
    if (idx * 2 + 1 <= h_size && heap[idx * 2 + 1] < heap[min_idx]) min_idx = idx * 2 + 1;

    // 如果顶部节点的值不是最小的，就要交换 + 继续往下走 （递归实现）
    if (min_idx != idx) {
        heap_swap(idx, min_idx);

        // 此时顶部节点对应数的下标变为了 min_idx， 之后继续进行 down 操作下去即可
        heap_down(min_idx);
    }
}

// 对堆中下标为 idx 的数组进行 up 操作
void heap_up(int idx) {
    // 父节点存在，并且父节点的值比当前节点的值大，那么就网上走 （循环实现）
    while (idx / 2 && heap[idx] < heap[idx / 2]) {
        heap_swap(idx, idx / 2); // 对二者进行交换
        idx /= 2;
    }
}

int main() {
    int n;
    cin >> n; // n 次操作

    string op; // 操作符
    int k, x; // 操作数

    while (n--) {
        cin >> op;
        if (op == "I") { // ---- 插入操作 ---- //
            i_k++;
            cin >> x;
            heap[++h_size] = x; // 插到尾部

            // 维护两个数组
            heap_idx_of_k[i_k] = h_size;
            k_of_heap_idx[h_size] = i_k;

            heap_up(h_size); // 尾部上浮

        } else if (op == "PM") { // ---- 输出最小值 ---- //
            cout << heap[1] << endl; // 输出堆的根部

        } else if (op == "DM") { // ---- 删除最小值 ---- //
            heap_swap(1, h_size);
            h_size--;
            heap_down(1);

        } else if (op == "D") { // ---- 删除第 k 个插入的数 ---- //
            cin >> k;

            /*
             * 这种写法一定是大错特错的，因为 heap_idx_of_k[k] 在交换后就变了 ！
             * 我们后续的 down 和 up 是针对原位置进行的
             * heap_swap(heap_idx_of_k[k], h_size);
             * h_size--;
             * heap_down(heap_idx_of_k[k]);
             * heap_up(heap_idx_of_k[k]);
            */

            // 因此一定要先找一个数组存储起来，保证位置不变
            int i = heap_idx_of_k[k];
            heap_swap(i, h_size);
            h_size--;
            heap_down(i), heap_up(i);

        } else if (op == "C") { // ---- 修改第 k 个插入的数 ---- //
            cin >> k >> x;
            /*
             * 这种写法是可以的
             * heap[heap_idx_of_k[k]] = x;
             * heap_down(heap_idx_of_k[k]);
             * heap_up(heap_idx_of_k[k]);
            */

            // 为了和上面对称，采用这种写法
            int i = heap_idx_of_k[k];
            heap[i] = x;
            heap_down(i), heap_up(i);

        } else cout << "Wrong Input !" << endl;
    }

    return 0;
}