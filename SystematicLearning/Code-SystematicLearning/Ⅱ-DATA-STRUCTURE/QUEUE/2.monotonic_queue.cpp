/*
    @author Karry 
    @date on 2023/8/13.
    @comment Day 13 单调队列
*/

#include<iostream>

using namespace std;

const int N = 1e6;
int n, a[N];
int k; // window size
int q[N], hh, tt; // the queue and head tail

int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) cin >> a[i];

    // ---- get the minimize ---- //
    hh = tt = 0; // 初始化 queue
    for (int i = 0; i < n; i++) {
        // 从前往后扫描原数组

        // step 1. 先检查队头下标所代表的元素是否已经出窗口了，如果已经出窗口了，那队头就要出队列
        if (hh < tt && q[hh] < i - k + 1) hh++;
        // step 2. 对新元素进行判断，使之不打破单调性，一定要注意队尾元素是 q[tt- 1] ！！！
        while (hh < tt && a[i] < a[q[tt - 1]]) tt--;
        // step 3. 新元素的下标入队列
        q[tt++] = i;

        // 输出结果，只有在窗口大小后才会输出结果
        if (i + 1 >= k) cout << a[q[hh]] << " ";
    }

    cout << endl;

    // ---- get the maximize ---- //
    hh = tt = 0; // 初始化 queue
    for (int i = 0; i < n; i++) {
        // 从前往后扫描原数组

        // step 1. 先检查队头下标所代表的元素是否已经出窗口了，如果已经出窗口了，那队头就要出队列
        if (hh < tt && q[hh] < i - k + 1) hh++;
        // step 2. 对新元素进行判断，使之不打破单调性，一定要注意队尾元素是 q[tt- 1] ！！！
        while (hh < tt && a[i] > a[q[tt - 1]]) tt--;
        // step 3. 新元素的下标入队列
        q[tt++] = i;

        // 输出结果，只有在窗口大小后才会输出结果
        if (i + 1 >= k) cout << a[q[hh]] << " ";
    }

    return 0;
}
