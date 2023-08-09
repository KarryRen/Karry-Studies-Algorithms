# Karry Studies Algorithms

<center>Karry</center>

这一轮学习的目的是：学好模板，直接使用

## 1. Foundation

### 1.1 Sort

> [十大经典排序算法](https://blog.csdn.net/qq_35344198/article/details/106857042)

#### [Quick Sort](https://www.acwing.com/problem/content/description/787/)

快排（时间复杂度 $n log_2n$）的核心思想是`分治`，主要步骤为：

```c++
设定数组 q 左右两边的下标为 l 和 r
Step 1. 确定分界点 x: 可以是最左 (q[l]) | 最右 (q[r]) | 中间 (q[(l + r)/2]) | 随机 < 是数值 >
Step 2. 调整区间: 保证分界点左边的数字都小于等于 x ，分界点右边的数都大于等于 x ， 分界点不一定是 x *难点*
Step 3. 递归处理左右两端
```

`抓核心点`（Step 2） — 如何优雅快速地调整区间

```c++
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

### 1.2 DICHOTOMY

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

### 1.3 HIGH-PRECISION

> 所谓高精度，就是指运算的数字超过了语言设定的变量所能表达的范围，只能换一种方式进行表示。

`大整数`：`整数的位数长达 10e6`

基本的思路：

1. `大整数的存储`：这么大的整数用 int, long long 都表示不了，把大整数的每一位都依次存到数组中（Vector ）。存储思路是让高位存在数组的小下标位置。
2. `运算的过程`：本质就是模拟人工加减乘除的过程，其实算法的本质就是对人类思考的模拟

#### [ADD](https://www.acwing.com/problem/content/793/)

用代码对两个数组进行操作，模拟人工算加法的过程，注意进位即可。

```c++
#include<iostream>
#include<vector>

using namespace std;

vector<int> high_precision_add(vector<int> &A, vector<int> &B) {
	// using the '&' can reduce the time

	// define C as the result
	vector<int> C;

	int t = 0; // define the t as the temp number to store the important number (存储进位) 一定要初始化为 0  
	for (int i = 0; i < A.size() || i < B.size(); i ++) {
		if (i < A.size()) t += A[i];
		if (i < B.size()) t += B[i];
		C.push_back(t % 10); // 存储下来个位
		t /= 10; // 存储下来进位
	}

	if(t) C.push_back(1); // 最后一位如果还有进位, 就再多一个 1 
	
	return C; 
}

int main() {
	// define string to store the input number, so that it won't overfit
	// let a = '123456'
	// let b = '654321'
	string a, b;
	cin >> a >> b;

	// define two arraies to stor the input num
	vector<int> A, B;
	// read them in a right to left way
	for (int i = a.size() - 1; i >= 0; i --) A.push_back(a[i] - '0'); // A = [6, 5, 4, 3, 2, 1]
	for (int i = b.size() - 1; i >= 0; i --) B.push_back(b[i] - '0'); // B = [1, 2, 3, 4, 5, 6]

	// do the high pricision add
	vector<int> C = high_precision_add(A, B);

	// print the result
	for (int i = C.size() - 1; i >= 0; i -- ) cout << C[i];

	return 0;
}
```

#### [SUB](https://www.acwing.com/problem/content/794/)

```c++
#include<iostream>
#include<vector>

using namespace std;

bool cmp(vector<int> &A, vector<int> &B) {
	// compare the A and B, judge if A >= B

	// compare the lenghth first. if not equal
	if (A.size() != B.size()) return A.size() > B.size();

	// if lenth equal, compare the num from top to down
	for(int i = A.size() - 1; i >= 0; i--)
		if(A[i] != B[i])
			return A[i] > B[i];

	// equal
	return true;
}

// C = A - B ( A >= B )
vector<int> high_precision_sub(vector<int> &A, vector<int> &B) {
	// using the '&' can reduce the time

	// define C as the result
	vector<int> C;

	int t = 0; // define the t as the temp number to store the important number (存储借位)
	for (int i = 0; i < A.size(); i ++) { // the length of A must be higher than the lenth of B
		t = A[i] - t;
		if (i < B.size()) t -= B[i];
		if(t >= 0) { // 如果不存在借位现象就直接将这一位存储起来, 然后 t 置零 
			C.push_back(t);
			t = 0; 
		} else { // 如果存在借位现象, 就直接存 t + 10 
			C.push_back(t + 10);
			t = 1;
		}
	}
	
	// now the lenth of C is equal to A, so there has an situation '003', which is not good enough
	while(C.size() > 1 && C.back() == 0) C.pop_back();

	return C;
}

int main() {
	// define string to store the input number, so that it won't overfit
	// let a = '123456'
	// let b = '654321'
	string a, b;
	cin >> a >> b;

	// define two arraies to stor the input num
	vector<int> A, B;
	// read them in a right to left way
	for (int i = a.size() - 1; i >= 0; i --) A.push_back(a[i] - '0'); // A = [6, 5, 4, 3, 2, 1]
	for (int i = b.size() - 1; i >= 0; i --) B.push_back(b[i] - '0'); // B = [1, 2, 3, 4, 5, 6]

	// do the high pricision sub
	if (cmp(A, B)) {
		vector<int> C = high_precision_sub(A, B);

		// print the result
		for (int i = C.size() - 1; i >= 0; i -- ) cout << C[i];
	} else {
		vector<int> C = high_precision_sub(B, A);

		// print the minus
		cout << "-";
		// print the result
		for (int i = C.size() - 1; i >= 0; i -- ) cout << C[i];
	}


	return 0;
}
```

#### [MUL](https://www.acwing.com/problem/content/795/)

> 因为这个地方的除数是一个比较小的数，可以直接用 int 进行存储，所以乘除的思想都是直接进行计算。
>
> 这样的话乘和加的思想完全是一脉相承了

```c++
#include<iostream>
#include<vector>

using namespace std;

// C = A * b
vector<int> high_precision_mul(vector<int> &A, int b) {
	// using the '&' can reduce the time

	// define C as the result
	vector<int> C;

	int t = 0; // define the t as the temp number to store the important number (存储进位) 一定要初始化为 0
	for (int i = 0; i < A.size(); i ++) {
		t += A[i] * b;
		C.push_back(t % 10); // 存储下来个位
		t /= 10; // 存储下来进位
		
	}
	
	// 最后如果还有进位, 就把 t 反向存储进去
	while (t) {
		C.push_back(t % 10);
		t /= 10;
	} 
	
	// now the lenth of C is equal to A, so there has an situation '003', which is not good enough
	while(C.size() > 1 && C.back() == 0) C.pop_back();

	return C;
}

int main() {
	// define string to store the input number, so that it won't overfit
	// let a = '123456'
	string a;
	int b;

	cin >> a >> b;

	// define array to stor the input num
	vector<int> A;
	// read them in a right to left way
	for (int i = a.size() - 1; i >= 0; i --) A.push_back(a[i] - '0'); // A = [6, 5, 4, 3, 2, 1]

	// do the high pricision mul
	vector<int> C = high_precision_mul(A, b);

	// print the result
	for (int i = C.size() - 1; i >= 0; i -- ) cout << C[i];

	return 0;
}
```

#### [DIV](https://www.acwing.com/problem/content/796/)

> 除法的逻辑看起来很难，但是仔细看的话其实并不复杂，和之前的进位 / 借位 的核心逻辑不同，其核心是余数。

```c++
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 返回除法的结果以及余数 
vector<int> high_precision_div(vector<int> &A, int b, int &r) {
	// using the '&' can reduce the time

	// define C as the result
	vector<int> C;

	r = 0; // 用 r 来存储余数 
	for (int i = A.size() - 1; i >= 0; i --) {
		// 除法是从高位往低位运算的 
		r = r * 10 + A[i];
		C.push_back(r / b); // 除数直接放入结果数组中 
		r %= b; // 余数当作下一次的运算结果 
	}
	
	reverse(C.begin(), C.end());
	
	// now the lenth of C is equal to A, so there has an situation '003', which is not good enough
	while(C.size() > 1 && C.back() == 0) C.pop_back();

	return C;
}

int main() {
	// define string to store the input number, so that it won't overfit
	// let a = '123456'
	string a;
	int b;

	cin >> a >> b;

	// define array to stor the input num
	vector<int> A;
	// read them in a right to left way
	for (int i = a.size() - 1; i >= 0; i --) A.push_back(a[i] - '0'); // A = [6, 5, 4, 3, 2, 1]

	// do the high pricision div
	int r = 0;
	vector<int> C = high_precision_div(A, b, r);

	// print the result
	for (int i = C.size() - 1; i >= 0; i -- ) cout << C[i];
	cout << endl << r;

	return 0;
}
```

### 1.4 PREFIX-SUM AND DIFFERENCE

前缀和和差分本质是一个互运算，二者所用的核心的原理是前缀求和中的递推以及集合代表个体的思想，这种思想值得思索。

#### [Prefix Sum](https://www.acwing.com/problem/content/797/)

> 前缀和问题就是求数组的一段数字的和，进而降低求解数组和的复杂度，核心在于：
>
> 1. 计算前缀和的扫描算法
> 2. 边界求解的公式
>
> 先扫一遍完成存储后，再使用所存储的内容进行辅助运算。这样就可以避免每一次的复杂度都是 $n$ 了

```c++
/*
    @author Karry 
    @date on 2023/8/5.
    @comment Day 5
*/

#include<iostream>

using namespace std;

const int N = 1e6 + 10; // the boundary
int q[N], s[N]; // the raw array and the sum array

int main() {
    int m, n; // the input num
    scanf("%d %d", &n, &m);

    // input the array
    for (int i = 1; i <= n; i++) scanf("%d", &q[i]);

    // compute the sum using equation (attention => s[0] = 0)
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + q[i];

    while (m--) {
        int l, r; // the began l and the end r
        scanf("%d %d", &l, &r);

        printf("%d\n", s[r] - s[l - 1]); // the important equation
    }

    return 0;
}
```

#### [Submatrices Sum](https://www.acwing.com/problem/content/798/)

> 将上述的一维前缀和拓展为二维前缀和，核心还是思考如下两个问题：
>
> 1. 如何计算和 ？
> 2. 如何利用和求解 ？
>
> 同样的还是递推思路！

```c++
/*
    @author Karry 
    @date on 2023/8/5.
    @comment Day5
*/

#include<iostream>

using namespace std;

const int N = 1e3 + 10; // the boundary

int q[N][N], s[N][N]; // the raw array and the sum array

int main() {
    int n, m, t;

    scanf("%d %d %d", &n, &m, &t);

    // input the raw array
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &q[i][j]);

    // step 1. compute the sum array
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + q[i][j];

    // step 2. compute the result one by one
    while (t--) {
        int x1, y1, x2, y2;

        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        printf("%d\n", s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1]);
    }

    return 0;
}
```

#### [Difference](https://www.acwing.com/problem/content/799/)

> 差分本质上是前缀和的逆运算，知道前缀和，求解原数组。
>
> 至此我们就了解了所谓的前缀和数组和差分数组的本质关系。
>
> 所谓差分就是对数组中某个区间的数据进行反复加和，然后得到最终结果数组的值
>
> 使用差分可以将 $o(n)$ 的复杂度减少到 $o(1)$，对差分数组中某一个值进行操作后，就相当于对原数组中该下标及其之后的值都进行了操作。

```c++
/*
    @author Karry 
    @date on 2023/8/6.
    @comment Day 6 the difference is actually the minus operation of prefix
*/

#include<iostream>

using namespace std;

// define the boundary
const int N = 1e6 + 10;
// define the raw array and the difference array
int raw[N], dif[N];
// define the length of array and the input times
int n, m;

void insert_dif(int l, int r, int c) {
    // the insert function : using raw array to construct the difference array
    dif[l] += c;
    dif[r + 1] -= c;
}

int main() {
    scanf("%d %d", &n, &m);

    // input the raw array
    for (int i = 1; i <= n; i++) scanf("%d", &raw[i]);

    // get the difference array
    for (int i = 1; i <= n; i++) insert_dif(i, i, raw[i]);

    // input the operation
    while (m--) {
        int l, r, c;
        scanf("%d %d %d", &l, &r, &c);
        insert_dif(l, r, c);
    }

    // get back the raw array
    for (int i = 1; i <= n; i++) {
        // the same way as the prefix_sum
        raw[i] = raw[i - 1] + dif[i];
        printf("%d ", raw[i]);
    }

    return 0;
}
```

#### [Submatrices Difference](https://www.acwing.com/problem/content/800/)

> 类似于上述的一维逆操作，这个地方的矩阵差分本质上也是上述子矩阵前缀和的逆操作。
>
> 所用的题目其实就是上述一维的扩展

```c++
/*
    @author Karry 
    @date on 2023/8/6.
    @comment Day 6 the difference in matrices
*/

#include<iostream>

using namespace std;

// define the boundary
const int N = 1010;

// define the raw array and difference array
int raw[N][N], dif[N][N];

// define the n rows, m cols and t times operations
int n, m, t;

void insert_dif(int x1, int y1, int x2, int y2, int c) {
    dif[x1][y1] += c;
    dif[x1][y2 + 1] -= c;
    dif[x2 + 1][y1] -= c;
    dif[x2 + 1][y2 + 1] += c;
}

int main() {
    scanf("%d %d %d", &n, &m, &t);

    // input the raw array
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &raw[i][j]);

    // get the difference array
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            insert_dif(i, j, i, j, raw[i][j]);

    // do t times operation
    while (t--) {
        int x1, y1, x2, y2, c;
        scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &c);
        insert_dif(x1, y1, x2, y2, c);
    }

    // get the raw array back
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // the same way as the prefix_sum
            raw[i][j] = raw[i - 1][j] + raw[i][j - 1] - raw[i - 1][j - 1] + dif[i][j];
            printf("%d ", raw[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```

### 1.5 TWO-POINTERS

> 双指针算法就像其名字一样，有两个指针进行操作

整体来说分为两大类：

1. 一种像归并排序对两个序列进行同时操作
2. 一种像快速排序对一个序列进行操作

所有双指针算法的模版都是类似的：

```c++
// 先对第一个指针进行遍历
for (int i = 0; i < n; i++) {
	// 再对第二个进行操作 (chech 是检验某种性质)
  while (j < i && chech(i, j)) j++;
  
  // do other operation
}
```

核心思想，是将朴素算法开两重循环的 $O(N^2)$ 复杂度优化成为 $O(N)$

```c++
// 朴素算法
for (int i = 0; i < n; i++){
  for (int j = 0; j < n; j++{
    // do main operation
  }
}
```

一个最为经典的双指针算法 => split

```c++
input : "abc def ghi"
output : "abc"
  			 "def"
         "ghi"

/*
    @author Karry 
    @date on 2023/8/7.
    @comment an example for two pointers -> split
*/

#include<iostream>
#include<string.h>

using namespace std;

const int N = 1e6 + 10;

int main() {
    char str[N];

    // input the string
    gets(str);

    int n = strlen(str);

    // a template for two pointers
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && str[j] != ' ') j++;

        // do the other operations
        for (int k = i; k < j; k++) cout << str[k]; // output the word
        cout << endl;
        
        i = j;
    }

    return 0;
}
```

#### [Longest Unrepeated Subsequence](https://www.acwing.com/problem/content/801/)

> 最长的不包含相同元素的的子序列长度

双指针问题的思考思路：

1. `step 1` 一般都是先想一种暴力求解的方法

   ```c++
   // 暴力算法 确定哪个指针是头，哪个是尾
   for (int i = 0; i < n; i++){
     for (int j = 0; j <= i; j++{
       // 如果 i 和 j 之间出现了重复的数字
       if (chech(j, i){
         res = max(res, i - j + 1);
       }
     }
   }
   ```

2. `step 2` 然后用双指针算法进行优化。一般是发现某一个指针满足某种性质（尤其是==单调关系==）进而不需要重新从头遍历了，而是直接向后走，这样就完成了优化。

   ```c++
   // 对于这个题目来说，发现一个典型的性质那就是 j 是永远不需要往前走的，因此进行修正
   for (int i = 0, j = 0; i < n; i++){
     while(j <= i && check(j, i)) j++;
     
     res = max(res, i - j + 1);
   }
   // 这个题目的另一大难点在于，如何写 check
   // 因为数据范围比较小，所以可以另外开一个数组记录原数组中每个数出现的次数
   // i 指针持续向后移动，导致出现重复后，要想不再重复，就需要 j 指针向后移动直至将重复的值挤出去。
   ```

解答（如果改成字母就需要哈希表了）：

```c++
/*
    @author Karry 
    @date on 2023/8/7.
    @comment Day 7 two pointers lus
*/

#include<iostream>

using namespace std;

const int N = 1e6 + 10; // the boundary
int a[N]; // the input array
int s[N]; // the sum array to doc the times of a[n]

int main() {
    int n; // the length of input array
    int res = 0; // the result
    scanf("%d", &n);

    // input the array
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    // lus
    for (int i = 0, j = 0; i < n; i++) {
        s[a[i]]++; // doc the times of a[i]
        while (j <= i && s[a[i]] > 1) {
            // actually, the j <= i is useless, but it's more clear
            s[a[j]]--;
            j++;
        }
        res = max(res, i - j + 1);
    }

    printf("%d", res);

    return 0;
}
```

#### [Target Sum](https://www.acwing.com/problem/content/802/)

还是按照双指针算法的经典求解思路来进行

1. 先想暴力算法 （时间复杂度是 $O(nm)$）

   ```c++
   for (int i = 0; i < n; i++){
     for (int j = 0; j <= m; j++{
       if (a[i] + b[j] == x)
         cout << i << " " << j << endl;
   	    break;
     }
   }
   ```

2. 进行双指针优化，单调性在于：数组 A 和 B 是单调增的，但这种单调增并不是我们上面提到的单个指针的性质，需要将其做一个转化。==那就是一旦 A[i] + B[j] > x 后， j 一定只能单调减下来，对于递增的 A[i] 而言，解不可能在 j 右边。==

   ```c++
   for (int i = 0, j = m - 1; i < n; i++) {
     while (j >= 0 && A[i] + B[j] > x) j-- ;
     if (A[i] + B[j] == x) break;
   }
   ```

   这样，时间复杂度就变为了 $O(n + m)$。

解答：

```c++
/*
    @author Karry 
    @date on 2023/8/7.
    @Day 7 target sum
*/

#include<iostream>

using namespace std;

typedef long long LL; // because the boundary of the num in array is out of int. so we set long long
const int N = 1e5 + 10; // the boundary of the length
LL A[N], B[N];

int main() {
    int n, m;
    LL x;
    scanf("%d %d %lld", &n, &m, &x);

    for (int i = 0; i < n; i++) scanf("%lld", &A[i]);
    for (int i = 0; i < m; i++) scanf("%lld", &B[i]);

    for (int i = 0, j = m - 1; i < n; i++) {
        while (j >= 0 && A[i] + B[j] > x) j--; // j will never right move
        if (A[i] + B[j] == x) {
            printf("%d %d", i, j);
            break; // must break
        }
    }

    return 0;
}
```

#### [Judge Subsequence](https://www.acwing.com/problem/content/2818/)

> 此处子序列的含义略有变化，只要求顺序相同即可（顺次匹配），不要求连续

这个题有着很显然的单调性，十分经典，所以直接使用双指针算法进行求解即可。遍历长序列，短序列递增即可。

```c++
/*
    @author Karry 
    @date on 2023/8/7.
    @Day 7 judge subsequence
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10;
int a[N], b[N]; // the two input array

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < m; i++) scanf("%d", &b[i]);

    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] == b[j]) i++; // i rightly move only equal
        j++; // j rightly move forever
    }

    // make the final judgement
    if (i == n) printf("Yes");
    else printf("No");

    return 0;
}
```

### 1.6 BIT-OPERATION

> 核心就是两个操作
>
> 1. n 的二进制表示中第 k 位是几 ？
>
>    ```c++
>    step 1 先把第 k 位，移动到最后一位 n >> k
>    step 2 看个位是多少 （& 1） 操作即可
>    
>    总的来说就是：右移动 k 位与上 1
>    	n >> k & 1
>    ```
>
> 2. 返回 x 的最后一位 1 是多少 （low bit）==简直就是一个脑筋急转弯==
>
>    ```c++
>    low_bit(x) = x & (-x) = x & (~x + 1)
>    ```

#### [The Number of One](https://www.acwing.com/problem/content/803/)

其实根据上面两个核心操作都可以完成这项工作了，但是第一个操作方法中，很难判断 n 的二进制位数，但是第二种方法进行减操作比较容易判定边际。

```c++
/*
    @author Karry 
    @date on 2023/8/8.
    @comment Day 8 the number of one
*/

#include<iostream>

using namespace std;

int low_bit(int k) {
    return k & (-k);
}

int main() {
    int n; // there are n numbers should be computed
    cin >> n;

    while (n--) {
        int k;
        cin >> k;

        int res = 0;
        while (k) k -= low_bit(k), res++; // minus res times

        cout << res << " ";
    }

    return 0;
}
```

### 1.7 DISCRETIZATION

`离散化的基本含义`：对于一个值域特别大但是个数很少的数组进行操作，那么如果直接对数值进行操作就会导致所开新数组的范围过大（因为要顾及数的范围），但是离散化可以帮助我们将这些少量但较大的数映射到一个较小的范围内（最好的映射操作就是求解下标），进而方便操作。

`离散化中的两个问题`：

1. 原数组中可能有重复元素 => 去重 ==直接使用库函数==
2. 实现映射 => 如何算出离散化后的值（也就是说如何求解该数的下标 ）  ==使用二分==

```c++
// template
	vevtor<int> alls; // 存储待离散化的值的数组
	sort(alls.begin(), alls.end()); // 将所有值进行排序
	alls.erase(unique(alls.begin(), alls.end()), alls.end); // 去重的标准写法

	// 二分法求出 某一个值对应的离散化值（说白了就是求出该数的下标）
	int find(int x){
    int l = 0, r = alls.size() - 1;
    while(l < r){
      int mid = l + r >> 1;
      
      if (alls[mid] >= x) r = mid;
      else l = mid + 1;
		}
    
    return r + 1; // 将 0 - (n - 1) 映射到 1 - n
  }
```

#### [Interval Sum](https://www.acwing.com/problem/content/804/)

> 一种解题方式就是前缀和，还是比较简单的，但是由于数据范围比较大，可能在直接加和的时候爆存，所以前缀和只适用于 $10^5$ 以内的数据范围。
>
> 从这个题目中很明显能看出来离散化题目的特点，就是范围很大，但是操作的数量很少。

因此整体的思路就是先对原数组操作的所有下标进行离散化（排序 + 去重 + find），离散化后的下标结果就在 $10^5$ 量级上了，这样就可以对离散化后的数组采用前缀和进行求解了。

```c++
/*
    @author Karry 
    @date on 2023/8/9.
    @comment Day 9
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int, int> PII; // because their will be pairing input

const int N = 3e5 + 10; // because there are max 3 indexes (x, l, r) and each of their number are in range (10^5)
int n, m; // the two input number

vector<int> alls; // the alls will note all raw indexes (x, l, r).
vector<PII> add, query_bound; // the add will note (x and c), the bound will note (l and r).
int a[N], s[N]; //  a 数组会记录下来原下标离散化后映射的结果, s 则是前缀和操作的结果

// 二分法求解离散化后的值 (说白了就是找到相应值的下标)
int find(int x) {
    int l = 0, r = alls.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;

        if (alls[mid] >= x) r = mid;
        else l = mid + 1;
    }

    return r + 1; // 返回下标 + 1
}

int main() {
    cin >> n >> m;

    // note the add array (in x add c)
    while (n--) {
        int x, c;
        cin >> x >> c;

        add.emplace_back(x, c); // note the index x and the value c;
        alls.push_back(x); // note the add point
    }

    // note the bound array (from l to r)
    while (m--) {
        int l, r;
        cin >> l >> r;

        query_bound.emplace_back(l, r); // note the boundary (l, r)
        // same as top 或许你会有疑问，为什么还需要对 query 中的数字进行保留呢，其实很简单，因为后续还需要对这些下标进行操作，所以必须也把它们离散化了
        alls.push_back(l);
        alls.push_back(r);
    }

    // do the discretization for all of index
    sort(alls.begin(), alls.end()); // do the sorting
    alls.erase(unique(alls.begin(), alls.end()), alls.end()); // make the raw indexes unique

    // do the add to array a[]
    for (auto item: add) {
        int x = find(item.first); // x 是 item.first 这一个 index 对应的离散化后的下标 (from 10^9 to 10^5)
        a[x] += item.second; // in a do the raw add operation.
    }

    // do the prefix sum of a 对于所有的下标都要进行一次操作，一定要注意这个地方的下标有了变化，所以是 <=
    for (int i = 1; i <= alls.size(); i++) s[i] = s[i - 1] + a[i];

    // do the query operation
    for (auto item: query_bound) {
        int l = find(item.first); // index 离散化后的结果
        int r = find(item.second); // index 离散化后的结果

        cout << s[r] - s[l - 1] << endl;
    }

    return 0;
}
```

### 1.8 INTERVAL-CONSOLIDATION

对多个区间中有交集的部分进行合并，进而将多个区间合并成为多个没有交集的区间。输入多个区间，输出合并后没有交集的区间个数。

1. 一定要先针对每一个区间按照左边界点进行排序
2. 然后从前往后进行扫描即可

#### [Interval Consolidation](https://www.acwing.com/problem/content/805/)

```c++
/*
    @author Karry 
    @date on 2023/8/9.
    @comment Day 9
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int, int> PII;

void merge(vector<PII> &segs) {
    vector<PII> res;

    // 1. sort the segs
    sort(segs.begin(), segs.end());

    // 2. merge from left to right
    int st = -2e9, ed = -2e9; // 因为所有元素的 boundary 是在 [-1e9, 1e9] 内，所以这样设计不会越界
    for (auto seg: segs) {
        if (seg.first > ed) {
            // 如果某个区间的开头，大于循环的结尾了，那就说明到了一个新的区间了
            if (st != -2e9) { // 避免将非第一个区间（初始的区间）的内容存入
                res.emplace_back(st, ed); // 将上面分离开的区间存到 result 之中
            }
            st = seg.first, ed = seg.second; // 更新开头结尾
        } else {
            // 如果某个区间的开头，小于或等于结尾，那就说明有交集
            ed = max(seg.second, ed); // 更新 ed 即可，这个地方必须是 max 因为涉及到大区间包含小区间的情况
        }
    }

    // 3. 将最后一个 seg 放入其中
    if (st != -2e9) res.emplace_back(st, ed);

    segs = res;
}

int main() {
    int n; // the number of intervals
    cin >> n;

    vector<PII> segs; // the raw input intervals

    // input the raw intervals
    while (n--) {
        int l, r;
        cin >> l >> r;
        segs.emplace_back(l, r); // construct the interval
    }

    // merge the intervals
    merge(segs);

    // cout the number of intervals after merging
    cout << segs.size();

    return 0;
}
```

## 2. DATA STRUCTURE

