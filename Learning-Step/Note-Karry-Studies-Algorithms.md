# Karry Studies Algorithms

<center>Karry</center>

学好模板，直接使用

## Foundation

### Sort

> [十大经典排序算法](https://blog.csdn.net/qq_35344198/article/details/106857042)

#### [Quick Sort](https://www.acwing.com/problem/content/description/787/)

快排（时间复杂度 $n log_2n$）的核心思想是`分治`，主要步骤为：

```
设定数组 q 左右两边的下标为 l 和 r
Step 1. 确定分界点 x: 可以是最左 (q[l]) | 最右 (q[r]) | 中间 (q[(l + r)/2]) | 随机 < 是数值 >
Step 2. 调整区间: 保证分界点左边的数字都小于等于 x ，分界点右边的数都大于等于 x ， 分界点不一定是 x *难点*
Step 3. 递归处理左右两端
```

`抓核心点`（Step 2） — 如何优雅快速地调整区间

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

[解析](https://www.acwing.com/solution/content/16777/) 核心难点在于边界问题（避免死循环情况）

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
    
    return 0;
}
```

#### [第 K 个数 (Quick Select)](https://www.acwing.com/problem/content/788/)

快速选择，和上述快速选择一脉相承，是快速排序算法的一种应用

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
    
    return 0;
}
```

#### [Merge Sort](https://www.acwing.com/problem/content/789/)

归并排序（时间复杂度 $nlog_2n$），同样是`分治`的思想，主要步骤如下：

```
设定数组 q 左右两边的下标为 l 和 r
Step 1. 确定分界点 mid = ( l + r ) / 2 < 是下标 >
Step 2. 递归排左右两边
Step 3. 将排好的归并起来 *重点*
```

`实现归并`：具体实现方法为`双指针`，两个有序的数组分别设置一个指针不断往后跑。归并排序是稳定的。

> 稳定的概念：相同的数排序后相对位置是否发生改变

[解析](https://www.acwing.com/solution/content/16778/)

```c++
#include<iostream>

using namespace std;

const int N = 1e6+10;
int n;
int q[N], tmp[N]; // using a temp array to store num

void merge_sort(int q[], int l, int r){
	if (l >= r) return;
	
	// Step 1. get the mid
	int mid = l + r >> 1;
	
	// Step 2. process the detail question
	merge_sort(q, l, mid), merge_sort(q, mid + 1, r);
	
	// Step 3. do the operation
	int k = 0; // k is a temp number
	int i = l, j = mid + 1; // the i and j are pointers, seperatly.
	while (i <= mid && j <= r){
		if (q[i] <= q[j]){
			tmp[ k ++ ] = q[ i ++ ];
		} else {
			tmp[ k ++ ] = q[ j ++ ];
		}
	}
	// if there are some number not ready
	while (i <= mid) tmp [ k ++ ] = q [ i ++ ];
	while (j <= r) tmp [ k ++ ] = q [ j ++ ];
	
	for (i = l, j = 0; i <= r; i ++, j++) q[i] = tmp[j];
}

int main(){
	scanf("%d", &n);
	
	for (int i = 0; i < n; i ++) scanf("%d", &q[i]);
	
	merge_sort(q, 0, n - 1);
	
	for (int i = 0; i < n; i ++) printf("%d ", q[i]);
	
	return 0;
}
```

#### [Inversion Number](https://www.acwing.com/problem/content/790/)

思路同样是`分治`，是归并排序的一个应用

> 找到中点，将所有的逆序对情况分为三种：

1. 逆序对在左半边 
2. 逆序对在右半边
3. 逆序对被中点分割

```c++
#include<iostream>

using namespace std;

typedef long long LL; // beacuse the result will boom the int, we should use the long long to define the result

const int N = 1e6+10;
int n;
int q[N], tmp[N]; // as same as the merge sort

LL inversion_number(int q[], int l, int r){
	if (l >= r) return 0;
	
	// Step 1. set mid
	int mid = l + r >> 1;
	
	// Step 2. seperate
	LL res = inversion_number(q, l, mid) + inversion_number(q, mid + 1, r);
	
	// Step 3. do the operation
	int k = 0;
	int i = l, j = mid + 1;
	while (i <= mid && j <= r){
		if (q[i] <= q[j]){
			tmp[ k ++ ] = q[ i ++ ];
		} else {
			tmp[ k ++ ] = q[ j ++ ];
			res += mid - i + 1;
		}
	}
	while (i <= mid) tmp [ k++ ] = q[ i ++ ];
	while (j <= r) tmp [ k++ ] = q[ j ++ ];
	
	for (i = l, j = 0; i <= r; i++, j++) q[i] = tmp[j];
	
	return res;
	
}

int main(){
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) scanf("%d", &q[i]);
	
	printf("%ld", inversion_number(q, 0, n - 1));
	
	return 0;
}
```

### DICHOTOMY

二分可以划分为`整数二分`和`实数二分`

二分的本质并不是单调性，也就是说：有单调性的可以二分，但是没有单调性的也可能可以二分。

#### [整数二分](https://www.acwing.com/problem/content/791/)

> 因为有边界问题，所以要考虑的东西有点多

二分的本质是可以找到一个确定的边界将原结构一分为二。

共有两个模板，关于如何选择，有一个迅速的口诀 `左 1 右 0`（来自于边界是否会死循环）：

```c++
// 记住二分的本质前提 永远是区间找边界，那就可能是找左边界，或者是右边界
// 比如元素 `起始位置` 和 `终点位置` 这道题目
// 起始位置是找左边界，终点位置是找右边界 

// 找左边界的模板
void dichotomy_branch1(){
    // - step 1 set the l and r boundary
    int l = 0, r = n - 1;
    
   	// - step 2 do the operation
    while(l < r){
        // -- set the mid
        int mid = l + r >> 1;
        // -- check() must be true, so r = mid
        if(check(mid)) r = mid; // here chech(mid) is q[mid] >= num;
        else l = mid + 1;
    }
}

// 找右边界的模板
void dichotomy_branch1(){
    // - step 1 set the l and r boundary
    int l = 0, r = n - 1;
    
   	// - step 2 do the operation
    while(l < r){
        // -- set the mid
        int mid = l + r + 1 >> 1;
        // -- check() must be true, so r = mid
        if(check(mid)) l = mid; // here chech(mid) is q[mid] <= num;
        else r = mid - 1;
    }
}
```

 二分算法一定是可以找到边界的，只不过边界的答案不满足性质，那就说明这个题目无解了。

#### [实数二分](https://www.acwing.com/problem/content/792/)

> 没有边界问题了，但是有精确值问题，如果是保留 n 位小数，一般是让 l 和 r 之间的差别小于 $10^{-(n + 2)}$ 注意变量类型即可

```c++
#include<iostream>

using namespace std;

int main(){
	double num; // the num needed to be computed the cubic root
	scanf("%lf", &num);
	
	double l = -1e5, r = 1e5; // the l and r boundary
	while(l < r - 1e-8){ // 1e-8 is from the experience
		double mid = (l + r) / 2;
		
		if(mid * mid * mid >= num) r = mid;
		else l = mid;
		printf("%lf %lf\n", l, r);
	}

	printf("%lf\n", l);
	
	return 0;
}
```

