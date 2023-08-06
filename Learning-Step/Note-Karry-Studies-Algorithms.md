# Karry Studies Algorithms

<center>Karry</center>

这一轮学习的目的是：学好模板，直接使用

## 1. Foundation

### 1.1 Sort

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

