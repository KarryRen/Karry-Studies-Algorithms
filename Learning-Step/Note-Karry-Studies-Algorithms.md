# Karry Studies Algorithms

<center>Karry</center>



## Sort

### [Quick Sort]([785. 快速排序 - AcWing题库](https://www.acwing.com/problem/content/description/787/))

快排（时间复杂度 n logn）的核心思想是分而治之，主要步骤为：

```
设定数组 q 左右两边的下标为 l 和 r
Step 1. 确定分界点 x: 可以是最左 (q[l]) | 最右 (q[r]) | 中间 (q[(l + r)/2]) | 随机
Step 2. 调整区间: 保证分界点左边的数字都小于等于 x ，分界点右边的数都大于等于 x ， 分界点不一定是 x *难点*
Step 3. 递归处理左右两端
```

抓核心点（Step 2） — 如何优雅快速地调整区间

```
Way 1 : 比较暴力的方法，重新开两个数组
	1. 开两个数组 a[], b[], 找到分界点 x 
	2. 扫描一遍 q[ l ~ r ]
	   大于 x 放在 a 里面, 小于 x 放在 b 里面
	3. 将 a 和 b 依次放回 q 中

Way 2 : 优美的做法, 开两个指针
	0. 选好一个 x
	1. i 从 l 往右边走, 直至遇到比 x 大的数
	2. j 从 r 往左边走, 直至遇到比 x 小的数
	3. i 和 j 互换, i 右移一位, j 左移一位, 重复 1 - 2, 直至 i 和 j 相遇
```

[标准答案](https://www.acwing.com/solution/content/16777/) 核心难点在于边界问题（避免死循环情况）

```c++
#include<iostream>

using namespace std;

int N = 1e6 + 10;
int q[N];

void quick_sort(int q[], int l, int r){
    // 判别边界
    if (l >= r) return;
    
    // 分成子问题, 分成子问题切记 0, N 和 N, 0 这两种情况
    int x = q[l + r >> 1]; 
    // 如果后面以 j 为边界, 就需要下取整; 如果后面以 i 为边界就需要下取整。
    int i = l - 1;
    int j = r + 1;
    
    while (i < j) {
        do i ++; while (q[i] < x); // 不断往后移动
        do j --; while (q[j] > x); // 不断往前移动
        if(i < j) swap(q[i], q[j]);
    }
    
    // 递归解决子问题
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main(){
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) scanf("%d", &q[n]);
    
    quick_sort(q, 0, n - 1);
    
    for (int i = 0; i< n; i++) printf("%d ", q[n]);
}
```

### [第 K 个数](https://www.acwing.com/problem/content/788/)

快速选择，和上述快速选择一脉相承

```c++
#include<iostream>

using namespace std;

const int N = 1e5 + 10;
int n, k;
int q[N];

int quick_k_num(int q[], int l, int r, int k) {
	if (l == r) return q[l]; // 如果只有一个数，那这个数一定是第 k 小的

	int x = q[l + r >> 1];
	int i = l - 1, j = r + 1;

	while (i < j) {
		do i ++;
		while (q[i] < x);
		do j --;
		while (q[j] > x);
		if (i < j) swap(q[i], q[j]);
	}

	int sl = j - l + 1; // 左边数字的个数
	if (k <= sl) {
		return quick_k_num(q, l, j, k); // 在左边 
	} else {
		return quick_k_num(q, j + 1, r, k - sl); // 在右边 
	}
}

int main() {
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) scanf("%d", &q[i]);

	printf("%d", quick_k_num(q, 0, n - 1, k));
}
```

