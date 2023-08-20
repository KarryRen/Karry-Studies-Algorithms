# Note of Systematic Learning

> [Basic Algorithm Course][https://www.acwing.com/activity/content/punch_the_clock/11/]

<center>Karry</center>

[toc]

## 1. Foundation

### 1.1 Sort

> [十大经典排序算法](https://blog.csdn.net/qq_35344198/article/details/106857042)

#### [Quick Sort](https://www.acwing.com/problem/content/description/787/)

快排（时间复杂度 $n log_2n$）的核心思想是==分治==，主要步骤为：

```c++
设定数组 q 左右两边的下标为 l 和 r
Step 1. 确定分界点 x: 可以是最左 (q[l]) | 最右 (q[r]) | 中间 (q[(l + r)/2]) | 随机 < 是数值 >
Step 2. 调整区间: 保证分界点左边的数字都小于等于 x ，分界点右边的数都大于等于 x ， 分界点不一定是 x *难点*
Step 3. 递归处理左右两端
```

==抓核心点==（Step 2） — 如何优雅快速地调整区间

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
    
    // 分成子问题, 分成子问题切忌 0, N 和 N, 0 这两种情况
    int x = q[l + r >> 1]; // 注意此处是取了一个数字，而不是下标，这是和归并的本质区别
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

#### [K Number (Quick Select)](https://www.acwing.com/problem/content/788/)

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

归并排序（时间复杂度 $nlog_2n$），同样是==分治==的思想，主要步骤如下：

```c++
设定数组 q 左右两边的下标为 l 和 r
Step 1. 确定分界点 mid = ( l + r ) / 2 < 是下标 >
Step 2. 递归排左右两边（左右两边必须是有序的，所以需要先递归）
Step 3. 将排好的归并起来 *重点*
```

==实现归并==：具体实现方法为==双指针==，两个有序的数组分别设置一个指针不断往后跑。归并排序是稳定的。

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
	
  // put the number back
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

思路同样是==分治==，是归并排序的一个应用

> 找到中点，将所有的逆序对情况分为三种：

1. 逆序对在左半边 （直接加上）
2. 逆序对在右半边（直接加上）
3. 逆序对被中点分割（两边排序与否是不影响的）

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
			res += mid - i + 1; // 如果此处出现一个逆序的数，根据数组分区有序性（就是说前、后半区的数字都是有序的）
      										// 因此如果不排序就得不到该结果，这就是采用归并排序的原因所在
      										// 那么逆序对的数量就要考虑到前半区一旦出现一个，其后面的数字也都大于后半区的数字，进而得到这一个结果
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

> 二分可以划分为`整数二分`和`实数二分`
>
> 二分的本质并不是单调性，而是存在一种划分方式。
>
> 也就是说：有单调性的可以二分，但是没有单调性的也可能可以二分。

#### [整数二分](https://www.acwing.com/problem/content/791/)

> 因为有边界问题，所以要考虑的东西有点多

二分的本质是可以找到一个确定的边界将原结构一分为二。

共有两个模板，关于如何选择，有一个迅速的口诀 ==左 1 右 0==（来自于边界是否会死循环）：

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
        // -- check() must be true, so l = mid
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

大整数：==整数的位数长达 10e6==

基本的思路：

1. ==大整数的存储==：这么大的整数用 int, long long 都表示不了，把大整数的每一位都依次存到数组中（Vector ）。存储思路是让高位存在数组的小下标位置。
2. ==运算的过程==：本质就是模拟人工加减乘除的过程，其实算法的本质就是对人类思考的模拟

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

> 前缀和和差分本质是一个互运算，二者所用的核心的原理是前缀求和中的递推以及集合代表个体的思想，这种思想值得思索。

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

核心思想，是将暴力算法开两重循环的 $O(N^2)$ 复杂度优化成为 $O(N)$

```c++
// 暴力算法
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

==离散化的基本含义==：对于一个范围特别广（下标特别大）但是个数很少的数组进行操作，那么如果直接对数值进行操作就会导致所开新数组的范围过大（因为要顾及数的下标范围），但是离散化可以帮助我们将这些少量但下标范围很大的数映射到一个较小的范围内（最好的映射操作就是求解下标），进而方便操作。

==离散化中的两个问题==：

1. 原数组中可能有重复元素 => 去重 ==直接使用库函数==
2. 实现映射 => 如何算出离散化后的值（也就是说如何求解出该数的目标下标 ）  ==使用二分==

```c++
// template
	vevtor<int> alls; // 存储待离散化的值下标的数组
	sort(alls.begin(), alls.end()); // 将所有原下标进行排序
	alls.erase(unique(alls.begin(), alls.end()), alls.end); // 去除原下标中的重复值的标准写法

	// 二分法求出某一个原下标对应的离散化后的下标（说白了就是实现原下标到目标下标的映射）
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

// 二分法求解离散化后的值 (说白了就是找到原本下标的离散化后的下标，x 原本表示较大的下标范围，后续会被离散化到所操作次数范围内)
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
        alls.push_back(x); // 把原下标进行保存
    }

    // note the bound array (from l to r)
    while (m--) {
        int l, r;
        cin >> l >> r;

        query_bound.emplace_back(l, r); // note the boundary (l, r)
        // same as top 或许你会有疑问，为什么还需要对 query 中的数字进行保留呢，
 	      // 其实很简单，因为后续还需要对这些下标进行操作，所以必须也把它们离散化了，才能在目标数组中找到
        alls.push_back(l);
        alls.push_back(r);
    }

    // do the discretization for all of index
    sort(alls.begin(), alls.end()); // 对原本的下标集进行排序
    alls.erase(unique(alls.begin(), alls.end()), alls.end()); // 对原本的下标集进行 unique 处理

    // do the add to array a[]
    for (auto item: add) {
        int x = find(item.first); // x 是 item.first 这一个 index 对应的离散化后的下标 (from 10^9 to 10^5)
        a[x] += item.second; // in a do the raw add operation. （在离散化后的数组中进行加和映射）
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

数据结构的本质是该存储结构可以快速维护相关的的操作以实现特定问题的简化，其核心在于存储数据的方式以及相关操作的具体形式。因此，当某些实际问题明显需要比较特殊的操作时（先进后出、树形查找【最大异或对】、集合合并【食物链】），就可以自动地往这上面靠。

不可否认，STL 库中给了我们大量的数据结构可以用，但是如果没有编译器优化的话，直接使用 STL 库中的数据结构就会造成运算速度不符合要求，因此最好的方法一定是用数组对数据结构进行模拟。因此这一部分的核心在于：

1. 对链表、栈、队列、字符串、Trie树、并查集、堆经典数据结构进行模拟（数据结构 + 算法操作）。
2. 使用模拟的数据结构解决相对应的常见问题（本质是借助数据结构的特性来进行求解）。

### 2.1 LINKED-LIST

> 第一种基本的数据结构，链表。
>
> 1. 了解基本的构造原理
>
>    ```c++
>    // 基本的实现方式就是 指针 + 结构体 => 动态链表
>    struct Node{
>      int val; // the value of Node
>      Node * next; // the next node of Node
>    }
>    
>    new Node(); 
>    ```
>
>    ==但是需要注意的是：由于存在 new 操作，所以速度十分慢，只适合于面试，不适合于算法题==。
>
> 2. 了解核心的操作思想
>
>    - 在头部插入
>    - 在第 k 个插入的数后面，插入数
>    - 在第 k 个插入的数后面，删除 数

所以在算法题目中我们通常采用的方式是：==数组模拟链表==，数组模拟链表可以实现指针实现链表的所有的操作。 

#### [Single Linked List](https://www.acwing.com/problem/content/828/)

> 单链表最常用的点在于实现==临接表==，存储图和树，进而实现后续有关这些数据结构的操作。所谓单链表是指只能向后走的单项链表。

```c++
使用数组实现单链表的核心思想是开两个数组
(value) e[N] => 某一个节点的值
(next) ne[N] => 该节点指向的内容（尾节点的下标用 -1 表示）
使用下标将 e 和 ne 关联起来
```

代码实现：

```c++
/*
    @author Karry 
    @date on 2023/8/10.
    @comment Day 10, 采用数组的方法实现单链表（数据结构第一课）
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10; // 数据范围定义

/*
 * 最为重要的四个定义
 * 1. head 表示名义上的“头”，是表示链表起始点的下标是多少（因为经历过增删，所以链表头的下标不一定是 0）
 *    head 的本质就是链表中逻辑上第一个节点的下标，如果没有节点，那就是 -1
 *    一个比较好理解的方式是，不断的 insert_to_head 相当于不断建头，尽管下标一直往后走，但是后面构建的始终是逻辑上链表的头
 *    所以更加具象的表示形式应该是 head 始终指向头部节点（在图上画成竖着的，而不是横着的）
 * 2. e[N] 指每一个节点的值是多少（通过下标访问）
 * 3. ne[N] 指每一个节点的下一指向的下标是多少（通过下标访问）
 * 4. idx 表示插入点的下标 （不断向前推进）
*/
int head, e[N], ne[N], idx;

// 链表初始化
void init_single_list() {
    head = -1; // 没有任何节点
    idx = 0; // 初始可以插入点的下标为 0
}

// 构建头节点 函数（x 为头节点的值）
void insert_to_head(int x) {
    e[idx] = x; // 构建这一节点的值
    ne[idx] = head; // 该节点指向原本的 head 节点
    head = idx; // head 标记该节点，表示此节点为链表的头，以方便后续地访问
    idx++; // idx++ 操作的下标后移
}

// 将节点插入到【下标】为 k 的后面 函数（x 为该插入节点的值）
void insert_node(int k, int x) {
    e[idx] = x; // 始终是 idx 维护构建新的节点的下标
    ne[idx] = ne[k]; // 新节点的 ne 为下标为 k 的节点的 ne
    ne[k] = idx; // 下标为 k 的 ne 变为 idx
    idx++;
}

// 删除【下标】为 k 的节点后的的节点
void delete_node(int k) {
    ne[k] = ne[ne[k]]; // 下标为 k 的节点指向其原本指向的节点的下一个节点
    // idx 不需要做任何的操作，因为这是算法题目，不用考虑内存的维护
}

// 删除头节点
void delete_head_node() {
    head = ne[head]; // 类似于上述删除操作，只不过此处直接找到 head 即可，因为千万别忘了 head 标识的就是头节点的下标
}

int main() {
    int m; // 操作次数
    cin >> m;

    // - 初始化
    init_single_list();

    // - 完成操作
    while (m--) {
        char op; // 操作符
        int k, x; // 操作数

        cin >> op; // 输入操作符

        if (op == 'H') {
            // 构建链表头
            cin >> x; // 输入待插入的节点的值
            insert_to_head(x);
        } else if (op == 'I') {
            // 在第 k 个插入的节点后，插入新的节点
            cin >> k >> x; // k : 第 k 个插入的节点
            insert_node(k - 1, x); // 第 k 个插入的节点的下标为 k - 1
        } else if (op == 'D') {
            // 删除第 k 个插入的节点后面的节点
            cin >> k; // k : 第 k 个插入的节点
            if (k == 0) delete_head_node(); // 如果 k = 0 表示删除头节点
            else delete_node(k - 1); // k != 0 表示删除第 k 个插入的节点，其下标为 k - 1
        } else {
            cout << "wrong op !";
        }
    }

    // - 输出链表
    for (int i = head; i != -1; i = ne[i]) cout << e[i] << " ";
    cout << endl;

    return 0;
}
```

#### [Double Linked List](https://www.acwing.com/problem/content/829/)

> 双链表最常用的点在于==优化某些问题==

```c++
双链表较比单链表而言，无非是有了双向性，既有后指向又有前指向
(value) e[N] => 某一节点的值
(right point) r[N] => 下标为 i 的节点右边的节点下标
(left point) l[N] => 下标为 i 的节点左边的节点下标
```

代码实现：

```c++
/*
    @author Karry 
    @date on 2023/8/10.
    @comment Day 10 采用数组实现双链表（数据结构第一课）
*/


#include<iostream>
#include<string>

using namespace std;

const int N = 1e5 + 10; // 数据范围定义

/*
 * 最为重要的四个定义
 * 0. head 因为过于繁琐，在双链表实现的时候我们就不再采用单链表的方式进行处理（包括 tail）
 * 1. e[N] 指每一个节点的值是多少（通过下标访问）
 * 2. r[N] 指每一个节点的右指向节点的下标是多少（通过下标访问）
 * 3. l[N] 指每一个节点的左指向节点的下标是多少（通过下标访问）
 * 4. idx 表示插入点的下标 （不断向前推进）
*/
int e[N], r[N], l[N], idx;

// 初始化双链表
void init_double_linked_list() {
    // 和单链表初始化不同，双链表将下标 0 直接当作头节点， 下标 1 直接当作尾巴节点
    r[0] = 1; // 下标 0 的右节点为 1
    l[1] = 0; // 下标 1 的左节点为 0
    idx = 2; // 由于 0 和 1 已经被用，所以 init 之后 idx = 2
}

// 后续的功能实现，其实归结到底只有两个，就是在【下标】k 的节点右边插入一个点，以及删除【下标】为 k 的节点
// 1. 实现在【下标】 k 的节点右边插入一个节点
void insert_right_node(int k, int x) {
    e[idx] = x; // 构建一个新的节点
    l[idx] = k; // 新的节点左边应该指向下标 k
    r[idx] = r[k]; // 新的节点右边应该指向下标 k 的节点的右指向下标
    l[r[idx]] = idx; // idx 的右边的左指向应该是 idx
    r[l[idx]] = idx; // idx 的左边的右指向应该是 idx
    idx++; // idx 右移动
    // 当然上面还可以写成更为常规的写法
    // l[r[k]] = idx;
    // r[k] = idx;
    // 如果这么写的话，那这个地方的顺序必须要保证，否则就会出错
}

// 2. 实现删除【下标】k 的节点
void delete_node(int k) {
    // 无非就是直接将 k 节点架空
    r[l[k]] = r[k]; // k 左边的右边指向 k 的右边
    l[r[k]] = l[k]; // k 右边的左边指向 k 的左边
}

int main() {
    int m; // 操作的次数
    cin >> m;

    // - 初始化
    init_double_linked_list();

    // - 进行操作
    while (m--) {
        string op; // 操作符
        int k, x; // 操作数

        cin >> op;
        if (op == "R") {
            // 在双链表的最右边插入一个节点
            cin >> x;
            insert_right_node(l[1], x); // 无非就是在 【尾节点】的【左边点】的【右边】插入一个节点
        } else if (op == "L") {
            // 在双链表的最左边插入一个节点
            cin >> x;
            insert_right_node(0, x); // 无非就是在【头节点】的【右边】插入一个节点
        } else if (op == "IR") {
            // 在第 k 个插入的数右边插入一个数
            cin >> k >> x;
            insert_right_node(k + 1, x); // 一定要搞清楚第 k 个插入的数的下标是多少！(因为 idx 是从 2 开始的)
        } else if (op == "IL") {
            // 在第 k 个插入的数左边插入一个数
            cin >> k >> x;
            insert_right_node(l[k + 1], x); // 在第 k 个插入的数的左边的数插入
        } else if (op == "D") {
            // 删除第 k 个插入的数
            cin >> k;
            delete_node(k + 1); // 同样是搞清楚第 k 个插入的数的下标是多少
        } else {
            cout << "wrong op !";
        }
    }

    // - 输出链表
    for (int i = r[0]; i != 1; i = r[i]) cout << e[i] << " ";

    return 0;
}
```

### 2.2 STACK

> 第二种数据结构，栈。stack 就是弹夹（后进先出）
>
> 其基本操作如下：
>
> 1. push
> 2. pop
> 3. 输出栈顶元素
> 4. 判断栈是否为空

#### [Stack](https://www.acwing.com/problem/content/830/)

使用数组进行模拟比较简单，因为不像链表需要对值和指向两个数组进行维护，此处只需要维护值这一个数组。

```c++
/*
    @author Karry 
    @date on 2023/8/11.
    @comment Day 11 using array to make stack
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10; // the boundary of input m

/*
 * 对于栈来讲，只需要两个内容
 * 1. stk[N] 中存储所放入的值
 * 2. idx 记录栈顶的下标，idx 从 0 or -1 开始都可以，在这个地方为了保持和前面的链表一致，
 *    我选择从 0 开始（这样的话栈顶元素就需要是 idx - 1 了）也就是说 idx 标识的是栈顶（下标 + 1）
 */
int stk[N], idx;

// 初始化操作
void init() {
    idx = 0;
}

// push 操作
void push(int x) {
    stk[idx] = x;
    idx++;
}

// pop 操作
void pop() {
    idx--;
}

// 查找栈顶元素操作
int find_top() {
    return stk[idx - 1];
}

// 判断栈是否为空
void empty() {
    if (idx <= 0) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main() {
    int n;
    cin >> n;

    string op; // 操作符
    int x; // 操作

    // - 初始化 stk
    init();

    // - 进行操作
    while (n--) {
        cin >> op;
        if (op == "push") {
            cin >> x;
            push(x);
        } else if (op == "pop") {
            pop();
        } else if (op == "empty") {
            empty();
        } else if (op == "query") {
            cout << find_top() << endl;
        } else {
            cout << "wrong input" << endl;
        }
    }

    return 0;
}
```

#### [Expression Evaluation](https://www.acwing.com/problem/content/3305/)

> 经典问题：二元运算符中缀表达式求解。解决这一问题，现在有两种基本的思路，其核心思想就是运算树的构建（非叶节点全部是运算符，叶节点全部是数字），进而使用递归进行求解。
>
> 1. 使用栈进行求解
>
>    ```c++
>    中缀表达式和后缀表达式都可以用栈来模拟树实现递归过程。
>    ```
>
> 2. 使用编译原理中的语法结构进行求解（更为简单）
>
>    ```c++
>    其实这种求解的本质是递归求解，关键是构建树的过程
>    ```
>
> 此处由于是学习 stack 的结构与使用技巧，所以我们采用 stack 进行求解。

 整体的思路如下：

```c++
eval(){
  		· 从操作数栈中弹出两个操作数
			· 从操作符栈中弹出一个操作符
			· 两个操作数和一个操作符执行相应的计算
			· 将结果压入操作数栈
}

input 是一个字符串（也就是说每一个数字其实本质是一个 string 中的 char ），表示中缀表达式。
step 1 - 读入该字符串

step 2 - 从左到右扫描该字符串
	1. 如果遇到操作数（数字），将 char 转换成数字，然后将其压入操作数栈
	2. 如果遇到操作符，则通过判断分情况处理
		- 如果【操作符栈为空】或【栈顶元素为左括号】，则将该操作符压入操作符栈中
		- 如果新的操作符的优先级大于操作符栈顶的操作符，那么就说明这棵子树还没有到顶，就要将该操作符压入到操作符栈中
		- 如果新的操作符的优先级小于或等于操作符栈顶的操作符，并且符号栈栈顶元素不是左括号，那么就说明这棵子树到顶了就要：
  		· eval()
		  · 循环进行判断
			· 直至将新的操作符压入操作符栈中
		- 如果遇到左括号，直接压入栈中
		- 如果遇到右括号，则执行以下操作直至遇到左括号
			· eval()
			· 弹出操作符栈顶的左括号
			
step 3 - 如果扫描完后操作符栈中仍然含有操作符，重复执行以下操作：
			· eval()

step 4 - 操作数栈栈顶的元素就是最终结果

写代码时字符的优先级有一个 map 来表示，就比较好做
```

根据上述思路可以得到如下代码：

```c++
/*
    @author Karry 
    @date on 2023/8/11.
    @comment Day 11 表达式值的计算（采用栈进行求解）
*/

#include<iostream>
#include<cstring> // 后续会用到字符串
#include<stack> // 引入栈
#include<algorithm>
#include <unordered_map> // 存储运算符的优先级需要用 map 来表示

using namespace std;

/*
 * 两个最为重要的结构
 * 1. 操作数栈，存储所有的操作数
 * 2. 操作符栈，存储所有的操作符
 */
stack<int> num;
stack<char> op;

// 满足条件时的计算操作
void eval() {
    // 取出操作数栈栈顶的两个操作数 （注意后进先出的顺序）
    int b = num.top();
    num.pop();
    int a = num.top();
    num.pop();
    // 取出操作符栈栈顶一个操作符
    char c = op.top();
    op.pop();

    int x; // 运算结果（根据不同的运算）
    if (c == '+') x = a + b;
    else if (c == '-') x = a - b;
    else if (c == '*') x = a * b;
    else x = a / b;
    num.push(x); // 将运算结果压入 num 栈栈顶
}

int main() {
    // 定义操作符的优先级
    unordered_map<char, int> pr{{'+', 1},
                                {'-', 1},
                                {'*', 2},
                                {'/', 2}};

    // ---- step 1. 输入中缀表达式运算符 ---- //
    string str;
    cin >> str;

    // ---- step 2. 从左到右进行扫描 ---- //
    for (int i = 0; i < str.size(); i++) {
        // - 对扫描到的字符进行判断
        char c = str[i];

        if (isdigit(c)) {
            // case 1. 如果是数字那就需要不断的往后扫描，直至把数字全部扣出来
            int x = 0, j = i;
            while (j < str.size() && isdigit(str[j])) x = x * 10 + (str[j] - '0'), j++;
            // 该数字扣完后需要进行两个操作
            i = j - 1;   // 1. 扫描字符串的指针前移（移动到最后一个数字那）
            num.push(x); // 2. 将该数字压到数字栈中
        } else if (c == '(') {
            // case 2. 如果是左括号就直接压入操作符栈中
            op.push(c);
        } else if (c == ')') {
            // case 3. 如果是右括号，就需要进行计算操作，直至遇到左括号，然后将左括号弹出
            while (op.top() != '(') eval();
            op.pop();
        } else {
            // case 4. 正常的操作符 符合以下三个条件就进行计算操作，如果不符合就不做
            // - op 栈不为空
            // - op 的栈顶不是左括号
            // - 操作符的优先级小于等于操作符栈顶操作符的优先级
            while (op.size() && op.top() != '(' && pr[c] <= pr[op.top()]) eval();
            // 将该操作符放入操作符栈中
            op.push(c);
        }
    }

    // ---- step 3. 扫描完毕后，进行收尾工作 ---- //
    while (op.size()) eval();

    // ---- step 4. 输出计算结果 ---- //
    cout << num.top() << endl;

    return 0;
}
```

#### [Monotonic Stack](https://www.acwing.com/problem/content/832/)

> 单调栈，所谓单调就是指栈中的元素呈单调增或者单调减的趋势。==单调栈的本质就在于其始终维护着对于求解问题中有意义数据的单调排列。==
>
> 因为栈的单头性质，只需维护栈顶的数值，进而维护一个具有某种特性的数列就较为简单。

==核心应用==：给定一个数组，找到某数左边距离最近的比它小的数。

```c++
// input [3, 4, 2, 7, 5]
// output [-1, 3, -1, 2, 2]
```

先考虑暴力怎么去做，很容易解决，但会超时。单调栈的思路和==双指针==是类似的，也就是说先考虑暴力求解算法，然后找到规律发现单调性，尝试挖掉一些元素进行求解简化。

```c++
// 暴力求解 (这种方法的时间复杂度是 O(n^2) )
#include<iostream>
using namespace std;

const int N=1e5 + 10;

int q[N];

int main(){
  int n;
  cin >> n;
  
  for(int i = 0; i < n; i++) cin >> q[i];
  
  int i, j;
  for(i = 0; i < n; i++){
    for(j = i - 1; j >= 0; j--){
      // 两重循环
      if (q[j] < q[i]) break;
    }
   	if(j >= 0) cout << q[j] << " ";
    else cout << "-1 ";
  }
  
  return 0;
}
```

==优化思路==：这种题目可以采用破坏性求解，也就是说不用维护原数组，就可以得到答案。

1. 发现无用值：先看有原序列二重扫描中有没有无用的数出现：对于一个数 q[i] 来说，如果该数的左边存在 q[x] > q[y] 且 x < y ，也就是说存在左边大于右边数的情况，那么左边的数就是无用值（任何情况下都不可能取到，也就意味着它可以被删去）。
2. 找到单调性：发现有意义的数始终保持着单调递增的趋势。
3. 使用单调性：如何使用单调栈进行这种单调性的维护成为了关键，每来一个数就去对栈顶元素进行依次查询，一旦破坏了单调性（新进来的元素比栈顶元素要大）那就把栈顶元素拿出来，重复操作，直到单调性再次成立，将该数字放进去即可。

```c++
/*
    @author Karry 
    @date on 2023/8/13.
    @comment Day 13 单调栈降低时间复杂度
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10;

int n;
int stk[N], tt; // 构建起一个栈

int main() {
    cin >> n;

    // 根本不需要提前构建一个数组
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x; // 输入新元素的值

        // 只要栈顶的元素大于输入的元素，那该元素就没有任何的意义了，直接去掉（出栈）即可。
        while (tt - 1 >= 0 && stk[tt - 1] >= x) tt--;

        // 如果在栈中找到一个元素 < x 的，那么该栈顶元素就是第一个小于 x 的值 （栈是有序的）
        if (tt - 1 >= 0) cout << stk[tt - 1] << " ";
        else cout << "-1 ";

        // 让新元素成为栈顶
        stk[tt++] = x;
    }

    return 0;
}
```

### 2.3 QUEUE

> 第三种数据结构，队列。queue，就是打饭窗口的队（先进先出）。
>
> 其本质和栈是一样的，只不过需要两个指针来进行维护。

#### [Queue](https://www.acwing.com/problem/content/831/)

```c++
/*
    @author Karry 
    @date on 2023/8/12.
    @comment Day 12 using array to do the queue
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10;

/*
 * 对于队列而言需要维护三个内容
 * 1. q[N] 用于存储队列中的值
 * 2. hh 表示头指针，表示队头（可以输出的地方）初始化为 0
 * 3. tt 表示尾指针，表示队尾（可以输入的地方）初始化为 0 （当然也可以初始化为 -1，那样访问队尾就不用减 1 了）
 *    但是为了和之前的链表以及栈保持一致，我在此处还是将 tt 初始化为了 0
 */

int q[N], hh, tt;

// 初始化函数
void init() {
    hh = 0;
    tt = 0;
}

// 向队尾插入一个数
void push(int x) {
    q[tt] = x; // 向队尾插入该数
    tt++; // 队尾指针后移动，因此可以看到 tt 的值是【队尾元素下标 + 1】，而不是队尾元素下标
}

// 从队头弹出一个数
void pop() {
    hh++; // 头指针只需要向后移动一个即可，因此可以看到 hh 的值就是队头元素的下标
    // 这个地方和链表一样不需要考虑空间的维护,实际上只有 stack 能充分利用数组的空间，只要有两个指针，就都不可能充分利用。
}

// 判断是否为空
void empty() {
    // 这个地方是否能取到等号也是和指针的初始化有关，一定要注意判别
    if (hh < tt) cout << "NO" << endl;
    else cout << "YES" << endl;
}

// 查询队头元素
void find_head() {
    cout << q[hh] << endl;
}

int main() {
    int m;
    cin >> m;

    // - 进行初始化
    init();

    // - 进行详细的操作
    string op; // 定义操作符
    int x; // 定义操作数
    while (m--) {
        cin >> op;
        if (op == "push") {
            cin >> x;
            push(x);
        } else if (op == "pop") {
            pop();
        } else if (op == "query") {
            find_head();
        } else if (op == "empty") {
            empty();
        } else {
            cout << "wrong input !" << endl;
        }
    }

    return 0;
}
```

#### [Monotonic Queue](https://www.acwing.com/problem/content/156/)

> 单调队列，较比单调栈来说更难。==单调队列的本质在于其始终维护着有效数据的单调性和顺序性。==

==核心应用==：滑动窗口求最小值，一旦相关的题目可以被转换为这种形式就可以思考单调队列。

先考虑暴力算法如何去做。

```c++
// 这道题的暴力去接是很简单的 O(nk)
#include<iostream>

using namespace std;

const int N = 1e6 + 10;
int n, k, q[N], max_n[N], min_n[N];

int main(){
	cin >> n >> k;
  
  for (int i = 0; i < n; i++) cin >> q[i];
  
  int idx = 0;
  for (int i = 0; i < n - k + 1; i++){
    int x = q[i];
    int y = q[i];
    for (int j = i + 1; j < i + k; j++){
      // 用一个指针来维护窗口，使用遍历法求解这一窗口中的最大最小值
      if (x < q[j]) x = q[j];
      if (y > q[j]) y = q[j]; 
    }
    max_n[idx] = x;
    min_n[idx] = y;
    idx ++;
  }
  
  for (int i = 0; i < idx; i++) cout << min_n[i] << " ";
  cout << endl;
  for (int i = 0; i < idx; i++) cout << max_n[i] << " ";
  
  return 0;
}
```

==优化思路==：使用队列进行窗口的维护，对原数组进行顺次求解，

1. 发现无用值：对于求窗口中的最小值而言，靠近队头的数 x 如果比靠近队尾的 y 还大的话，那 x 的存在是没有任何意义的。也就是说存在左边大于右边的情况，左边的数就是无用值。
2. 找到单调性：发现所维护的应该是一个单调递增的序列，最小值永远都在队头，直接取就可以了，不用再进行循环。
3. 使用单调性：关键是如何使用单调队列维护好这种单调性，此处就不像是单调栈那么简单了，因为单调栈只需要考虑一头的出，出完了之后自然就压栈了。但是这个地方，我们既要考虑队头的出，也要考虑队尾的入，而且因为有了窗口的概念，所以要时刻判断某值是否仍然在窗口中。因此需要以下的步骤：
   - 每次扫入一个值时，我们要先判断所维护的单调队列中的队头是否还在窗口中（因此在队列中维护下标，而非元素是一个更好的选择），如果不在了就从头出去。
   - 然后对扫入的值进行判断，如果该值打破了原本的单调性（比队尾下标所对应的元素还要小），那就需要从队尾出元素，直至单调性恢复。然后将扫入的值的下标放入队尾。 
   - 输出队头

```c++
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
```

### 2.4 STRING

> 第四种数据结构：字符串，其本质就是字符的数组。常见的问题就是字符串匹配、找子串等算法。
>

#### [KMV](https://www.acwing.com/problem/content/833/)

> [延伸 blog](https://blog.csdn.net/raelum/article/details/128823560)，前缀和后缀的理解是这个算法的关键

==算法本质==：求子串是 string 中的重要问题，暴力求解的思路其实很简单，那就是在子串和母串上分别都开一个指针，然后进行逐个扫描即可，这种算法也被称为 BF 算法，因为在母串上会有指针回溯，所以复杂性极高，实用性不强，KMV 的本质就是为了减少时间复杂度。

==算法思想==：其实和单调栈和单调队列一样，暴力算法都很简单，但也都是改良算法的出发点。KMV 的出发点肯定是暴力算法（BF）

```c++
// 两个 str 事件复杂度是 O(mn)
char str_P[N], str_S[N];

// 开两个指针，然后进行循环遍历即可
for (int i = 0; i < n; i++) {
  bool flag = true;
  for (int j = 0; j < m; j++) { // m 是子串的长度
    // 一旦有一个字符不匹配，就说明不是子串
    if(str_S[j] != str_P[i]) {
      flag = false;
      break;
		}
  }
  cout << flag << endl;
}
```

暴力算法慢的本质是在于其完全舍弃了已经匹配的相关信息（母串的指针已经向后移动好多位了，这些信息其实已经反映了母串和子串的匹配关系，但是并没有存储下来），也就是说**不管是在子串的哪个字符不匹配的，母串指针都只会向后移动一位**。

因此，我们的出发点就在于：如何用好这些匹配的相关信息构造单调性，一个很自然的思路就是：**<u>在不匹配的时候，让母、子指针都尽少地向前回溯。</u>**

```c++
// 来个例子 数组都是从 0 开头的
母串：abcababcabcabc
子串：abcabcabc
当循环到 a != c 的时候，j 有必要回到开头吗？ 
没有必要，因为我明明已经知道在不匹配钱有 ab 匹配了，那我如果能找到从头开始出现的 ab 后面的继续找就可以了呀。其他的指针循环都是多余操作，只用保留这个利用了最多信息的操作即可。
因此第一次不匹配后，指针 i 根本不用变，指针 j = next[j]，匹配从逻辑上就变成了：
abcababc
   abcabc

// 在这个地方仔细阐述一下 next[] 数组的含义。
// 说文艺一点就是回溯到多远能够找到曾经自己出现过的地方
// 数学一点就是 j 下标的最长前缀和从子串开头的最长后缀结尾的下标，满足：
str_s[0, next[j]] = str[j - next[j] , j] // (一定是最长的 j - next[j] != 0，从这就可以看出子串开头的特殊性了)
// 尽管从数学上看起来很复杂，但是直观看很简单，就拿上面的例子来说，对于 abcabc
next = [0, 0, 0, 0, 1, 2, 3, 4] 
// 但是这样的结果代码还没想出来，本质是子串的开头没有跟 next[i] 指向的开头区分开，有很多情况无法跳出循环或者访问错误！因此常用的方法是按照下面的定义
next = [-1, 0, 0, 0, 1, 2, 3, 4] // 下标从 0 开始
next = [0, 1, 1, 1, 2, 3, 4, 5] // 下标从 1 开始
```

通过上面的思考，就能得到 KMV 算法的整体逻辑了：（注意子、母指针错位的思路）

1. **<u>*Step 1.*</u>** 求出子串的 next 数组

   可以看成是自己跟自己的匹配，获取 next 的本体，再来一个副体表示目前匹配的最长前缀（主体的指针从 1 开始往后走，副体的指针从 0 开始往后走）

   - next[0] 设定为 -1（作为很多情况下的一种跳出条件）
   - 因此主体的指针从 1 开始循环，副体的指针从 0 开始循环
     - 如果二者不匹配，不断循环往前推出前一个最长前缀（有一点递归的思路）
     - 如果匹配，前缀和后缀都往后移动
     - 为 next 赋值
     - 母指针向后移动一位（母指针始终往后走）

2. **<u>*Step 2.*</u>** 从母串的开头进行遍历（母指针均从 0 开始，子指针从 1 开始）

   - 如果母串和子串符号不匹配（注意是母指针的 i 和子指针的 j + 1 比），子串的指针就退回到 j = next[j]，循环的比较（跳出循环的条件是 1. 回溯到的下标已经到了子串的开头（j = -1）；2.出现了匹配）
   - 如果母串和子串符号匹配，子指针往后移动 1 位 （一定要先判断不匹配做操作，再做匹配判断）
   - 母指针往后移动一位（母指针始终往后走）

[解答](https://www.acwing.com/activity/content/code/content/43108/)

```c++
注意，此处我已经深刻理解了 kmv 的本质含义所在，但是无奈想用最淳朴的方法写出，熬到凌晨 2 点半，最终放弃，选择更加 fancy 的做法！
// 以后若是有时间，一定要再补回来 ！！！！ //
  /*
    @author Karry 
    @date on 2023/8/14.
    @comment 凌晨所做，发现自己的思路行不通，下标从 0 开始，记住下面的做法
*/
#include <iostream>

using namespace std;

const int N = 1000010;

int n, m;
char s[N], p[N];
int ne[N];

int main() {
    cin >> m >> p >> n >> s;

    // step 1 求解 next 数组
    ne[0] = -1; // 因为子串开头有着自己的特殊性，必须要定义成 -1，就算后面的 next[j] 名义上是指第下标 0，实质上也是 0
    // 这样就可以将实际上的开头和 next[j] 指向的开头区分开，就可以跳出循环了！
    for (int i = 1, j = -1; i < m; i++) {
        while (j >= 0 && p[j + 1] != p[i]) j = ne[j];
        if (p[j + 1] == p[i]) j++;
        ne[i] = j;
    }

    // step 2 使用 next 数组进行求解
    for (int i = 0, j = -1; i < n; i++) {
        while (j != -1 && s[i] != p[j + 1]) j = ne[j];
        if (s[i] == p[j + 1]) j++;
        if (j == m - 1) {
            cout << i - j << ' ';
            j = ne[j];
        }
    }

    return 0;
}
```

### 2.5 TRIE

> 第五种数据结构：Trie 树（本质是一种字母的树形结构），能够高效地==存储和查找字符串集合==。
>
> 用到 Trie 树的情况通常比较简单，比如只有大写字母 or 小写字母 or 只有数字。
>
> 构建 Trie 树，完成串的存储，方式很简单，分为两步：
>
> 1. 对每一个单词，沿着单词每一个字母向下走，直至 end。
> 2. 对单词的结尾进行标记。
>
> 根据 Trie 树进行路径寻找，完成串的查找，方法也很简单，就是两种情况：
>
> 1. 根本不存在指定单词的路径。
> 2. 存在这条路径，但是到了这个单词的最后一个字母时，发现没有终点标记。

#### [String Statistics](https://www.acwing.com/problem/content/837/)

> 就是完成字符串的经典操作：存储 + 查询

1. 存储（存储的本质是构建一个树，关键在于如何存储每一个节点）

   - 用一个唯一的标识符（idx）来标记节点（根节点的 idx = 0）。
   - 采用二维数组（arr\[N][26]）来进行构建树节点的存在性以及指向关系。
   - 对该二维数组进行第一维度的访问通过 idx，表示找节点。
   - 对该二维数组进行第二维度的访问通过（0 - 25 表示字母的存在），表示找子节点

   因此在构建树的过程中，就是进行数组的插入操作

   ```c++
   // step 1. 从根节点出发（标识符 p = 0）。
   // step 2. 对字符串进行遍历，逐个取出字符，并转换成 0 - 25 的标识 (u)。
   // step 3. 判断该字符是否存在（arr[p][u] 是否为 0），如果存在就继续向下访问，如果不存在就创建一个（通过 idx 进行维护）并继续向下访问，直到字符串遍历完毕。
   // step 4. 字符串的终点对应的树的标识（通过 idx 进行维护）现在已经拿到，只需要在记录以该节点为结尾的字符数组中 + 1 即可（表示目前有多少单词以之为结尾）。
   ```

2. 查询（找到这个字符串终点的节点上的结尾标识数有多少）

   - 从根节点出发，按照上述操作进行找子节点
   - 如果根本没有这条路，那该字符串肯定就不存在
   - 如果存在这条路，输出终点对应的结尾标识数有多少即可

```c++
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
```

#### [Maximal Dissimilarity Pair （MDP）](https://www.acwing.com/problem/content/145/)

> 异或操作就是不进位加法（相同为 0，不同为 1 ）

这个题目暴力算很简单，无非就是开两个指针进行枚举

```c++
// 暴力求解
int res = 0;

for (int i = 0; i < n - 1; i++){
  // 第一个指针遍历
  for (int j = i + 1; j < n; i++){
    // 第二个指针遍历
    res = max(a[i] xor a[j], res);
  }
}
```

因此，这个题目的本质仍然是优化，找到一种好的方式能够将时间复杂度降低下来（和之前所学的双指针、单调栈、单调队列是一样），此处借助的是 Trie 树来减少第二重遍历的数量。

思考的过程是这样的，因为异或的本质是位运算，所以可以单独考虑每个数的每一位。又因为需要比较数的大小，所以从左往右挨个 bit 进行比较即可，针对每一个数就可以形成一个树的寻找路线。

```c++
比如对于一个 31 位的数 101110...1
现在在找和它异或最大的数时：
	- 31 位为 0 的肯定大于 31 位为 1 的
		-- 30 位为 1 的肯定大于 30 位为 0 的
			--- 29 位为 0 的肯定大于 29 位为 1 的
				---- ... 以此类推，形成树的结构
```

正是因为这样的特性，启发我们可以采用 Trie 树的形式对所有数字进行存储，然后再进行查询比较：

- 将每个数以 31 位二进制的形式进行表示（因为数的范围是 $0- 2^{32} $）
- 先插入（将新数插入 Trie 树中，构建起来更大的树，树的每个节点代表一位，整体思路和上面的基础是完全相同的）
- 后查询（得到和目标树异或最大的数）

```c++
/*
    @author Karry 
    @date on 2023/8/16.
    @comment Day 16 最大异或对 MDP
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10, M = 31 * N; // N 是数的个数范围，M 表示 Trie 树的节点数范围（每个节点是 1 位，每个数的位数范围是 0 - 31）
int a[N]; // 输入的数组
int trie[M][2], idx; // MDP 问题的 trie 树，因为每个子节点只有可能是 0 or 1，idx 是节点标识

// 插入输入的数
void insert_trie(int x) {
    int p = 0; // 从根节点开始

    // 从高位到低位把数的每一位都扣出来
    for (int i = 30; i >= 0; i--) {
        int u = x >> i & 1; // 取出数的第 i 位
        if (trie[p][u] == 0) trie[p][u] = ++idx; // 将数的第 i 位插到 trie 树中
        p = trie[p][u]; // 访问到下一位
    }

    // 一个数就成功插入其中了
}

// 查找目前的 Trie 树中与 x 异或最大的树
int fine_trie(int x) {
    int p = 0, target_num = 0; // 从根节点开始，target_num 初始化为 0

    // 从高位到低位把数的每一位扣出来
    for (int i = 30; i >= 0; i--) {
        int u = x >> i & 1; // 取出数的第 i 位
        if (trie[p][!u] != 0) {
            p = trie[p][!u]; // 如果和该位不同的数存在（异或值更大）就往该方向移动
            target_num = target_num * 2 + !u; // 每移动一次算一次 num 值
        } else {
            p = trie[p][u]; // 否则只能退而求其次
            target_num = target_num * 2 + u; // 每移动一次算一次 num 值
        }
    }

    return target_num;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i]; // 输入数组

    // mdp
    int res = 0;
    for (int i = 0; i < n; i++) {
        insert_trie(a[i]); // 先插入
        res = max(res, a[i] ^ fine_trie(a[i])); // 再查找
    }

    cout << res;
}
```

### 2.6 UNION-SET

> 第六种数据结构，并查集。在面试的时候经常出现：思维性比较强 + 代码短
>
> 并查集的基本操作（为了简化数据合并的复杂性，以近乎 $O(1)$ 的方式快速支持一下操作）
>
> 1. 将两个集合合并
> 2. 询问两个元素是否在一个集合当中
>
> 数据结构实现的基本思路：==每一个集合都用一棵树来进行表示==
>
> - 根节点的编号就是整个集合的编号
> - 每一个节点 x 存储其父节点 p[x]
>
> 具体操作实现的基本思路：
>
> - 既然树根节点的编号是集合的唯一标识，那该如何判断树根呢？
>
>   ```c++
>   定义只有根节点 p[x] == x
>   ```
>
> - 如何初始化这棵树？
>
>   ```c++
>   初始化的时候，可以把范围中的每一个点单独看成一个个集合，反过来说就是有 n 个集合，一个集合中只有一个点，这些集合共同组成了 0 - n 这个数据范围。
>   既然每个树中只有一个点，那就是根节点了呗，直接用上述定义进行初始化即可。
>   ```
>
> - 如何求 x 所在集合的编号？
>
>   ```c++
>   只要找到 x 所在集合的树根即可 while(p[x] != x) x = p[x]; 
>   ```
>
> - 如何合并两个集合？
>
>   ```c++
>   无非就是让两个树进行合并，只要让其中一个树的根节点并到另外一个树上
>   假设 A 集合的编号是 x，也就是说集合根节点 p[x] == x，B 集合的编号是 y，也就是说集合根节点 p[y] = y。
>   这样若是想合并 A 和 B 集合就只需要让 p[x] = y 或者 p[y] = x
>   ```
>
> 优化方式：求解 x 所在集合的编号这个操作时间复杂度还是很高的（需要不断地向上找），因此需要一定的优化
>
> - 路径压缩：将 x 找回根节点的所有点的 p[x`] 都直接赋值为根节点（思路也很简单，既然都在这条路径上，那就说明都在一个集合内，干脆只用查一次）。
>
>   ```c++
>   实现的方式就是采用递归（递归最好的推理方式是画树）
>   find_root(){
>   	if (p[x] != x) p[x] = find_root(p[x]); // p[x] 一直在改变
>   	return p[x];
>   }
>   ```
>
>   

#### [Union Set](https://www.acwing.com/problem/content/838/)

将上面的思路进行实现

```c++
/*
    @author Karry 
    @date on 2023/8/17.
    @comment Day 17 并查集数据结构的应用 - 合并集合（很巧妙的优化思想，以后肯定也能用到）
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 1e5 + 10; // 数据范围
int p[N]; // 存储父节点的数组（以数组的形式来构建树）
int n, m;

// 找到数 x 的集合编号
int find_root(int x) {
    // 不进行优化（很简单）
//    while (x != p[x]) x = p[x];
//    return x;

    // 进行优化（路径压缩 - 采用递归的形式对 p[x] 进行修改）
    if (x != p[x]) p[x] = find_root(p[x]); // 如果 x 不是根节点，就让其父节点为根节点
    return p[x];
}

int main() {
    cin >> n >> m;

    // step 1. 初始化：让范围内的每一个点都单独成为一个集合 (每一个节点都是根节点)
    for (int i = 1; i <= n; i++) p[i] = i;

    // step 2. 合并 or 查找
    string op;
    int a, b; // 两个操作数
    while (m--) {
        cin >> op >> a >> b;

        // 注意在合并与查找的过程中都可以进行路径压缩
        if (op == "M") p[find_root(a)] = find_root(b); // 其中一个数的根节点的父节点指向另一个树的根节点
        else if (op == "Q") {
            if (find_root(a) == find_root(b)) cout << "Yes" << endl; // 如果两个元素的根节点相同就输出 yes
            else cout << "No" << endl;
        } else cout << "wrong input !" << endl;
    }

    return 0;
}
```

#### [Connecting Block](https://www.acwing.com/problem/content/839/)

> 使用数组合并的思路实现无向图的简单操作，存储点的数量这一额外信息

无向图的操作只包含点构成集合的合并与查询，而不涉及路径之类的信息，只是多了一个统计集合元素个数的操作（相当于维护了一种额外信息），自然联想到在集合合并操作中保证节点数量的加和即可。

思路如下：

1. 整体的数据结构思路与 Union Set 完全一致
2. 增加一个 cnt_point[N] 数组，存储每个根节点所在集合的元素个数（只有根节点的值才有意义）
3. 每次合并的时候都维护一个新的根节点的 cnt_point[x] 值，因此需要注意合并的方向。如果说两个根节点已经在同一颗树上了，那就不用管这个事情了。

```c++
/*
    @author Karry 
    @date on 2023/8/17.
    @comment Day 17 在 union set 的基础上增加一个数集合元素个数的操作
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 1e5 + 10;
int p[N], cnt_points[N]; // 增加了一个 cnt_points 数组来维护根节点所在集合的节点数量

int find_root(int x) {
    if (x != p[x]) p[x] = find_root(p[x]);
    return p[x];
}

int main() {
    int n, m;
    cin >> n >> m;

    // step 1. 初始化 union set
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        cnt_points[i] = 1;
    }

    // step 2.
    string op;
    int a, b; // 两个操作数
    while (m--) {
        cin >> op;
        if (op == "C") {
            // 集合合并
            cin >> a >> b;
            if (find_root(a) != find_root(b)) { // 如果已经在同一个集合中了，那就直接跳过即可
                // 注意这个地方的顺序，一定要先加，然后再修改树的连接
                cnt_points[find_root(b)] += cnt_points[find_root(a)]; // 元素个数的变化
                p[find_root(a)] = find_root(b); // 根节点变化
            }
        } else if (op == "Q1") {
            // 查询两个节点是否在同一个树内
            cin >> a >> b;
            if (find_root(a) == find_root(b)) cout << "Yes" << endl;
            else cout << "No" << endl;
        } else if (op == "Q2") {
            // 查询节点所在集合元素的个数
            cin >> a;
            cout << cnt_points[find_root(a)] << endl;
        } else cout << "wrong input !";
    }

    return 0;
}
```

#### [Food Chains](https://www.acwing.com/problem/content/242/)

> 并查集的核心优势在于其可以在维护集合关系的同时维护一些额外的信息，比如上面的点的数量，以及本题目中食物链中的相关定义。这两个题目其实同属一种类型。

这道题目的核心解决思路就是采用并查集来维护食物链的额外信息。

出发点在于三类动物就之间的关系是一种集合操作，既然是集合操作我们就可以用并查集将有关系的点放在一个集合中来辅助进行维护。

但此处点与点关系的更加复杂了（存在同类和吃两种关系），而不像是之前只有同类这一种关系，直接就放到一个集合中就可以了。如何同时维护两种关系呢？现在我们要想一下，并查集底层的树结构除了集合的信息，还有什么信息可以用？自然想到距离，尤其是和根节点的距离，因此我们可以在与根节点的距离上做文章（考虑到最多有三种情况，因此采用 mod 3）：

- 如果距离 mod 3 = 1，表示可以吃根节点
- 如果距离 mod 3 = 2，表示可以被根节点吃
- 如果距离 mod 3 = 0，表示和根节点是同类

一个更加直观的理解思路，把吃与被吃的关系放在一代一代上，距离的概念就转换为了代差

```c++
根节点是     0 代
吃根节点的是  1 代
吃第 1 代的是 2 代， 2 代可以被 0 代吃
吃第 2 代的是 3 代， 3 代肯定和 0 代是同一代
```

这个地方之所以选择和根节点的距离，是因为我们完全不需要 care 到底是哪一只动物能吃哪一只动物的精确关系，只需要 care 哪一代动物能吃哪一代动物的大类关系，所以我们只需要维护和根的距离能够使我们判断其属于哪一代就可以了，这样的思路使我们成功将复杂度由 $O(N^2)$ 优化为了 $O(N)$。

```c++
/*
    @author Karry 
    @date on 2023/8/18.
    @comment Day 18 用并查集解决食物链问题，在 union set 的基础上开一个表示到根节点距离的数组，维护附加关系
*/

#include<iostream>

using namespace std;

const int N = 5e5 + 10;


/*
 * p[N] 表示并查集底层的树（存储节点 n 的父节点为 p[n]
 * d[N] 数组始终表示点 n 到其到父节点 p[n] 的距离 || 深刻理解 d数组的含义是理解本题的核心
 */
int p[N], d[N];


int find_root(int x) { // 找根节点 + 路径压缩 + 距离维护
    if (p[x] != x) {
        /*
         * 一定是先进行递归，因为递归不仅是求解根节点的过程，还是进行压缩的过程
         * 一方面，这样压缩后 x 父节点 p[x] 的父节点就是 root 了
         * 另一方面，d[p[x]] 所表示的就是父节点到根的距离了
         */
        int root = find_root(p[x]);

        d[x] += d[p[x]]; // x 到父节点的距离 = x 到的父节点的距离 + 父节点到其父节点（根）的距离 （先递归后算本质是一种自 root 向下算的方法，才是对的！）
        p[x] = root; // x 指向根

        // 可以看出此时 d[x] 仍然维护着 点 x 到其到父节点 p[x] 的距离，只不过此时 p[x] 为 root，因此也是 x 到根的距离
    }

    return p[x];
}

int main() {
    int n, m; // n 表示输入数的范围 | m 表示操作次数
    cin >> n >> m;

    for (int i = 1; i <= n; i++) p[i] = i; // 初始化并查集

    int false_res = 0; // 初始化假话的数量

    while (m--) {
        int op, x, y; // 操作符 和 操作数
        cin >> op >> x >> y;

        if (x > n || y > n) false_res++;
        else {
            int x_root = find_root(x); // x 所在树的根节点
            int y_root = find_root(y); // y 所在树的根节点

            if (op == 1) { // x y 为同类 判断
                if (x_root == y_root && (d[x] - d[y]) % 3 != 0) false_res++; // 两个节点在同一棵树上了，就说明这句话是判断，不满足同类条件=>是假话
                else if (x_root != y_root) { // 两个节点不在同一颗树上，就说明这句话不是判断，需要操作
                    p[x_root] = y_root; // 树的合并，将 x_root 合并到 y_root 下
                    d[x_root] = d[y] - d[x]; // 合并前 d[x_root] = 0，合并后需要满足 (d[x] + d[x_root] - d[y]) mod 3 == 0
                }
            } else if (op == 2) { // x 吃 y 判断
                // ！！！！ 注意 这个地方的判定条件不能写成 (d[x] - d[y]) % 3 != 1 因为二者之差可能为负数 ！！！！ //
                if (x_root == y_root && (d[x] - d[y] - 1) % 3 != 0) false_res++; // 两个节点在同一棵树上了，就说明这句话是判断，不满足同类条件=>是假话
                else if (x_root != y_root) { // 两个节点不在同一颗树上，就说明这句话不是判断，需要操作
                    p[x_root] = y_root; // 树的合并，将 x_root 合并到 y_root 下
                    d[x_root] = d[y] - d[x] + 1; // 合并前 d[x_root] = 0，合并后需要满足 (d[x] + d[x_root] - d[y]) mod 3 == 1
                }
            }

        }

    }

    cout << false_res << endl;
    return 0;
}
```

这个题目代码书写有一个很大的难点就是==如何理解 d[x] 和更新 d[x]==，在此贴出解释：

- find(x)有两个功能： 路径压缩 和 更新 d[x] 。
- 假设有一棵树 a -> b -> c -> d， 根节点为 d。d[b]一开始等于 b、c 之间的距离，再执行完路径压缩命令之后，d[b] 等于b、d之间的距离。 
- d[a] += d[b]：为了确保d[a]等于节点 a、d 的距离，d[b] 必须等于 b 、d 的距离，所以要先调用 find(b) 更新d[b]， 同时 p[x] = find(b) 会改变 p[x] 的值，结果就会变成d[a] += d[d]，所以先用一个变量把p[a]的值存起来。

==这个题目是至今学到的最难的题目，有很多的坑，需要仔细思考才能破解！==

### 2.7 HEAP

> 第七种数据结构，堆。此处我们仍然采用数组进行模拟
>
> 堆的结构形式，本质是一个==完全二叉树==，分为小根堆和大根堆两类：
>
> - 小根堆：每个节点的值都小于等于子节点的值（递归的思想），因此根节点是整棵树的最小值。
> - 大根堆：每个节点的值都大于等于子节点的值，因此根节点是整棵树的最大值
>
> 因此要想实现这样的一种数据结构，就需要一种全新的存储方式：采用一个一维数组，本质来说所有的完全二叉树都可以如此存储。
>
> ```c++
> 一维数组 heap[N] 存堆：
> 	- 下标 1 存储根节点
> 	- 下标 x 的节点的左子节点对应的下标为 2x
> 	- 下标 x 的节点的右子节点对应的下标为 2x + 1
> 因此根节点的左子节点下标为 2，右子节点的下标为 3
> ```
>
> 堆的基本操作有：
>
> - 插入一个数
> - 求集合当中的最小值
> - 删除最小值
> - 删除任意一个元素
> - 修改任意一个元素
>
> ```c++
> 堆的所有操作的底部核心就是两个操作 down(index) 和 up(index) ，保证小根堆始终保持性质
> - down(index) 指小根堆失特性时，让新插入在 index 的大值向下沉，每次沉的操作是（根节点、左孩子、右孩子）三个点进行比较，把最小值放在根节点上，新插入的大值和最小值交换，依次到底。
> - up(index) 指小根堆失特性时，让新插入在 index 的小值向上浮，每次浮的操作是（根节点、左孩子、右孩子）三个点进行比较，把最小值放在根节点上，新插入的小值和根交换，依次到根。
> ```

下面就开始考虑如何在一维数组存储结构的基础上，通过两种操作的组合实现堆

- 插入一个数：插在堆的尾节点上，然后 up 上来

  ```c++
  heap[++h_size] = x; // 将数插入 （下标是从 1 开始的） h_size 存储当前 heap 的尾节点下标
  up(h_size); // 对插入点下标 h_size 进行上浮调整
  ```

- 求集合当中的最小值：直接取出根节点即可

  ```c++
  min = heap[1]; // 取出根节点
  ```

- 删除最小值：按理来说直接删掉根节点（数组的头）即可，但对于数组而言，很难直接删除头，所以在这的思路是根节点取到尾节点的值，然后把尾节点删去实现间接删除。

  ```c++
  heap[1] = heap[h_size]; // 根节点取尾节点的值交换一下
  idx--; down(1); // 删掉尾节点 + down(浮上去的根节点) 实现间接根节点删除
  ```

- 删除任意一个元素：和上面的删除最小值是一样的

  ```c++
  heap[k] = heap[h_size]; // 待删除的点的值取尾节点的值
  idx--; down(k); up(k); // 删掉尾节点 + down or up 尽管写了两个，但是只会执行一个
  ```

- 修改任意一个元素：思路和删除又是一样的

  ```c++
  heap[k] = x; // 修改元素
  down(k); up(k); // 尽管写了两个，但是只会执行一个
  ```

除了以上的操作以外，还有一个点需要考虑，那就是==如何高效地创建一个堆？==

- Way 1. 一个个值插入，这样的时间复杂度为 $O(nlog_2n)$

- Way 2. 从倒数第二层开始 down，直至尾节点

  ```c++
  for(int i = idx / 2; i; i--) down(i); 
  ```

#### [Heap Sort](https://www.acwing.com/problem/content/840/)

堆排序是数据结构的一个很好的应用，只要搭建了堆后，发现堆排序就很简单了，只需要用到三个操作，所以在这不用完整地模拟出来整个堆，只需要实现一个 down() 即可

- 构建堆
- 取堆的最小值
- 删除根节点

```c++
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
```

#### [Heap](https://www.acwing.com/problem/content/841/)

模拟堆实现的操作其实并不难，上面已经写出来一大半了，而且 up 很自然地就可以推出来。但是难点在于，==如何维护插入的第 k 个数的位置 ？==

```c++
我们只能依附下标 idx 对 heap 进行操作，因此必须要用新的数组来存储下标和插入数的顺序之间的关系。
一方面，肯定要维护一个 heap_idx_of_k[N]; 存储第 k 个数的下标是多少
另一方面，还是那句话，我们始终都是依附下标 idx 进行操作，那么当进行 down or up 调整交换的时候，如果只有 heap_idx_of_k[] 是很不方便的：
	- 要先【遍历】该数组，分别找到两个下标对应第几个插入的数（数组元素向下标的反向映射）
	- 然后再对 heap_idx_of_k[] 对应的值交换
遍历显然是很慢的，因此我们就想着同时维护一个反向映射 k_of_heap_idx （下标 idx 存储的是第几个数）明显这二者是反函数关系
	- if ` k_of_heap_idx[i] = k
	- then ` heap_idx_of_k[k] = i
这样的话，我们在找下标对应第几个插入的数时，只需要直接访问 k_of_heap_idx[]
```

因此，为了多这么一个操作，本质是在 down or up 进行元素维护堆的同时，维护两个数组

```c++
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
             * 这种写法是可以的，因为不涉及到下标修改
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
```

### 2.8 HASH 

> 第八种数据结构：哈希表。
>
> 首先我们要理解一下哈希表的用处，实现数值下标范围的压缩（有点类似于离散化，方式是排序 + 去重 + 二分查找），比如将 $0 \sim 10^9$ 的范围映射到 $0 \sim 10^5$ 上。更具体一点在 $-10^9 \sim 10^9$ 范围的下标下进行 $10^5$ 以内个操作，也就是说在很大的下标范围内，只有很少部分的下标被访问过（有意义的点很少）。
>
> 面对上述的问题，我们希望存在一个函数 $hash(x)$ 能将 $-10^9 \sim 10^9$ 这一范围映射到 $0 \sim 10^5$ 上，将这个函数称作哈希函数。至此我们可以明显看出离散化是一种较为特殊的哈希函数（因为其要求操作下标必须保序而且无重复），现在我们想要设定更为一般的哈希方式，常用的函数就是取余：$hash(x) = x \ mod\ 10^5$ （==明显会有冲突==<两个不同的数字映射到同一个数上>），==注意在这个地方取模最好模上大于边界的第一个质数，而且尽可能离2的次方远一些==。这种冲突是必须要进行处理的，根据处理方式的不同就可以将哈希表分成：
>
> - 拉链法：处理冲突的方式是串糖葫芦，一个坑可以串很多个人。
>
>   ```c++
>   step 1. 开一个 10^5 大小的数组 h[N] 存储 hash(x)
>   step 2. 开始往数组里面存数
>   	- hash(11) = 3; 那么就在数组 h 中下标为 3 处开一个拉链头放 11
>   	- hash(3) = 3; 在数组 h 中下标为 3 处继续往拉链头上插入数字 3
>   	- 顺次操作
>   step 3. 最终就在某些下标处形成了长长的“拉链”（拉链的结构是单链表）
>   step 4. 想要查询某个数字 y 先求 hash(y) 然后在以 hash(y) 为头的单链表中从头依次访问寻找 y
>   ```
>
> - 开放寻址法：处理冲突的方式是找厕所，顺次寻找，直至找到！
>
>   ```c++
>   step 1. 开一个 2 到 3 倍于 10^5 大小的数组 h[N] 存储每一个 hash(x)
>   step 2. 计算 hash 值，开始往数组中存数字
>   	- hash(11) = 3; 没有冲突，h[3] = 11
>   	- hash(3) = 3; 存在冲突了，那么就从 3 开始往后找，直至找到 h[4] 是空的，就放进去
>   step 3. 这样最终就形成了一个一维的 hash 表
>   step 4. 想要查询某个数字 y 先求 hash(y) 然后从 hash(y) 往后寻找，直至找到不为空且值为 y 的地方。
>   ```

#### [Hash](https://www.acwing.com/problem/content/842/)

具体实现上来看代码实现：

1. ==拉链法==：核心是单链表的维护，直接将 h[N] 作为每一个链表的头，初始化为 -1，然后每次都往头部插入。这也就是说，虽然我们仍然只使用一个一维数组来维护链表，但是其本质有多个头，逻辑上是多个链表。要想访问哪个链表就必须通过某个头依次查询。

   ```c++
   /*
       @author Karry 
       @date on 2023/8/20.
       @comment Day 20 实现散列表（采用 拉链法）
   */
   
   #include<iostream>
   #include<cstring>
   
   using namespace std;
   
   const int N = 100003; // 大于 1e5 的第一个质数
   
   int h[N]; // hash 表数组 （每个元素存储的是链表的表头）
   int e[N], ne[N], idx; // 单个数组表示多维度链表
   
   // 向 hash 表中插入元素（模仿在单链表表头插入）
   void insert(int x) {
       // 将数映射到 0 ~ 10^5 上，之所以不能直接取 mod 是因为要防止负数出现
       int k = (x % N + N) % N;
   
       // 将数 x 进行插入链表头中
       e[idx] = x;
       ne[idx] = h[k]; // h[k] 标识的是 head
       h[k] = idx; // head 指向头 idx
       idx++; // idx 后移动
   }
   
   // 在 hash 表中找到数 x
   bool find(int x) {
       // 先求出来映射值
       int k = (x % N + N) % N;
   
       // 从头开始找
       for (int i = h[k]; i != -1; i = ne[i])
           if (e[i] == x) return true;
       return false;
   }
   
   int main() {
       int n;
       cin >> n;
   
       // 初始化哈希表。因为哈希表的每一个元素代表的是链表表头，所以初始化为 -1 就很自然了！
       memset(h, -1, sizeof(h));
   
       string op; // 操作符
       int x; // 操作数
       while (n--) {
           cin >> op >> x;
           if (op == "I") insert(x); // 插入头部的操作
           else if (op == "Q") {
               if (find(x)) cout << "Yes" << endl;
               else cout << "No" << endl;
           } else cout << "Wrong Input" << endl;
       }
   
       return 0;
   }
   ```

2. ==开放寻址法==：只需要维护一个数组，而且核心只用 care 一个函数 find 如果数在 hash 表中就返回下标，如果不在就返回应该存储的下标。

   ```c++
   /*
       @author Karry 
       @date on 2023/8/20.
       @comment Day 20 开放寻址法实现 hash 表
   */
   
   #include<iostream>
   #include<cstring>
   
   using namespace std;
   
   const int N = 200003; // 大于 2 * 1e5 的第一个质数
   const int null = 0X3f3f3f3f; // 用一个不可能出现的数标识 hash 表的坑是空的
   
   int h[N]; // hash 表数组
   
   /*
    * 在 hash 表中找到数 x
    * 如果 x 存在就返回 x 的下标
    * 如果 x 不存在就返回 x 应该存储的下标
    */
   bool find(int x) {
       // 先求出来映射值
       int k = (x % N + N) % N;
   
       // 从头开始在单链表中进行寻找
       while (h[k] != null && h[k] != x) {
           k++; // 如果不是空而且还不相等，说明没有找到，那就继续往后面找
           if (k == N) k = 0; // 如果找到了尾部，就回到开头
           // 直到找到目的下标
       }
   
       return k;
   }
   
   int main() {
       int n;
       cin >> n;
   
       // 初始化哈希表，让每一个坑都为空
       // memset这个函数是按字节来赋值的，int 有 4 个字节，所以把每个字节都赋值成 0x3f 以后就是 0x3f3f3f3f
       memset(h, 0x3f, sizeof(h));
   
       string op; // 操作符
       int x; // 操作数
       while (n--) {
           cin >> op >> x;
           int k = find(x);
           if (op == "I") h[k] = x; // 插入操作：如果之前没有插入过 x 那么直接在应该插入的位置赋值即可；如果之前已经插入过 x 了，再赋值一遍也无所谓
           else if (op == "Q") {
               if (h[k] != null) cout << "Yes" << endl; // 如果存在返回的就应该是之前插入的位置
               else cout << "No" << endl; // 否则该插入的位置的数值一定是空
           } else cout << "Wrong Input" << endl;
       }
   
       return 0;
   }
   ```

   
