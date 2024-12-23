# Note of Systematic Learning

> Karry



## 1. FOUNDATION

### 1.1 SORT

#### [Quick Sort](https://www.acwing.com/problem/content/description/787/) | LeetCode 912.

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

#### [K Number (Quick Select)](https://www.acwing.com/problem/content/788/) | LeetCode 215.

快速选择，和上述快速选择一脉相承，是快速排序算法的一种应用。**注意**：LeetCode 上是找最大的 k^th number，我的代码中实现的是选最小的 k^th number，修改思路很简单，快速排序调整成由大到小即可。

#### [Merge Sort](https://www.acwing.com/problem/content/789/) | LeetCode 912.

归并排序（时间复杂度 $nlog_2n$），同样是==分治==的思想，主要步骤如下：

```c++
设定数组 q 左右两边的下标为 l 和 r
Step 1. 确定分界点 mid = ( l + r ) / 2 < 是下标 >
Step 2. 递归排左右两边（左右两边必须是有序的，所以需要先递归）
Step 3. 将排好的归并起来 *重点*
```

==实现归并==：具体实现方法为==双指针==，两个有序的数组分别设置一个指针不断往后跑。归并排序是稳定的（稳定的概念：相同的数排序后相对位置是否发生改变）

#### [Inversion Number](https://www.acwing.com/problem/content/790/) | LeetCode LCR 170.

思路同样是==分治==，该题目本质上是归并排序的一个应用，首先找到中点，将所有的逆序对情况分为三种：

```python
1. 逆序对在左半边 （直接加上）
2. 逆序对在右半边（直接加上）
3. 逆序对被中点分割（两边排序与否，不产生影响的）
```

### 1.2 DICHOTOMY

> 二分可以划分为`整数二分`和`实数二分`。二分的本质并不是单调性，而是存在一种划分方式。也就是说：有单调性的可以二分，但是没有单调性的也可能可以二分。
>

#### [Number Range](https://www.acwing.com/problem/content/791/) | LeetCode 704.

二分的本质是可以找到一个确定的边界将原结构一分为二。 二分算法一定是可以找到边界的，只不过边界的答案不满足性质，那就说明这个题目无解了。解决这些题目共有两个模板，关于如何选择，有一个迅速的口诀 ==左 1 右 0==（来自于边界是否会死循环）：

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
        if(check(mid)) r = mid; // here check(mid) is q[mid] >= num;
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

#### [Cubic Root](https://www.acwing.com/problem/content/792/) | LeetCode 69.

没有边界问题了，但是有精确值问题，如果是保留 n 位小数，一般是让 l 和 r 之间的差别小于 $10^{-(n + 2)}$ ，同时注意变量类型即可。在解 LeetCode 求平方根的时候，遇到了输出整数数值的边界问题，这个地方只需要加一个 Check 数值即可。另外，在求平方根和三次方根这种数学问题的时候，往往有更简单的数值求解法，比如 LeetCode 对[**平方根求解**](https://leetcode.cn/problems/sqrtx/solutions/238553/x-de-ping-fang-gen-by-leetcode-solution/)给出的牛顿下降法，或者算子替代法。

#### Divide | LeetCode 29.

两数相除，也用到了二分查找的方法，详细解释看代码。

### 1.3 HIGH-PRECISION

> 所谓高精度，就是指运算的数字超过了语言设定的变量所能表达的范围，只能换一种方式进行表示。

大整数：==整数的位数长达 10e6==

基本的思路：

1. ==大整数的存储==：这么大的整数用 int, long long 都表示不了，把大整数的每一位都依次存到数组中（Vector ）。存储思路是让高位存在数组的小下标位置。
2. ==运算的过程==：本质就是模拟人工加减乘除的过程，其实算法的本质就是对人类思考的模拟

#### [ADD](https://www.acwing.com/problem/content/793/) | LeetCode 415

首先将文本转化为数字，用数组来存储文本标识的数据。对两个数组进行操作，模拟人工算加法的过程，算法上无非就是加法和进位的思想，但是在功能上需要注意使用 Vector 或 String 的相关操作。核心是采用一个临时变量来存储加和结果，进行进位计算。

#### [SUB](https://www.acwing.com/problem/content/794/) 

较比加法而言，减法将进位变为了借位，没有什么本质区别。

#### [MUL](https://www.acwing.com/problem/content/795/) | LeetCode 43

因为这个地方的除数是一个比较小的数，可以直接用 int 进行存储，所以乘除的思想都是直接进行计算。这样的话乘和加的思想完全是一脉相承了。ACWing 上是一个简单的版本，如果 Num2 也变成了和 Num1 一样的情况，就变成了两个大数相乘，就需要真正用到位和位相乘的计算了，在这给出了一个简单的用加法实现乘法的功能。

#### [DIV](https://www.acwing.com/problem/content/796/)

除法的逻辑看起来很难，但是仔细看的话其实并不复杂，和之前的进位 / 借位 的核心逻辑不同，其核心是余数。

### 1.4 PREFIX-SUM AND DIFFERENCE

> 前缀和和差分本质是一个互运算，二者所用的核心的原理是前缀求和中的递推以及集合代表个体的思想，这种思想值得思索。

#### [PreSum](https://www.acwing.com/problem/content/797/) [**Ref**](https://blog.csdn.net/fuxuemingzhu/article/details/120132922) ｜ LeetCode 1480、303、643

前缀和问题简单来说就是求数组的一段数字的和，降低求解数组和的复杂度，核心在于：

- 计算前缀和的扫描算法，得到从 0 到 n 的和
- 边界求解的公式，通过边界差进行计算

先扫一遍完成存储后，再使用所存储的内容进行辅助运算。这样就可以避免每一次的复杂度都是 $n$ 了

#### [Submatrices Sum](https://www.acwing.com/problem/content/798/) ｜ LeetCode 304

将上述的一维前缀和拓展为二维前缀和，核心还是思考如下两个问题：

1. 如何计算和 ？
2. 如何利用和求解 ？

同样的还是递推思路，只不过从一维变为了二维。

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

#### [KMP](https://www.acwing.com/problem/content/833/)

> [延伸 blog](https://blog.csdn.net/raelum/article/details/128823560)，前缀和后缀的理解是这个算法的关键

==算法本质==：求子串是 string 中的重要问题，暴力求解的思路其实很简单，那就是在子串和母串上分别都开一个指针，然后进行逐个扫描即可，这种算法也被称为 BF 算法，因为在母串上会有指针回溯，所以复杂性极高，实用性不强，KMP 的本质就是为了减少时间复杂度。

==算法思想==：其实和单调栈和单调队列一样，暴力算法都很简单，但也都是改良算法的出发点。KMP 的出发点肯定是暴力算法（BF）

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

通过上面的思考，就能得到 KMP 算法的整体逻辑了：（注意子、母指针错位的思路）

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
注意，此处我已经深刻理解了 kmp 的本质含义所在，但是无奈想用最淳朴的方法写出，熬到凌晨 2 点半，最终放弃，选择更加 fancy 的做法！
// 以后若是有时间，一定要再补回来 ！！！！ //
  /*
    @author Karry 
    @date on 2023/8/14.
    @comment 凌晨所做，发现自己的思路行不通，数组下标从 0 开始，记住下面的做法
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

按照上述思路，完成以下两种方式的 hash 书写

1. ==拉链法==：核心是单链表的维护，直接将 h[N] 作为每一个链表的头，初始化为 -1，然后每次都往头部插入。这也就是说，虽然我们仍然**只使用一个一维数组来维护链表，但是其本质有多个头，逻辑上是多个链表**。要想访问哪个链表就必须通过某个头依次查询。==重复的元素会有重复的节点（尽管都在一个坑内）。==

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
       ne[idx] = h[k]; // h[k] 标识的是每一个链表的 head 节点位置
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

2. ==开放寻址法==：只需要维护一个数组，而且核心只用 care 一个函数 find 如果数在 hash 表中就返回下标，如果不在就返回应该存储的下标，如果是进行插入那就将该数完成制指定位置的插入，重复的话也只会在一个坑位插入；如果是查询发现该坑内的树为空的话那就说明该数不存在。==重复的数也都只会用一个坑==

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


#### [String Hash](https://www.acwing.com/problem/content/843/)

一种特殊的 hash 方式，不是数与数之间的映射方式，而是字符串与数之间的映射。核心目标是将字符串通过 hash 函数，得到每一个字符串对应的哈希值，进而将字符串映射到 $0\sim Q-1$ 范围的数值上。具体方式如下：

- 为每一个字符赋予一个确定的值（A-1, B-2, C-3, D- 4....）

- 确定 $p$ 进制计算规则保证多样性

  ```c++
  对于 "ABCD" 这个字符串而言，相应的数值就是
  value = (1234)p = 1 * p^3 + 2 * p^2 + 3 * p^1 + 4
  ```

- 确定余数 Q 进而实现范围映射

  ```c++
  hash(value) = value % Q
  ```

- 一些经验值

  ```c++
  p 取 131 或 13331
  Q 取 2^64 (在实际操作中往往用 unsigned long long 这个数据类型进行替代)
  ```

举个例子对于字符串 "ABCDEF" 而言，散列表的存储前缀的 hash 值，具体规则如下

```c++
h[0] = 0; // 表示开头
h[1] = hash("A"); // (1 * p ^ 0) % Q; 存储第一个前缀
h[2] = hash("AB"); // 存储第二个前缀
h[3] = hash("ABC"); // 存储第三个前缀
h[4] = hash("ABCD"); // 存储第四个前缀
h[5] = hash("ABCDE"); // ....
```

这样存储有一个明显的好处，就是通过这种方式：我们可以很方便地求出原字符串中所有子串的 hash 值，这样在对任意子串进行比较的时候时间复杂度就是 $O(1)$ 了

```c++
比如对于一个很长的串，现在已经知道：
- h[L - 1] 存储从第 1 个字符到第 L - 1 个字符子串的 hash 值，因此其第一位对应 p^(L - 2) 
- h[R] 存储从第 1 个字符到第 R 个字符子串的 hash 值，因此其第一位对应 p ^ (R - 1)
  
那么从第 L 个字符到第 R 个字符所构成的子串的 hash 值为: h[R] - h[L - 1] * p ^ (R - L + 1) 直接可以通过下标算出来，然后再进行相关的计算即可。
```

==对于一些复杂的题目，都可以通过字符串散列表的方式简便求解，比 KMP 方便得多==

```c++
/*
    @author Karry 
    @date on 2023/8/21.
    @comment Day 21. 字符串哈希算法，理解如何将字符串转存到一个散列表中，并借助此解决字符串相关问题
*/

#include<iostream>

using namespace std;

typedef unsigned long long ULL; // 用 ULL 这一数据类型，可以免去取余的过程
const int N = 1e5 + 10; // 注意这个地方所求的的 hash 值表证的含义不是下标，而是字符串对应值，因此 N 就是数组长度，千万别搞混了
const int P = 131; // 按照经验值进行设定
ULL h[N], p[N]; // 使用 p[N] 来存储 p^x 次方(p[x] = p^x)，进而方便运算
char str[N];

// 找到从 [l, r] 这个区间的子串对应的 hash 值
ULL find_str_hash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    int n, m;

    scanf("%d%d%s", &n, &m, str + 1); // 字符串下标从 1 开始，都选用这种输入方法

    p[0] = 1; // p^0
    for (int i = 1; i <= n; i++) {
        p[i] = P * p[i - 1]; // p ^ i 直接存储到 p[i] 中，方便后续直接调用计算
        h[i] = h[i - 1] * P + str[i]; // 遍历前缀构造 hash 表
    }

    int l1, r1, l2, r2;
    while (m--) {
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if (find_str_hash(l1, r1) == find_str_hash(l2, r2)) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}
```

借助这个思想我们也可以解决 kmp 那道题目了（很有成就感的一件事情！）

```c++
/*
    @author Karry 
    @date on 2023/8/21.
    @comment Day 21 用字符串 hash 的方法解决找子串的问题（等效于 kmp 算法）
*/


#include<iostream>

using namespace std;

typedef unsigned long long ULL; // 用 ULL 这一数据类型，可以免去取余的过程
const int NS = 1e5 + 10, NP = 1e6 + 10;
const int P = 131; // 按照经验值进行设定
ULL h[NP], p[NP], h_s;
int n, m;
char str_s[NS], str_p[NP];

// 找到从 [l, r] 这个区间的子串对应的 hash 值
ULL find_str_hash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    scanf("%d%s", &n, str_s + 1); // 字符串下标从 1 开始，都选用这种输入方法
    scanf("%d%s", &m, str_p + 1); // 字符串下标从 1 开始，都选用这种输入方法

    // step 1. 求解模式串对应的 hash 表
    p[0] = 1; // p^0
    for (int i = 1; i <= m; i++) {
        p[i] = P * p[i - 1]; // p ^ i 直接存储到 p[i] 中，方便后续直接调用计算
        h[i] = h[i - 1] * P + str_p[i]; // 遍历前缀构造 hash 表
    }

    // step 2. 求解子串对应的 hash 值
    for (int i = 1; i <= n; i++) h_s += str_s[i] * p[n - i];

    // step 3. 遍历母串求解 O(n) 的时间复杂度
    for (int i = 1; i <= m - n + 1; i++) if (find_str_hash(i, i + n - 1) == h_s) printf("%d ", i - 1);

    return 0;
}
```



## 3. SEARCH AND GRAPH THEORY

将世间万物抽象为图节点，将关系抽象为边进行处理，核心是三大问题。

dfs 和 bfs 做为==**经典的搜索算法**==，dfs 是一条路走到黑直到能找到结尾，但无法保证路径最短；bfs 则是一层层往下推，直至每一个点都遍历完成没有新的情况产生，因为有一层层的概念所以可以记录路径距离，进而找到最短路径。二者相通之处在于都只需要对所有点进行一次遍历，因此需要记录下点是否某点是否被遍历过。

之后提到几个==**经典的最短路径算法**==，是对于图而言最重要的算法，是图中最常见的考察内容。单源最短路问题当然可以重复应用得到多源最短路的解，但是较比直接使用多源最短路问题而言，时间复杂度肯定更高，这就需要多源汇最短路。

<img src="/Users/karry/Pictures/NoteImages/image-20230829232923880.png" alt="image-20230829232923880" style="zoom:50%;" />

然后就是==**两类最小生成树算法**==，一个是 Prim 一个是 Kruskal

<img src="/Users/karry/Pictures/NoteImages/image-20230907003226269.png" alt="image-20230907003226269" style="zoom:50%;" />

最后是**==二分图算法==**，两种方式，一是染色法，一是匈牙利算法

<img src="/Users/karry/Pictures/NoteImages/image-20230907003345470.png" alt="image-20230907003345470" style="zoom:50%;" />

### 3.1 DFS - search it （一条路走到黑）

dfs（深搜）俗称为暴力搜索，关键是如何按照顺序进行输出。深度搜索的含义不言而喻，搜索过程可以用树的形式来呈现，就是一遍遍撞南墙（走到终点）后**回溯**到可以继续往下走的位置，和递归的本质是一样的（完全没有必要区分概念）。

#### [Ordinal Number](https://www.acwing.com/problem/content/844/)

这道题最难理解的地方其实是如何进行地不断回溯：

- 到底（有了 n 个数字）之后 return 很好理解
- 但当回溯到 n 个数字之前时，依靠 i 指针到头进行的回溯（这是系统辅助进行的自动回溯）

借助上述两条回溯特性，同时依靠这 i 指针时刻**向前移动**就可以实现全排列，而且是字典顺序。

```c++
/*
    @author Karry 
    @date on 2023/8/22.
    @comment Day 22. 进入第三章搜索与图论（离散数学的重要意义所在）
*/

#include<iostream>

using namespace std;

const int N = 10; // 因为这道题最多只有可能有 7 个数字，稍微多开几个即可
int n;
int path[N]; // 存储路径的数组
int st[N]; // 存储 0 ~ n 之间每个数字状态的数组，被用着（在路径里面）就是 true 否则就是 false

// dfs function 从 u 开始寻找 （u 就是深度）
void dfs(int u) {
    if (u == n) { // u = n; 说明找到树的最后一级了，也就说明路径到头了
        for (int i = 0; i < n; i++) cout << path[i] << " "; // 输出路径结果
        cout << endl;
        return; // 返回上一级
    }

    for (int i = 1; i <= n; i++) // i 指针从前往后走直到遍历完整，可以保证前后顺序，数字从 1 开始所以 i 从 1 开始
        if (!st[i]) {
            path[u] = i; // 将数字 i 放到路径中
            st[i] = true; // 数字 i 已经被用过了
            dfs(u + 1); // 往下走一级
            st[i] = false; // 一旦跳出就需要进行向上回溯，刚被用过的数就自动弹出不再被用
        }

    // return; // 这个 return 是系统自带的，可以不写！

}

int main() {
    cin >> n;
    dfs(0); // 从 0 开始找 （树根部）
    return 0;
}
```

#### [N Queen](https://www.acwing.com/problem/content/845/)

n 皇后问题本质上是一个条件更加复杂的排列问题，因此可以借助条件更加复杂的 dfs 辅助解决

==思路一==：发现每一行只能放一个的情况下，对列进行全排列，然后再剔除不满足条件的点。

```c++
同行肯定不行，同列也肯定不行，因此所有的答案肯定在 1 ～ n 行每个皇后所能够处的列数一定是 1 ～ n 这些数字全排列的子集，所以可以按照后面两步走：

  - 全排列构建树：得到 1 ～ n 的全排列
  - 进行剪枝：判断是否满足两辆都不在一个对角线上的条件，把不符合题解的排列删去

这样就可以得到最后的结果。
```

==思路二==：延续之前的思路，全排列的同时进行条件判断完成减枝（除了看列有没有被用到，还要看对角线有没有被用到）来进行减枝。

```c++
这个地方的思考难点在于如何对对角线进行正确的标识
	- 首先肯定是有正、负两条对角线
	- 坐标轴上在同一对角线上的点 (i_x, u_y) 的正、负对角线应该是一致的 i_x 为数组的列, u_y 表示数组的行 （都是从 0 开始的）
  - 通过简单的数学推导就能发现，考虑对角线标识符 b （数组下标）
  	· 正对角线：存在 u_y = - i_x + b => b = u_y + i_x
  			验证一下，棋盘上的 [0, 2] 和 [1, 1] 和 [2, 0] 就在一条对角线上，b 都为 2
  	· 反对角线：存在 u_y = i_x + b => b = u_y - i_x，但是这样就可能出现负数
  		所以加上一个偏移量防止负数的出现 b = u_y - i_x + n
  			验证一下，棋盘上的 [0, n - 2] 和 [1, n - 1] 就在同一反对角线上，b 都为 2

这样在做每一列的判断时，只要加上关于点对角线的判断即可
/*
    @author Karry 
    @date on 2023/8/23.
    @comment Day 23. n 皇后问题：全排列的过程中，进行条件检验（对角线判断）
*/

#include<iostream>

using namespace std;

const int N = 20; // 因为对角线是行数的 2n - 1 倍，所以开 2 倍肯定够了
int n;
char queen[N][N]; // n rows and n cols.
int col[N], dg[N], ndg[N]; // 标识列、正对角线和反对角线是否被用过了

// 和基本的 dfs 如出一辙，此处 u 标识期盼的第 u 行（从 0 开始）
void dfs_n_queen(int u) {
    if (u == n) { // 到了最后一行就把数组全部输出
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cout << queen[i][j];
            cout << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) { // 指针 i 始终前进
        if (!col[i] && !dg[u + i] && !ndg[u - i + n]) { // 如果列没被用过，正反对角线都没被用过，说明符合规则
            queen[u][i] = 'Q'; // 全排列赋值
            col[i] = dg[u + i] = ndg[u - i + n] = true; // 标识被用过了
            dfs_n_queen(u + 1); // 到达下一行
            col[i] = dg[u + i] = ndg[u - i + n] = false; // 回溯清空所有的状态
            queen[u][i] = '.'; // 回溯清空第 i 列的皇后
        }
    }
};

int main() {
    cin >> n;

    // 初始化 queen 数组
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            queen[i][j] = '.';

    // dfs 条件性全排列 解决 n_queen （从第 0 行开始走）
    dfs_n_queen(0);

    return 0;
}
```

==思路三==：走到最初的起点，把每一行只能存一个皇后这个先验知识都舍弃掉，直接一个格子一个格子的去进行搜索，这样就需要每个格子进行一次判断，这样就还需要加上行判断，同时模拟好格子移动的过程（之前只需要模拟好列向右移动的过程，现在还要做好行）。

```c++
/*
    @author Karry 
    @date on 2023/8/23.
    @comment Day 23. n 皇后问题：全排列的过程中，进行条件检验（对角线判断）按照格子搜索，每一个格子往后移动
*/

#include<iostream>

using namespace std;

const int N = 20; // 因为对角线是行数的 2n - 1 倍，所以开 2 倍肯定够了
int n;
char queen[N][N]; // n rows and n cols.
int row[N], col[N], dg[N], ndg[N]; // 标识行、列、正对角线和反对角线是否被用过了

// 和基本的 dfs 如出一辙，此处 (x, y, n_q) 标识期盼的第 x 行, y 列, 皇后的数量为 n_q
void dfs_n_queen(int x, int y, int n_q) {

    if (y == n) y = 0, x++; // 列到结尾了，直接转移到行头

    if (x == n) { // 到了最后一行
        if (n_q == n) { // 并且皇后的数量为 n 了，就把皇后输出出来
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) cout << queen[i][j];
                cout << endl;
            }
            cout << endl;
        }
        return;
    }

    // 在该格子上不放皇后
    dfs_n_queen(x, y + 1, n_q);

    // 在该格子上放皇后
    if (!row[x] && !col[y] && !dg[x + y] && !ndg[x - y + n]) { // 符合规则
        queen[x][y] = 'Q'; // 全排列赋值
        row[x] = col[y] = dg[x + y] = ndg[x - y + n] = true; // 标识被用过了
        dfs_n_queen(x, y + 1, n_q + 1); // 到达下一个格子，且皇后数量 + 1
        row[x] = col[y] = dg[x + y] = ndg[x - y + n] = false; // 回溯清空所有的状态
        queen[x][y] = '.'; // 回溯清空第 i 列的皇后
    }
}


int main() {
    cin >> n;

    // 初始化 queen 数组
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            queen[i][j] = '.';

    // dfs 条件性全排列 解决 n_queen （从第 0 行开始走）
    dfs_n_queen(0, 0, 0);

    return 0;
}
```

#### [Gravity of Tree](https://www.acwing.com/problem/content/848/)

在此我们必须要捋一下。在之前的数据结构学习时，我们并没有系统地了解树、图这种二维数据结构，而是停留在用一维的数组来模拟一些诸如并查集和 Trile 树这种简单的数据结构。这是因为树的思维结构是很重要但又简单的，因为并查集和 Trile 树的思想本质就是树，而我们在理解 dfs 的时候也是从树的角度出发的，把全排列和 n-皇后的问题在逻辑上转换为树的结构。

因此，有向图的深度优先搜索其实才是最 general 的形式，其包括了普通图、树的所有形式，进而包括了能够用图和树进行模拟的数据形式。这些结构在思想上的实现是完全一致的，最核心的区别在于 coding 上如何进行深度的递进。

在这个地方我们要思考两件事情

- 如何用数组模拟树的结构
- 如何对该树进行 bfs

对于这道题而言，之所以使用 bfs ，出发点是因为这种遍历方式可以快速得到根节点所在子树的节点数，同时又能够遍历去掉所有节点的情况。

==先来看如何用数组构建图== 本质有两种方式，但实际上只用后者

- 邻接矩阵：上课所学的方式，二维数组标识点与点是否存在边的连接。但这种方式比较费空间，适合稠密的图，不适合稀疏的图，因此不常用

- 邻接表：每个顶点上都放一个单链表（有点类似于 hash 表实现的拉链法），顶点的单链表存储的是该顶点可以==直接==到达图上的哪些其他点（所谓直接是指与该顶点直接相连的点），可以充分地利用空间比较常用

  ```c++
  开一个 h[N] 存储图中所有的顶点（类似于拉链法表 hash 表中，每一个 hash 值标识一个头）
  逻辑上就有 n 个单链表：
  	- 每次插入新的连接时 (p1 to p2) 只需要找到 p1 顶点对应的单链表，然后在头部进行插入即可。
  	- 完全可以用一个单链表来实现上述功能，完全类似拉链法，模拟多个链表的思路
   
  可以看到，对于多个顶点都会同时指向另一个节点的情况比如 1 => 2; 3 => 2
  在以 h[1] 为头的链表和在以 h[3] 为头的链表都会插入一个新的点其值为 2，尽管这两个点的值都是 2，但是在链表中的 idx 是完全不同的，也就是说同一个数可能同时存在多个链表的多个节点上。尽管值相同，但逻辑位置完全不同。
  
  再次解释一下直接的含义：如果有一条边为 1 => 2 => 3，那么 2 在 h[1] 为头的链表中，3 在 h[2] 为头的链表中。直接在 h[1] 为头的链表中是无法访问到 3 的。因此这种存储方式天然就为 bfs 打下基础，而如果想要用 dfs 就必须用到嵌套：
  for(int i = h[1]; i != -1; i = ne[i]){ // 这一层循环只能访问到 1 => 2
    int p1 = e[i];
    for (int j = h[p]; j != -1; j = ne[j]){ // 这一层就可以继续往下走
      int p2 = e[j];
      for (....)
    }
  }
  从下面的 dfs 中我们就可看到对这个思路的践行
  ```
  
  代码实现如下：
  
  ```c++
  int h[N]; // 顶点（链表的头）
  int e[N], ne[N], idx; // 这三个数组的含义和单链表完全相同
  
  // 向图中插入一条 a => b 的边 十分 easy！
  void add(int a, int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
  }
  
  int main(){
    memset(h, -1, sizeof(h)); // 初始化，头节点指向 -1
  }
  ```

下面我们就要具体考虑这道题中，在对每个点进行遍历的时候，所求取的内容有哪些？

- 必须要得到以该点根节点的子树节点总数 sum，这样才能求出来去掉该点后，其父节点所在子树（这个子树一定是一个连通块），也即这个连通块的节点数 = n - sum。
- 必须要求出该节点的每一棵子树的节点总数，也即每一个子树连通块的大小 res 并且通过每一棵子树的 res 求最大值得到其子树中 res 的最大值

注意到，这个地方求子树节点总数是可以利用 bfs 搜索的，这就是核心思想所在！

```c++
/*
    @author Karry 
    @date on 2023/8/26.
    @comment Day 26. 树的重心 对 bfs 进行深入理解，研究其在树中的核心应用
    @note 理解如何用单链表存储树
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 1e5 + 10, M = N * 2;
int n; // n 个顶点
int h[N]; // 存储树的每一个顶点，顶点同时也是每个单链表的表头
bool st[N]; // 存储每一个节点的使用状态
// 注意：因为顶点输入可能重复，因此链表大小要开到顶点数量的 2 倍
int e[M], ne[M], idx; // 单链表的三件套 （尽管形式上是单链表，但是逻辑上是多个链表共用这一个区间）

int ans = N; // 题解，在这设定为一个全局变量，便于对去掉每一个节点后得到的答案进行更新

// 在图中加一条 a -> b 的边 （类似与 hash 表的思路，底层就是在单链表表头插入数）
void add_edge(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// 此处 dfs 的抓手是返回以 u 这个顶点，为根节点的子树的节点总数（子树大小），这样就可以完成连通块大小的比较
int dfs(int u) {
    // ---- step 1. 修改节点的状态 ---- //
    st[u] = true; // 顶点 u 被使用过了

    // ---- step 2. 开始找该顶点为根节点的子树的节点总数 ---- //
    int sum = 1; // sum 存储的就是以该节点为根节点的子树大小，因为有个根节点，所以初始化为 1
    int res = 0; // res 表示的是去掉该节点后连通块大小的最大值
    for (int i = h[u]; i != -1; i = ne[i]) { // 对该节点所有的子节点进行遍历
        int s_point = e[i]; // 取出子顶点的值
        if (!st[s_point]) {
            int s = dfs(s_point); // 求该以子节点为根节点的子树大小 （这个地方用到递归的思想，也是此题使用 dfs 的核心所在）
            res = max(res, s); // 更新 res 的值，取到最大子树大小
            sum += s;  // 把子树的大小加到原顶点上
            // （这个地方在初始思考的时候，总觉得是把一棵子树的每个点重复算了一下，但仔细想一想 bfs 的过程中状态会改变，不会重复的！）
        }
    }

    // ---- step 3, 求该节点父节点所在子树的大小，并完成更新 ---- //
    res = max(res, n - sum); // 至此我们既得到了去掉该节点后每一个连通块大小的最大值

    // ---- step 4. 依据这个节点的结果，对总解答进行更新 ---- //
    ans = min(ans, res);

    return sum;
}

int main() {
    cin >> n;

    // ---- step 1. 构建无向树 ---- //
    memset(h, -1, sizeof(h)); // 初始化每一个单链表的表头为 -1

    for (int i = 0; i < n - 1; i++) { // 输入 n - 1 条边
        int a, b; // a <-> b
        cin >> a >> b;
        // 在 a 和 b 之间同时加上 a -> b 的边 和 b -> a 的边
        add_edge(a, b), add_edge(b, a);
    }

    // ---- step 2. 从起点开始 dfs 找答案，是在 dfs 的过程中对答案完成的更新 ---- //
    dfs(1); // 此处起点是 1

    // ---- step 3. 输出结果 ---- //
    cout << ans << endl;

    return 0;
}
```

### 3.2 BFS - search min （一层层向下推）

bfs（宽搜）常用于搜索最短路线，==一层层地向下走==（此处层的概念是由路径的权重来表现的，一般情况下 bfs 要求权重必须是相等的），不断前进，每走到一个区域（可能有很多个点），就用队列将其存起来，然后把队列中所有的可能点进行遍历，直至不再有新的区域被开发出来，这样到任何一个点的距离到起点都是最短的。

bfs 的关键问题是：

- 如何存储现在所在的状态？（一般是采用一个队列，保证先进先出）
- 如何进行开拓领域后的状态转移，也就是说怎样在进行条件判断后完成进行转移？【一般就需要一个状态数组和距离数组】理解了队列 bfs 就理解一半了！

因此 bfs 的书写是有标准模版的

#### [Walk Maze](https://www.acwing.com/problem/content/846/)

走迷宫是 bfs 最经典的问题，从起点出发，等权重向周围搜索。核心是如何记住当前的立足点，以及如何向后继续拓展延伸，同时存储下来该点到起点的距离。

- 此处采用队列存储后续新开拓的区域，用一个数对表示坐标，存储区域所在位置，完成状态的存储。
- 往上下左右四个区域去找进行拓展，也就是状态转移（这个地方的转移条件判断也比脚简单），每次成功拓展后，将可能到达的点（对应着新状态）存储到队列中，同时将该状态下距离初始状态的距离赋值为上一个状态对初始状态的距离 + 1。
- 用一个和棋盘一样大的数组存储每一个点（每一个状态）到起点的最短距离

```c++
/*
    @author Karry 
    @date on 2023/8/24.
    @comment Day 24 BFS 算法实践 => 走迷宫 ｜ 核心在于用队列存储所有的可能点，每次都进行逐个访问，寻找最急的后续点
    @note 这一份是用数组模拟队列
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 110; // 因为迷宫的宽度最大为 100，多开 10 个是足够的
typedef pair<int, int> PLL; // 记录坐标的元素

int n, m; // 行高，列宽

// 表示迷宫的两个重要数组
int maze[N][N]; // 迷宫数组
int maze_dist[N][N]; // 表示迷宫每个点到起点的距离 (distance) 的数组

// 数组模拟的队列：队列中的元素是点，所以需要设置点坐标的队列
PLL q[N * N];
int hh, tt;

// bfs 搜索，从 [0, 0] 点开始
int bfs() {
    hh = 0, tt = 0; // 初始化队列为空
    memset(maze_dist, -1, sizeof(maze_dist)); // 初始化迷宫所有点的初始状态，刚开始所有点到起点的距离都是 -1

    // step 1. 从起点开始搜索
    q[tt++] = {0, 0}; // 起点入队列
    maze_dist[0][0] = 0; // 迷宫起点的状态更新 （初始距离设定）

    // step 2. 开始逐层搜索
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1}; // 两个一维数组组合称四个方向，0-上[-1, 0], 1-下[1, 0], 2-左[0, -1], 3-右[0, 1];
    while (hh < tt) { // 只要队列不为空，就说明新的区域中有点还没有往下走
        auto p = q[hh++]; // 把队头元素（立足点）取出来，可能转移的状态

        for (int i = 0; i < 4; i++) { // 走遍四个方向
            int x = p.first + dx[i], y = p.second + dy[i]; // 从立足点往四个方向走的坐标点 (x, y)

            // (x, y) 必须在迷宫范围内，该点还不是墙，且该点之前没有被访问过
            if (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && maze_dist[x][y] == -1) {
                maze_dist[x][y] = maze_dist[p.first][p.second] + 1; // 修改该点的状态：该点到起点的距离 = 立足点到起点的距离 + 1
                q[tt++] = {x, y}; // 该点入队尾
            }
        }
    }

    return maze_dist[n - 1][m - 1]; // 终点到起点的距离
}

int main() {
    cin >> n >> m;

    // 输入迷宫
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    // 进行 bfs 搜索
    cout << bfs() << endl;

    return 0;
}
```

#### [Eight Figure Puzzles](https://www.acwing.com/problem/content/847/)

八数码问题，其实和走迷宫异曲同工，可以把空格的走动想象成棋子的走动，但只不过最终的状态并不但要让棋子到达终点，还要把数字排列给搞对。因此可以将此问题抽象为一个有附加条件的寻找最短路径问题，既然是最短路径就可以尝试使用 bfs 进行求解。

正是因为条件更加复杂了，所以每一种情况的状态表示以及状态转移判断就变得更加复杂了

- 此处采用字符串的方式存储状态。具体地，就是将棋盘拉直变为一个字符串存储，记录下此时棋盘的具体状态。
- 将字符串转变为棋盘，然后可能有三个或两个方向的变换，完成条件判断后，就可以确定状态是否能够进行转移，把可能的新状态入队列，同时基于上一状态到起始状态的距离，计算出该状态对应的到起始状态的距离。
- 用一个哈希表存储 {字符串表示的状态：该状态到起点的距离}

```c++
/*
    @author Karry 
    @date on 2023/8/26.
    @comment Day 26. 树的重心 对 bfs 进行深入理解，研究其在树中的核心应用
    @note 理解如何用单链表存储树
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 1e5 + 10, M = N * 2;
int n; // n 个顶点
int h[N]; // 存储树的每一个顶点，顶点同时也是每个单链表的表头
bool st[N]; // 存储每一个节点的使用状态
// 注意：因为顶点输入可能重复，因此链表大小要开到顶点数量的 2 倍
int e[M], ne[M], idx; // 单链表的三件套 （尽管形式上是单链表，但是逻辑上是多个链表共用这一个区间）

int ans = N; // 题解，在这设定为一个全局变量，便于对去掉每一个节点后得到的答案进行更新

// 在图中加一条 a -> b 的边 （类似与 hash 表的思路，底层就是在单链表表头插入数）
void add_edge(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// 此处 dfs 的抓手是返回以 u 这个顶点，为根节点的子树的节点总数（子树大小），这样就可以完成连通块大小的比较
int dfs(int u) {
    // ---- step 1. 修改节点的状态 ---- //
    st[u] = true; // 顶点 u 被使用过了

    // ---- step 2. 开始找该顶点为根节点的子树的节点总数 ---- //
    int sum = 1; // sum 存储的就是以该节点为根节点的子树大小，因为有个根节点，所以初始化为 1
    int res = 0; // res 表示的是去掉该节点后连通块大小的最大值
    for (int i = h[u]; i != -1; i = ne[i]) { // 对该节点所有的子节点进行遍历
        int s_point = e[i]; // 取出子顶点的值
        if (!st[s_point]) {
            int s = dfs(s_point); // 求该以子节点为根节点的子树大小 （这个地方用到递归的思想，也是此题使用 dfs 的核心所在）
            res = max(res, s); // 更新 res 的值，取到最大子树大小
            sum += s;  // 把子树的大小加到原顶点上
            // （这个地方在初始思考的时候，总觉得是把一棵子树的每个点重复算了一下，但仔细想一想 bfs 的过程中状态会改变，不会重复的！）
        }
    }

    // ---- step 3, 求该节点父节点所在子树的大小，并完成更新 ---- //
    res = max(res, n - sum); // 至此我们既得到了去掉该节点后每一个连通块大小的最大值

    // ---- step 4. 依据这个节点的结果，对总解答进行更新 ---- //
    ans = min(ans, res);

    return sum;
}

int main() {
    cin >> n;

    // ---- step 1. 构建无向树 ---- //
    memset(h, -1, sizeof(h)); // 初始化每一个单链表的表头为 -1

    for (int i = 0; i < n - 1; i++) { // 输入 n - 1 条边
        int a, b; // a <-> b
        cin >> a >> b;
        // 在 a 和 b 之间同时加上 a -> b 的边 和 b -> a 的边
        add_edge(a, b), add_edge(b, a);
    }

    // ---- step 2. 从起点开始 dfs 找答案，是在 dfs 的过程中对答案完成的更新 ---- //
    dfs(1); // 此处起点是 1

    // ---- step 3. 输出结果 ---- //
    cout << ans << endl;

    return 0;
}
```

#### [Hierarchy of Points](https://www.acwing.com/problem/content/849/)

将 bfs 应用到图中，核心仍然是寻找最短路径。

因此在这个地方，无非是修改了一下状态存储形式和状态转移条件罢了。看到题目中提到每一个边的长度都是 1，想到可以用宽搜来进行最短路径的求解。 思路和之前完全是一样的，只不过搜索的对象变了，需要换成单链表存储图，每个节点有一个对应的状态和距离。

```c++
/*
    @author Karry 
    @date on 2023/8/27.
    @comment Day 27. 将 bfs 应用到图的搜索中
    @note bfs 是有标准模版的，无非就是遍历形式会跟随数据存储的载体而改变
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

int n, m; // 从 1 号节点到 n 号节点； 总共有 m 条边
const int N = 1e5 + 10; // 数据范围
int h[N], e[N], ne[N], idx; // 因为这个地方说明了最多有 m 条边，所以不需要开点的二倍大小
queue<int> q; // 存储等待访问的点的队列，以完成状态转移
int dist[N]; // 存储 1 号点到 i 号点的最短距离（distance），顺带着辅助进行存储状态

// 往图中添加 a -> b 这条边 （一定要熟练背住！）
void add_edge(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// 从 u 号点开始搜索
int bfs(int u) {
    // ---- step 1. 配置初始状态 ---- //
    memset(dist, -1, sizeof(dist)); // 初始化 dist 数组，表示从 u 号点到所有点的最短距离都是 -1 这也说明每个点都还没被访问过
    dist[u] = 0; // 作为搜索的起点，u 号点到 u 号点的距离为 0
    q.push(u); // u 号点入队列，作为后续状态转移的抓手

    // ---- step 2. 按照套路开始一层层向下访问 ---- //
    while (q.size()) { // 只要队列不空说明还可以继续往下拓展
        int p = q.front(); // 取出队头元素 p 号顶点
        q.pop(); // 队头元素队列

        for (int i = h[p]; i != -1; i = ne[i]) { // 访问 p 号点所能到达的所有点
            int j = e[i]; // 取出其能到达顶点的编号 j （新状态）
            if (dist[j] == -1) { // 该顶点之前从来没有到达过
                dist[j] = dist[p] + 1; // u 到 j 号点的最近距离 = u 到 p 号点的最近距离 + 1
                q.push(j); // 将 j 号顶点放入队列，方便后续状态拓展
            }
        }
    }

    // ---- step 3. 返回最终结果 ---- //
    return dist[n]; // u 号点到 n 号点的距离，如果无法到达就是初始值 -1 （从来没有更新过）
}


int main() {
    cin >> n >> m;

    // ---- step 1. 输入 n 条边 ---- //
    memset(h, -1, sizeof(h)); // 所有的单链表头设定为 -1
    while (m--) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b); // add the edge a -> b;
    }

    // ---- step 2. 从 1 号点开始搜索即可 ---- //
    cout << bfs(1) << endl;

    return 0;
}
```

#### [Toplogical Sequence](https://www.acwing.com/problem/content/850/)

寻找拓扑序列是==针对有向图的一种特殊的 bfs 应用==。

拓扑序列在理论上的含义是：节点若按照此序列进行排序，那么所有边的指向对于该节点序列而言，都是从前面的节点向后面的节点。不存在拓扑排序的理论含义就是：对于所有的节点而言，不存在一种排序使得所有边的指向都是从序列中前面的点指向后面的点。可以证明有向无环图一定有拓扑序列（可以用反证法证明），因此有向无环图也被称为拓扑图。

推导拓扑序列是有标准步骤的：

- 选出入度为 $0$ 的节点，然后把节点序号写出来，并将该节点从图中删去
- 重复上述操作，直至所有点被选出（如果同时有多个入度为 $0$ 的节点，那就可以随便选一个）
- 但凡有一次遇到图中没有入度为 $0$ 的节点的情况，就说明该有向图不存在拓扑序列

用代码写出上述步骤的关键无非也就两点

- 如何选出某一状态下，所有入度为 $0$ 的点 ？
- 节点被删去，图的结构发生改变时，怎么把这种变化反映在相关节点的入度上？

思考到这，就发现直接套用 bfs 的框架即可，每一个节点的状态 d[N] 此时变成了入度

- 构造图的时候对 d[N] 进行初始化 （每加一条边 a => b；d[b] ++ ）
- 通过对 d[N]  的判断就可以选出入度为 $0$ 的点 （刚开始循环一遍，把符合条件的点入队列）
- 每一次删去节点 i 后，枚举出所有的 i => j 的边，然后修改指向点 j 点的入度 d[j]（d[j]--）， 一旦 d[j] = 0 就让点入队列
- 如果所有点都进入过队列（因为一个点不可能重复进入队列，只需要做出 push 到队中的操作数 = 点数即可），就说明该图已经遍历完成了。

我们用 stl 队列和数组模拟队列和 分别写一下，都比较简单！

- stl 队列（需要开两处间接存储的空间）

  ```c++
  /*
      @author Karry 
      @date on 2023/8/28.
      @comment Day 28. 有向图的拓扑序列是一个重要性质，判断一个有向图是否存在拓扑序列进而就可以判断一个图中是否存在环
      @note 仍然贯穿 bfs 的思想，无非是修改了队每一个节点状态的表示方法，此处为每一个节点的入度。
            这段是直接用 stl 中的 queue 来写的 （较比数组写的话可能要麻烦些）
              - 采用一个 push_time 记录点入队列的次数，进而对是否完成遍历做判断
              - 再开一个 topo_s[] 数组保存拓扑序列
  */
  
  #include<iostream>
  #include<cstring>
  #include<queue>
  
  using namespace std;
  
  const int N = 1e5 + 10; // 数据范围
  int n, m; // n 个点； m 条边
  int h[N], e[N], ne[N], idx; // 模拟有向图的单链表
  queue<int> q; // bfs 中的队列，存储后续可能被依次访问到的点
  int push_num; // 记录总共 push 到队列的点的熟练
  int d[N]; // 记录每一个节点状态的数组，此处其含义为点的入度
  int topo_s[N], s_idx; // 最终的拓扑序列
  
  // 添加一条 a => b 的边
  void add_edge(int a, int b) {
      e[idx] = b;
      ne[idx] = h[a];
      h[a] = idx;
      idx++;
  }
  
  // 对图进行拓扑排序
  bool topo_sort() {
      // ---- step 1. 让图中所有入度为 0 的点入队列 ---- //
      for (int i = 1; i <= n; i++) { // 对 1 ～ n 号点进行遍历（因为题目要求点的编号只能是 1 ～ n）
          if (d[i] == 0) {
              q.push(i); // 如果 i 号点的入度为 0 就让他入队列
              push_num++; // push 的次数 + 1
          }
      }
  
      // ---- step 2. 对图中所有的点进行 bfs 搜索 ---- //
      while (q.size()) {
          int p = q.front(); // 取出队头元素
          topo_s[s_idx++] = p; // 取队头元素的顺序就是 topo 顺序
          q.pop();
  
          for (int i = h[p]; i != -1; i = ne[i]) { // 对 i 号点所能到达的点进行遍历
              int j = e[i]; // 取出该 i 号点指向点的号
              d[j]--; // 该点的入度 -1 （逻辑上等价于删除 i -> j 这条边）
              if (d[j] == 0) { // 如果入度为 0，就放入队列
                  q.push(j);
                  push_num++;
              }
          }
      }
  
      // ---- step 3. 对 push num 进行判断 ---- //
      return push_num == n;
  }
  
  int main() {
      cin >> n >> m;
  
      // ---- step 1. 对图进行初始化 ---- //
      memset(h, -1, sizeof(h));
      while (m--) {
          int a, b;
          cin >> a >> b;
          add_edge(a, b);
          d[b]++; // b 的入度 + 1
      }
  
      // ---- step 2. 进行拓扑排序 ---- //
      if (topo_sort())
          for (int i = 0; i < s_idx; i++)
              cout << topo_s[i] << " ";
      else cout << "-1";
  
      return 0;
  }
  ```

- 数组模拟队列（数组队列中保留着很多队列操作的历史信息，因此可以直接使用）

  ```c++
  /*
      @author Karry 
      @date on 2023/8/28.
      @comment Day 28. 使用数组模拟队列完成拓扑排序
      @note 由于数组模拟队列中的数组能够存储很多的历史信息，因此可以不需要开多余的空间对数据进行存储
  */
  
  #include<iostream>
  #include<cstring>
  
  using namespace std;
  
  const int N = 1e5 + 10;
  int n, m; // n 个点 m 条边
  int h[N], e[N], ne[N], idx; // 图
  int d[N]; // 图中每个节点的状态
  int q[N], hh, tt; // 数组模拟的队列
  
  void add_edge(int a, int b) {
      e[idx] = b;
      ne[idx] = h[a];
      h[a] = idx;
      idx++;
  }
  
  bool topo_sort() {
      hh = tt = 0; // 队列初始化
  
      for (int i = 1; i <= n; i++)
          if (d[i] == 0)
              q[tt++] = i; // 入度为 0 的点入队列
  
      while (hh < tt) { // 如果队列不为空
          int p = q[hh++]; // 将队头元素取出，同时队头元素出队列
          for (int i = h[p]; i != -1; i = ne[i]) {
              int j = e[i];
              d[j]--;
              if (d[j] == 0) q[tt++] = j; // 如果 j 号点的入度为 0，j 入队列
          }
      }
  
      return tt == n;
  }
  
  int main() {
      cin >> n >> m;
  
      memset(h, -1, sizeof(h));
      while (m--) {
          int a, b;
          cin >> a >> b;
          add_edge(a, b);
          d[b]++;
      }
  
      if (topo_sort())
          for (int i = 0; i < n; i++)
              cout << q[i] << " "; // 入队的顺序就是拓扑排序（十分巧妙！）
      else cout << "-1";
  
      return 0;
  }
  ```

### 3.3 【单源最短路 + 所有边权都是正数】DIJKSTRA

求解有向图中最短路径的算法。对于每条边等权重，也就是变长都为 1 的有向图，我们当然可以借助 bfs 进行求解（对节点进行遍历执行 [Hierarchy of Points] 中的操作，找到两两节点之间的最小距离）。但是如果给有向图中的边进行加一个正向的权重，每条边所表示的距离存在区别也就是变长不同时，就很难用 bfs 直接进行求解了，转而用 dijkstra 这个工具求解所有边都是正数的情况下的最短路径问题。

#### [Simplicial Dijkstra](https://www.acwing.com/problem/content/851/)

朴素版的 Dijkstra 算法，底层原理是贪心（每次根据状态找距离最近的点），时间复杂度是 $O(n^2)$

核心维护着点 i 到起点的==最短==距离 dist[i]，同时维护已经确定是最短距离的点集 s[n] ，思路如下：

- **<u>*Step 1.*</u>** 初始化：dist [] = 正无穷; dist[1] = 0; 
- **<u>*Step 2.*</u>** 对所有点进行遍历 （这个过程总共进行 n 次）【下面两步对全图进行不断渗透，直至全部点状态更新完成】
  - 每次都先判断点否在 s[n] 中，遍历完成找到不在 s[n] 中且 dist 最小点 t，将其放入 s 中 （每次只会放入一个点，这个点一定是最优的，可以用贪心算法进行推导）
  - 因为点 t 已经放入 s 中，所以用其帮助更新 t 点所能到达点的 dist

Dijkstra 算法面向的一般是比较稠密的图，所以采用邻接矩阵来存。此处我们还不用考虑负数边长，对于最短路径而言，1）根本不需要 care自环，不用对其进行存储；2）重边也只需要存储最短边。因此这样构建邻接矩阵就比较简单。

```c++
/*
    @author Karry 
    @date on 2023/8/29.
    @comment Day 29. 朴素的 Dijkstra 算法，时间复杂度 O(n^2)
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 510; // 数据范围，图中最多 500 个节点，开 510 简便边界处的思考
int n, m; // n 个点，m 条边
int g[N][N]; // 邻接矩阵表示图
/*
 * dijkstra 中最核心的两个数组
 * dist 表示 i 号节点到起始节点的【最短距离】
 * st 表示 i 号节点是否已经确定了到起始节点的最短路径【就位点池】
 */
int dist[N];
bool st[N];

// dijkstra 算法，求图中 r 号点（起点）到 t 号点（终点）的最短距离
int dijkstra(int r, int t) {
    // ---- step 1. 初始化起始状态 ---- //
    memset(dist, 0x3f, sizeof(dist)); // 初始化所有点到起点的【最短距离】都是无穷大
    dist[r] = 0; // 起始点到起始点的【最短距离】为 0

    // ---- step 2. 将 n 个点一个个地进行确定最短路径【放到就位点池中】 ---- //
    for (int i = 0; i < n; i++) { // i 只是计数功能，每一次都只能确定一个点，总共要确定 n 次
        // --- step 2.1 寻找此时不在 s 中且 dist 最小的节点
        int t = -1; // t 就是目标点号，初始为 -1 表示起点，以 -1 为一个起点标注
        for (int j = 1; j <= n; j++) // 对 1 ～ n 号点进行遍历寻找，遍历完成后确定一个点 t 这就是 i 循环中确定的唯一一个点，将其选入【就位点池】
            if (!st[j] && (t == -1 || dist[j] < dist[t])) // 遍历寻找的 j 号点必须还没有就位。
                /* 此处 t 的设置很精妙，必须展开说一下。这样做可以保证 t 的初始值都是第一个不在 s 中的点，这样的比较才意义
                 * 刚开始有个很天真的想法，那就是为什么不直接让 t = 1; 然后把 t == -1 这个条件直接去掉呢 ？
                 * 这样想就是忽略了前提条件，能够被比较的点一定都是不在 s 中的，如果你设置 t = 1，那么就都会进行一次和 1 号点的比较，这显然是矛盾的 */
                t = j;
        st[t] = true; // 将其选入【就位点池】

        // --- step 2.2 因为 s 发生了改变，基于新加入的点，更新 dist
        for (int j = 1; j <= n; j++) // 同样还是对 1 ～ n 号点进行遍历更新
            dist[j] = min(dist[j], dist[t] + g[t][j]); // j 号点到起点的距离至少可以有两种路 1. 直接到起点； 2. 先到 t 号点，再去起点
    }

    // ---- step 3. 将终点取出 ---- //
    if (dist[t] == 0x3f3f3f3f) return -1;
    return dist[t];
}

int main() {
    // ---- step 1. 构造图 ---- #
    memset(g, 0x3f, sizeof(g)); // 初始化邻接矩阵，让点与点之间的初始距离都是无穷大
    cin >> n >> m;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c); // 由于是求最短路问题，所以出现重边时，只用存下来最短的那条边，这个地方邻接矩阵表示的 g 和后面在 floyd 中再次使用邻接矩阵含义是并相同的，这个地方不用 care 自环问题
    }

    // ---- step 2. dijkstra 找到 n 号点到 1 号点的最短距离 ---- //
    cout << dijkstra(1, n) << endl;

    return 0;
}
```

#### [Heap Optimized  Dijkstra](https://www.acwing.com/problem/content/852/)

由上述我们可知 Dijkstra 的时间复杂度较高，因此要尽力进行优化，一种方式是采用堆优化，可以将时间复杂度降到 $O(nlog\ n)$。对算法进行优化的时候，思路一般是先写出原算法的步骤，然后思考每一步中有哪些可以进行调整减少循环次数。

基础的 Dijkstra 算法核心维护着点 i 到起点的==最短==距离 dist[i]，同时维护已经确定是最短距离的点集 s[n] ，思路如下：

- **<u>*Step 1.*</u>** 初始化：dist [] = 正无穷; dist[1] = 0; 
- **<u>*Step 2.*</u>** 对所有点进行遍历 （这个过程总共进行 n 次）
  - 每次都先判断点否在 s[n] 中，遍历完成找到不在 s[n] 中且 dist 最小点 t （采用堆进行存储最小值，这样可以减少找点的复杂度，每次直接取堆顶即可），将其放入 s 中 
  - 因为点 t 已经放入 s 中，所以用其帮助更新 t 点所能到达点的 dist 

```c++
/*
    @author Karry 
    @date on 2023/8/30.
    @comment Day 30. 用堆优化的 Dijkstra 算法，其核心点在于优化了寻找每次不在 s 中，且到起点最短距离最小的点 （堆排序算法）
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1e6 + 10; // 点的数量扩大了一个量级
typedef pair<int, int> PII;
int n, m; // n 个点 m 条边
int h[N], e[N], w[N], ne[N], idx; // 带权重的有向图，其他的都一样，新加的 w[N] 表示权重
/*
 * dijkstra 中最核心的两个数组
 * dist 表示 i 号节点到起始节点的【最短距离】
 * st 表示 i 号节点是否已经确定了到起始节点的最短路径【就位点池】
 */
int dist[N], st[N];

// 有向图中带权重的加边 【 a -> b 权重为 c 】
void add_edge(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c; // 唯一标识权重的数组
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// 从 r 号点到 t 号点的最短距离
int dijkstra(int r, int t) {
    // 内置的小顶堆排序（每次插入一个新点后都自动进行堆调整）【按照 pair 的第一个元素按照从小到大进行排序】
    // 其存储的内容是 {当前该点到起始点（r 号点）的最短距离，点的编号}
    // 按照到起点的最短距离排序，我们就能得到此时不在就位点池中到达起点最短距离最小的点
    priority_queue<PII, vector<PII>, greater<PII>> heap;

    // ---- step 1. 初始化起始状态 ---- //
    memset(dist, 0x3f, sizeof(dist)); // 初始化所有点到起点的【最短距离】都是无穷大
    dist[r] = 0; // 起始点到起始点的【最短距离】为 0
    heap.push({0, r}); // 将 {0, r} 放入堆中

    // ---- step 2. 每次都选取不在就位点池中到达起点最短距离最小的点（会遍历 n 次） ---- //
    while (heap.size()) { // heap 为空就表示 n 个点选完了
        // --- step 2.1 寻找此时不在 s 中且 dist 最小的节点
        auto t = heap.top(); // 取到此时到达起点最短距离最小的点
        heap.pop(); // 该点出队列
        int distance = t.first, p = t.second; // 拿出该点到起点的最短距离以及该点的编号
        /*
         * 这里判断一下之前是不是已经将这个点判断过了 如果是就找下一个heap最短的边
         * 为什么会有重复的点被判断呢 比如说再加入后要更新相关距离的时候 有a->x  还有 b->x 当我们将 a,b都纳入s当中之后
         * 如果a,b到x 的距离都更新成功了 也就是意味着 我们将{dis1,x},{dis2,x}都加入了heap当中  假设有dis1>dis2
         * 那么就会先取出dis2 这个时候x还没有被纳入s当中 那么我们就可以将s纳入进来
         * 等到后续 取出 dis1的时候 就会因为 这个判断 而直接忽略这个{dis1,x} 而考虑其他边
         * 但是 事实上 如果不加这个判断也是可以 (这个判断其实就像是一个剪枝 对算法的一个小优化)
         * 因为 在取出{dis2,x}之后 我们会对x的邻接结点进行更新 这个时候的更新的结果一定要比 {dis2,x}要来的小
         * 那么后续的判断{dis1,x}相当于只是做了一遍无用功  并没有改变什么
         * 作者：yxc
         * 链接：https://www.acwing.com/video/282/
         * 来源：AcWing
         * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
         */
        if (st[p]) continue; // 如果该点之前已经被取到过了就直接跳过
        st[p] = true; // 将该点选入【就位点池】

        // --- step 2.2 因为 s 发生了改变，基于新加入的点，更新 dist
        for (int i = h[p]; i != -1; i = ne[i]) { // 这个地方使用邻接表存储，就可以直接访问临边，不用遍历所有点了
            int j = e[i]; // 将 i 能到达的点的点号 j 取出来
            if (distance + w[i] < dist[j]) { // w[i] 的含义是 i -> j 的权重
                dist[j] = distance + w[i]; // 找到更短的到起点的距离，就对 dist 进行更新
                heap.push({dist[j], j}); // 该点可能是候选点，所以放入 heap 中 （push 入后就会自动排序）
            }
        }

    }

    // ---- step 3. 将终点取出 ---- //
    if (dist[t] == 0x3f3f3f3f) return -1;
    return dist[t];
}

int main() {
    // ---- step 1. 初始化有向图 ---- //
    cin >> n >> m;
    memset(h, -1, sizeof(h));
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
    }

    // ---- step 2. 返回 1 号点到 n 号点的最短距离
    cout << dijkstra(1, n) << endl;

    return 0;
}
```

### 3.4 【单源最短路 + 存在负权边】BELLMAN FORD【如果有最长边数限制只能用该算法】

贝尔曼算法，简称 BF 。此算法只需要考虑所有边，因此一般不再使用邻接矩阵或者邻接表存储图中的有向图，而是直接用结构体把所有的边都存储起来

```c++
struct Edge { 
  int a, b, w; // 边是从 a => b 边的权重是 w
} edge[N]; // 总共有 n 条边
```

算法思想也比较简单直接，时间复杂度为 $O(nm)$

```c++
for n 循环 n 次 等价于找 n 条边（这个等价必须要在下面不发生串联的前提下才成立）
  for 所有边 {a, b, w}
		dist[b] = min(dist[b], dist[a] + w);【松弛操作】
    // 注意这一步的更新必须不能发生串联！更新的时候 dist[a] 在做这次遍历时修改前的 dist[a] 而不能是修改了 dist[a] 后又用修改后的 dist[a] 去更新 dist[b]!
      
可以被证明：完成循环后 一定有 dist[b] <= dist[a] + w 【三角不等式】
```

对于一个存在负权环（边形成回路且边的总权重为负数）的图来说，可能并不存在最短路径，因为绕着这样一个总权重为负数的回路走一圈其距离会一直减小，这样 $1$ 号点到 $n$ 号点的距离就最短距离可能就是 $-\infin$ 了（之所以是可能，是因为如果这个负环出现在 $1$ 号点到 $n$ 号点的路径上，那么就会出现负无穷的情况，如果负环根本无法出现在这条路径上，那明显就不会出现负无穷了）。所以需要要判断是否存在负权环，y 总说 bf 可以辅助进行判断，但是时间复杂度比较高，<font color=red>这个地方没有听太明白</font>，因为一般不采用这种方法进行计算，所以也不需要深究。bf 算法也可以判断是否存在负权环，核心是利用抽屉原理，这一点在后续的 bf 算法中有更加深刻的说明。

#### [Edge Limitted Shortest Circuit](https://www.acwing.com/problem/content/855/)

可以看到 bf 算法较比 Dijkstra 算法而言时间复杂度而言并不算优秀。但是对于存在负边的有向图来说，要解决==最多不超过 k 条边的最短路径==这一问题，也就是说在求含负权边的图最短路径的基础上加上一个==对边数的限制条件==后，其他算法就不是那么容易求解出答案了，一般就只能采用 bf 算法进行求解。这个题目的现实意义是在约束条件下求解最优化问题（比如做坐飞机去旅游，有很多条路可以选，尽管换乘可以省钱，但是我不想换乘超过 n 次，这样就只需要考虑 n 次换乘以内的最便宜方案了）

另外，因为这个地方有了不超过 k 条边的限制，所以上面的 $-\infin$ 情况不会出现，也就不需要进行多余的的考虑了。

```c++
/*
    @author Karry 
    @date on 2023/8/31.
    @comment Day 31. 寻找有负权边的有向图中在 k 条边的限制下的最短路径问题。一般只能采用 bf 算法进行求解
    @note 坚持了 31 天，就算拔牙也是至少刷一道题。现在基本保持每天一道题目 1 个小时学习 + 反思的时间，坚持下去！
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 510;
const int M = 1e5 + 10; // 点数的限制和边数的限制
int n, m, k; // n 个点；m 条边；在 k 条边限制下的最短路径
int dist[N], backup[N]; // dist 的还是 i 号点到起点的最短距离，backup 是为了防止串联出现对 dist 数组的备份数组，保留初始状态
struct Edge {
    // 存储边的结构体，表示 a => b 这条边的权重为 w
    int a, b, w;
} edge[M]; // 共有 m 条边
int ans; // 全局变量存储答案

// bf 算法，求解从 r 号点 到 t 号点在 k 条边限制下的最短路径
bool bellman_ford(int r, int t, int k) {
    // ---- step 1. 进行状态初始化 ---- //
    memset(dist, 0x3f, sizeof(dist));
    dist[r] = 0;

    // ---- step 2. 进行 k 次循环，表示最多走 k 条边 ---- //
    for (int i = 0; i < k; i++) {
        /*
         * 为了防止【串联】更新的发生必须要把 dist 中的值存储到 backup 中
         * 什么是串联问题 ？
         * 首先我们要明确 bf 算法有效的前提是每次更新 dist[b] 时 dist[a] 应该是进行本次外层循环是的值，而不是进行内层循环更新后的值
         * 举个例子 对于图 1 => 2 (1)；2 => 3(1)；1 => 3(3)
         * 设定 dist[1] = 0 后，会首先将 dist[2] 从正无穷更新为 1 此时如果直接用 dist 进行更新的话，dist[3] 会从正无穷更新为 1 + 1 = 2 这就发生了【串联】问题
         * 正确的解决方法，是将本次外层循环的值先 copy 到 backup 中也就是说 dist[2] 在进行更新时，始终参考的都是之前未更新点的值！
         * 对于这个例子本次外循环的值为 dist[1] = 0；dist[2] = 正无穷；dist[3] = 正无穷，将其 copy 到 backup 中
         * 这样在进行循环内的更新时 dist[1] = 0; dist[2] = min{正无穷，0 + 1}; dist[3] = min{正无穷，正无穷 + 1} = 正无穷
         */
        memcpy(backup, dist, sizeof(dist));
        for (int j = 0; j < m; j++) { // 遍历 n 条边 不断进行更新
            int a = edge[j].a, b = edge[j].b, w = edge[j].w;
            dist[b] = min(dist[b], backup[a] + w);
        }
    }

    // ---- step 3. 进行结果判断 ---- //
    // 如果可能是正无穷那就说明到达不了。这个地方因为存在负权边，加以考虑数据范围，所以判断正无穷的方式是大于正无穷加负数后可能出现的下界
    if (dist[t] > 0x3f3f3f3f / 2) return false;
    else {
        ans = dist[t];
        return true;
    }
}

int main() {
    // ---- step 1. 初始化有向图 ---- //
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) { // 构建 m 条边
        int a, b, w;
        cin >> a >> b >> w;
        edge[i] = {a, b, w};
    }

    // ---- step 2. 使用 bellman ford 算法求解 1 号点到 n 号点在 k 条边限制下的最短路径 ---- //
    if (bellman_ford(1, n, k)) cout << ans;
    else cout << "impossible";

    return 0;
}
```

### 3.5 【单源最短路 + 存在负权边】SPFA 【本质是对 Bellman Ford 的优化】

#### [SPFA Shortest Circuit](https://www.acwing.com/problem/content/853/)

可以发现 bf 算法中最大的冗余点在于每次循环时，对有向图中的所有边都进行了扫描，尝试将 dist 缩小，但是明显很多时候都是无法缩小的。比如对于第一次循环，只有起始点能到达的点的 dist 才会缩小，而后面的都不会改变无穷大的现状。

因此我们就要思考一个问题：如何及时止损？明显发现如果说 dist[a] 在循环中不变的话，因为 a 到 b 的 w 不会变，所以 dist[b] 肯定不会变（没有传导机制）。因此我们就想到是不是可以存储下来那些 dist 变小的点 a，后面只针对他们进行更新？

正是基于上面的思考，我们想到可以借助 bfs 的思路将那些状态发生改变（dist 变小）的 a 存入队列。

```c++
- 每次都取出队头 t（上次循环中状态发生改变的点）
- 更新队头 t 所有可能到达的点的 dist，如果更新成功那就把被更新的入队列
	【只有起点 a 变小了，后继的 b 才有可能变小，才有可能存到队列中用以更新后续的点】
```

具体实现和 Dijkstra 经过堆优化很像，甚至可以直接拿那个模版来写！

```c++
/*
    @author Karry 
    @date on 2023/9/1.
    @comment Day 32. spfa 是对 df 的优化，核心是抓住了 bf 中有很多没有完成的更新操作，只对可能被更新的点进行存储和操作
    @not 开启新的九月
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1e5 + 10; // 点数和边数的限制
int n, m; // n 个点，m 条边
int h[N], e[N], w[N], ne[N], idx; // 邻接表表示有向图
int dist[N], st[N]; // 常规两件套，dist 表示 i 号点到起点的最短距离；st 表示 i 号点的状态
queue<int> q; // 存储待更新点的点号
int ans;

// 邻接表加带权边操作
void add_edge(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// spfa 算法从起点 r 号点到终点 t 号点的最短路径
bool spfa(int r, int t) {
    // ---- step 1. 状态初始化 ---- //
    memset(dist, 0x3f, sizeof(dist));
    dist[r] = 0;
    q.push(r);
    st[r] = true;

    // ---- step 2. 围绕队列展开更新 ---- //
    while (q.size()) {
        int t = q.front(); // 取出之前有过更新的点，出队列 + 调状态
        q.pop();
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i]; // 取出 t 所能到达的点，只有这些点的 dist 才有可能被更新
            if (dist[j] > dist[t] + w[i]) { // 如果可以被 t 更新，才进行更新
                dist[j] = dist[t] + w[i];
                if (!st[j]) { // 如果没在队列中才将其放入，否则不用 care
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    // ---- step 3. 对终点编号做出判断 ---- //
    if (dist[t] > 0x3f3f3f3f / 2) return false;
    else {
        ans = dist[t];
        return true;
    }
}

int main() {
    // ---- step 1. 初始化有向图 ---- //
    cin >> n >> m;
    memset(h, -1, sizeof(h));
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
    }

    // ---- step 2. spfa 寻找最短路径 ---- //
    if (!spfa(1, n)) cout << "impossible" << endl;
    else cout << ans << endl;

    return 0;
}
```

#### [SPFA Judge Nagetive Ring](https://www.acwing.com/problem/content/854/)

判断负环的核心是抽屉原理，回想一下，我们什么时候会更新点 a 的 dist[a] ？ 只有路径变换（到点 a 的路径变成了新的一条，在能够在到达 b 点的基础上加一条边到达 a）的时候才会更新 dist ，这个时候 dist[a] 所蕴含的边数显然增加了一条。

因此我们想到可以把与 dist[N] 相对应的边的数量存储到 cnt[N] 中，如果 cnt[N] 中对应的从起始点到某点总共需要经历的边的数量大于等于点的数量，就说明==从起点到该点之间的路径之间存在 n + 1 及以上的点，此时必定存在负环==。注意，就像我们之前所说的那样，这种方法只能判断起始点能到达的负环，因此如果我们想要检测整个图中是否存在负环，我们需要把所有点都遍历一遍，最好的方法就是把所有点都初始化到队列中。

最直观的解法

```c++
/*
    @author Karry
    @date on 2023/9/2.
    @comment Day 33. 使用 spfa 判断有向图中是否存在负环
    @note 直接暴力求解，多套一圈循环即可，十分 simple
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1e5 + 10; // 点数和边数的限制
int n, m; // n 个点，m 条边
int h[N], e[N], w[N], ne[N], idx; // 邻接表表示有向图
int dist[N], st[N]; // 常规两件套，dist 表示 i 号点到起点的最短距离；st 表示 i 号点的状态
int cnt[N]; // cnt 和 dist 一一对应，表示 i 号点到起点最短距离需要经历的路径长度
queue<int> q; // 存储待更新点的点号

// 邻接表加带权边操作
void add_edge(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// spfa 算法判断图中是否存在负环
bool spfa() {
    // 把所有可能的起点都来一次
    for (int r = 1; r <= n; r++) {
        // ---- step 1. 状态初始化 ---- //
        memset(dist, 0x3f, sizeof(dist));
        memset(cnt, 0, sizeof(cnt));
        dist[r] = 0;
        q.push(r);
        st[r] = true;

        // ---- step 2. 围绕队列展开更新 ---- //
        while (q.size()) {
            int t = q.front(); // 取出之前有过更新的点，出队列 + 调状态
            q.pop();
            st[t] = false;

            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i]; // 取出 t 所能到达的点，只有这些点的 dist 才有可能被更新
                if (dist[j] > dist[t] + w[i]) { // 如果可以被 t 更新，才进行更新
                    dist[j] = dist[t] + w[i];
                    cnt[j] = cnt[t] + 1; // 更新 cnt
                    if (cnt[j] >= n) return true;
                    if (!st[j]) { // 如果没在队列中才将其放入，否则不用 care
                        q.push(j);
                        st[j] = true;
                    }
                }
            }
        }

    }


    return false;
}

int main() {
    // ---- step 1. 初始化有向图 ---- //
    cin >> n >> m;
    memset(h, -1, sizeof(h));
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
    }

    // ---- step 2. spfa 图中是否存在负环 ---- //
    if (spfa()) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}
```

更加优雅的解法，这种解法有着更流畅的思路

```c++
/*
    @author Karry 
    @date on 2023/9/2.
    @comment Day 33. 使用 spfa 判断有向图中是否存在负环
    @note 当然，对于这个题而言，如果我们想要让所有的点都当起点，可以再在外面套一层循环，暴力解决，十分简单，但是下面这种方法更是 elegant，复杂度稍微低一点
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1e5 + 10; // 点数和边数的限制
int n, m; // n 个点，m 条边
int h[N], e[N], w[N], ne[N], idx; // 邻接表表示有向图
/*
 * spfa 判断负环三件套 这个地方 dist 的含义与之前的题目中完全不同了，这也是这道题的核心
 * dist 只是代表存在负边时的一种更新器，不再有任何距离的含义，只有遇到负边才有可能更新（因此初始化为 0 即可，没必要初始化为正无穷）
 * cnt 与 dit 一一对应，其表达的是在更新 dist 的时候走了多少条负边，如果负边的数量大于 n（所有边的数量肯定也大于 n 了）
 * st 含义不变
 */
int dist[N], cnt[N], st[N];
/*
 * 除了上面的理解方法，也可以用下面这位大佬的思路，这样 dist 的含义就是一脉相承的了 【参考该题下的第一条评论】
 * 我觉得可以这样理解：
 * 1. 构造一个虚拟节点 x，单向指向所有的节点，且到所有节点距离为0；
 * 2. 新图是否有负环等价于原始的图。
 * 3. dist数组一开始为 0，没有违背算法过程，可以理解为根据算法已经从 x 更新到了各个节点，接下来的代码就是顺理成章。
 * 所以 dist 数组从所有为0的状态开始是有对应意义的。就是先走一步。
 */
queue<int> q; // 存储待更新点的点号
int ans;

// 邻接表加带权边操作
void add_edge(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// spfa 算法判断图中是否存在负环
bool spfa() {
    // ---- step 1. 状态初始化 ---- //
    for (int i = 1; i <= n; i++) {
        q.push(i); // 把所有的点都放入队列，表示每个点都可以当起点
        st[i] = true;
        // dist[i] = xx; 完全不需要对 dist 进行任何的初始化，直接全部为 0
    }

    // ---- step 2. 围绕队列展开更新 ---- //
    while (q.size()) {
        int t = q.front(); // 取出之前有过更新的点，出队列 + 调状态
        q.pop();
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i]; // 取出 t 所能到达的点，只有这些点的 dist 才有可能被更新
            if (dist[j] > dist[t] + w[i]) { // 如果可以被 t 更新，才进行更新，注意只有 w[i] < 0 也就是负边出现的时候才有可能出现更新（变相只记录负边的数量）
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1; // 表示到达该点需要经历的负边数 = 到该点起点所需要经历的负边数 + 1
                if (cnt[j] >= n) return true;
                if (!st[j]) { // 如果没在队列中才将其放入，否则不用 care
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    return false;
}

int main() {
    // ---- step 1. 初始化有向图 ---- //
    cin >> n >> m;
    memset(h, -1, sizeof(h));
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
    }

    // ---- step 2. spfa 图中是否存在负环 ---- //
    if (spfa()) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}
```

#### [SPFA Multi-Source Shortest Circuit](https://www.acwing.com/problem/content/856/)

就像我们之前说的那样，spfa 肯定可以解决多源问题，但是时间会超时。

```c++
/*
    @author Karry 
    @date on 2023/9/3.
    @comment Day 34. spfa 解决多源最短路径问题
    @note 直接把 spfa 拿过来，但是这样搞肯定会比较慢，对于这个题目而言是会超时的
*/

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1e5 + 10; // 点数和变数的限制
int n, m, k; // n 个点，m 条边
int h[N], e[N], w[N], ne[N], idx; // 邻接表表示有向图
int dist[N], st[N]; // 常规两件套，dist 表示 i 号点到起点的最短距离；st 表示 i 号点的状态
int ans;

// 邻接表加带权边操作
void add_edge(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

// spfa 算法从起点 r 号点到终点 t 号点的最短路径
bool spfa(int r, int t) {
    // ---- step 1. 状态初始化 ---- //
    memset(dist, 0x3f, sizeof(dist));
    dist[r] = 0;

    queue<int> q; // 存储待更新点的点号
    q.push(r);
    st[r] = true;

    // ---- step 2. 围绕队列展开更新 ---- //
    while (q.size()) {
        int t = q.front(); // 取出之前有过更新的点，出队列 + 调状态
        q.pop();
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i]; // 取出 t 所能到达的点，只有这些点的 dist 才有可能被更新
            if (dist[j] > dist[t] + w[i]) { // 如果可以被 t 更新，才进行更新
                dist[j] = dist[t] + w[i];
                if (!st[j]) { // 如果没在队列中才将其放入，否则不用 care
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    // ---- step 3. 对终点编号做出判断 ---- //
    if (dist[t] > 0x3f3f3f3f / 2) return false;
    else {
        ans = dist[t];
        return true;
    }
}

int main() {
    cin >> n >> m >> k;

    // ---- step 1. 初始化有向图 ---- //
    memset(h, -1, sizeof(h));
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
    }

    // ---- step 2. spfa 寻找最短路径 k times ---- //
    while (k--) {
        memset(dist, 0, sizeof(dist)); // dist 初始化 （每次查询的时候都必须是全新状态）
        memset(st, false, sizeof(st)); // st 初始化 （每次查询的时候点都没有被用过）

        int r, t;
        cin >> r >> t; // 输入起点和终点

        if (!spfa(r, t)) cout << "impossible" << endl;
        else cout << ans << endl;
    }


    return 0;
}
```

### 3.6 【多源汇最短路】FLOYD

多源汇最短路问题要想让时间复杂度尽可能低，就需要借助 Floyd 算法（时间复杂度为 $O(n^3)$），而不是将 SPFA 算法跑 k 次（时间复杂度为 $O(n^2k)$ 一旦查询次数过多（$k$ 过大），就会超时！）

Floyd 算法思想比较简单，是基于动态规划算法写出的，具体形式如下，记住该形式即可（暂时不需要理解）

```c++
d[i][j] // 初始是一个邻接表
// 使用三重循环 【整体的复杂度就是 n^3 和询问次数没有任何关系】
for(int k = 1; k <= n; k++){
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      // 每次循环更新一次
      d[i][j] = min(d[i][j], d[i][k] + d[i][j]);
    }
  }
}
// 更新完成后 d[i][j] 存储的就是点 i 到 点 j 的最短距离
```

#### [Floyd Multi-Source Shortest Circuit](https://www.acwing.com/problem/content/856/)

按照上述的基本模块将代码写出即可，十分简单

```c++
/*
    @author Karry 
    @date on 2023/9/3.
    @comment Day 34. Floyd 求解多源汇最短路径问题
    @note 这个算法写起来比较简单，其背后的原理是动态规划哈！现在先记住，后面再推导
*/

#include<iostream>

using namespace std;

const int N = 210, INF = 0x3f3f3f3f; // 定义点的数量和正无穷
int d[N][N]; // floyd 中最重要的数组，初始化的时候表示邻接矩阵存储图，经过 floyd 算法后 d[i][j] 就变成了点 i 到点 j 的最短距离
int n, m, q; // n 个点，m 条边，q 次询问

// floyd 算法求解多源最短路问题
void floyd() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); // base dp
}

int main() {
    cin >> n >> m >> q;

    // ---- step 1. 初始化图 ---- //
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            /*
             * 这个地方之所以没像 Dijkstra 那样直接把图中所有点都初始化为正无穷，是因为 d 在变换后的含义不再是图了
             * 而是两点之间的距离，所以需要提前把对角线初始化为 0
             */
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;
        }
    }

    // ---- step 2. 构造边 ---- //
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        d[a][b] = min(d[a][b], c);
    }

    // ---- step 3. 调用 floyd ---- //
    floyd();

    // ---- step 4. 进行 1 次询问 ---- //
    while (q--) {
        int r, t; // r 号点是起始点，t 号点是终点
        cin >> r >> t;
        // 经典无穷判断
        if (d[r][t] > INF / 2) cout << "impossible" << endl;
        else cout << d[r][t] << endl;
    }

    return 0;
}
```

### 3.7 MINIMUM SPANNING TRESS

最小生成树算法，主要有两种思路一种是 Prim（拓展点集）一种是 Kruskal（拓展边集）。 对应的实际问题有在 n 个城市之间（完全图）修建起来距离最短的能够将所有点连接起来的连通公路。

#### [Prim](https://www.acwing.com/problem/content/860/)【核心是加点】

思路和 Dijkstra 如出一辙，贪心的思路，集合不断往后找到最短距离点拓展形成最后的最小生成树，基本思路如下：

```c++
// 最小生成树的核心思路是将已经就位的状态点集合 s[N] 一点点增大
dist[N] 表示点 i 到的距离到 s[N] 集合的最短距离

step 1. 初始化 
	dist[n] <= +infin
	s <= False
step 2.
	for (int i = 0; i < n; i++) // 和 Dijkstra 一样计数 n 次，每次将一个点放进来
		找到距离集合最近的点 t
		将点 t 放到集合当中 s[t] = true
		用已经找到的点 t 来更新其他点到集合的距离
```

这个思路是直观向前推导，核心点在在于：

- 如何找到距离集合最近的点？

  ```
  不在 s 中，且 dist 最小的点就是距离集合最近的点
  ```

- 如何用已经找到的点 t 来更新其他点到集合的距离？

  ```
  和 Dijkstra 一样，利用贪心的思想，dist 表示的是该点到集合最近的距离，因此只用关注 dist 即可
  ```

具体的代码实现

```c++
/*
    @author Karry 
    @date on 2023/9/4.
    @comment Day 35. 最小生成树算法 1 prim 算法，完全参考 Dijkstra
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 510; // 边数上界
const int INF = 0x3f3f3f3f; // 正无穷
int g[N][N]; // 因为边的数量 > 点数^2 所以是稠密图因此采用邻接矩阵来求解
int dist[N], s[N]; // dist 指的不再是点 i 到起点的最短距离，而是点 i 到已经就位的点的集合的最短距离; s 表示已经就位的所有点
int n, m; // 点数和边数

// prim 算最短生成树
int prim() {
    memset(dist, 0x3f, sizeof(dist)); // 初始化 dist 数组
    int res = 0; // 最小生成树中路径的长度

    for (int i = 1; i <= n; i++) { // 计数器记录 n 次
        int t = -1; // t = -1 鉴别是否为第一个点，这个思路和 Dijkstra 是完全一样的，t 始终表示的是不在 s 中的第一个点！
        for (int j = 1; j <= n; j++)  // 从 1 号点开始遍历
            if (!s[j] && (t == -1 || dist[j] < dist[t])) // 求出来当前不在 s 中且距离 s 最近的点
                t = j;

        if (i != 1 && dist[t] == INF) return INF; // 出现了中断点，证明没有最小生成树 （排除第一次，这个地方是为了排除特殊的边界情况，比如出现 a=>a -6 自环负权的情况）

        s[t] = true; // 将点 t 放入 s 中
        if (i != 1) res += dist[t]; // res 中加上路径的长度 (第一次不用加，放在这是为了排除边界情况，比如出现 a=>a -6 自环负权的情况)

        for (int j = 1; j <= n; j++) dist[j] = min(dist[j], g[t][j]); // 用新的加入的点 t 来更新 dist
    }

    return res;
}

int main() {
    cin >> n >> m;

    // ---- step 1. 初始化图 ---- //
    memset(g, 0x3f, sizeof(g));
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c); // 无向图的边的初始化，一是对称，二是是需要保留最小边
    }

    // ---- step 2. 求解最小生成树 ---- //
    int r = prim();

    // ---- step 3. 判断 ---- //
    if (r == INF) cout << "impossible";
    else cout << r;

    return 0;
}
```

#### [Kruskal](https://www.acwing.com/problem/content/861/)【核心是加边】

最为直观的最小生成树算法，直接将最短边尽可能地拿进来，算法思路如下

```c++
step 1. 
	将所有边按照权重从小到大排序（随便用一种方法）【这一步是 Kruskal 算法的瓶颈 O(mlogm)】

step 2.
	按照排好的顺序，从小到大，枚举每条边 a => b 其权重为 c
	如果对于该边对应的两个端点 a、b 而言，点 a 所在的集合与点 b 所在的集合是不连通的，就把这条边加到生成树中，作为最小生成树的一部分。如果二者已经在一个集合中了就直接跳过该边
```

第二步不太容易想清楚，怎么样控制集合，同时查询点是否在一个集合中呢？自然联想到之前在==并查集==问题中的操作，并查集的思路可以帮助我们简单实现如下内容：

```c++
a. 将两个点放在一个集合中
b. 查询量给的那是否在一个集合中
```

所以，说白了，Kruskal 就是并查集这种数据结构的一种应用

```c++
/*
    @author Karry 
    @date on 2023/9/5.
    @comment Day 36
    @note 核心是选权最小的边，组合成最小生成树；时间复杂度比较低，能够处理点数较多的稠密图
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int N = 2e5 + 10; // 边的数量上限
int p[N]; // 并查集中的 p[N] 概念，表示点 i 指向的上一个节点
int n, m; // n 个点，m 条边
int res; // 全局变量存储最小生成树的权重之和
// 这个地方用一个边的结构体来封装边；因为后续需要用到排序，所以就不能用邻接矩阵或者邻接表了
struct Edge {
    int a, b, w;

    bool operator<(Edge &E) const { // 结构体符号重载
        return w < E.w;
    }
} edges[N];

// 并查集中的找点 + 压缩概念
int find_root(int x) {
    if (p[x] != x) p[x] = find_root(p[x]);
    return p[x];
}

// kruskal 算法求解最小生成树
int kruskal() {
    // ---- step 1. 对有向图中的边的权重排序 ---- //
    sort(edges, edges + m);

    // ---- step 2. 并查集的初始化 ---- //
    for (int i = 0; i < m; i++) p[i] = i;

    // ---- step 3. 从小到大遍历所有边，进行最小生成树的构造 ---- //
    int cnt_m = 0; // 记录当前放入了多少条边 （如果全部的边都遍历完了，但是放入的边数小于 n - 1 说明存在未被连通的点）
    for (int i = 0; i < m; i++) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w; // 取出该边对应的顶点和权重
        if (find_root(a) != find_root(b)) { // 如果二者不在一个集合中
            p[find_root(a)] = find_root(b); // 归到一个集合中
            cnt_m++;
            res += w;
        }
    }

    return cnt_m;
}

int main() {
    cin >> n >> m;

    // ---- step 1. 构建初始边的集合 ---- //
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i] = {a, b, c};
    }
	
  	// ---- step 2. kruskal 求解 ---- //
    if (kruskal() < n - 1) cout << "impossible";
    else cout << res;

    return 0;
}
```

### 3.8 BIPARTITE GRAPH

二分图是指能够将点二分成两个集合，保证集合内部顶点之间不存在边，所有的边一定是跨集合连接顶点的。

#### [Coloration](https://www.acwing.com/problem/content/862/)【判断二分图】

染色法的根基是如下定理：一个图如果是二分图，当且仅当图中不存在奇数环（奇数个点连成的环）

```c++
【必要性】一个图是二分图，那么必然不存在奇数环。如果存在，起点既在 A 集合又在 B 集合，矛盾
【充分性】一个图中不含有奇数环，这个图必然是二分图。通过染色过程可以说明，只要给起点标好了号码，那么必然可以分成两类。
```

因此，就可以用染色的思路来判断一个图是否为二分图，只要一个点的颜色确定了，整个图的颜色就确定了。

```c++
/*
    @author Karry 
    @date on 2023/9/7.
    @comment Day 38. 判断二分图的经典方法 （dfs 的应用）
*/

#include<iostream>
#include<cstring>

using namespace std;

const int N = 100010, M = 200010; // 点数和边数的上限，因为是无向图所以有二倍关系

int n, m; // 点数 和 边数
int h[N], e[M], ne[M], idx; // 经典邻接表存储图
int color[N]; // 标识点是否被染色

// 邻接表存储无向图
void add_edge(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx ++ ;
}

// dfs 进行染色
bool dfs(int u, int c) {
    // ---- step 1. 对 u 号点。染上 c 颜色 ---- //
    color[u] = c;

    // ---- step 2. 访问 u 号点所能到达的所有点 ---- //
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i]; // 取出点的编号
        if (!color[j]) { // 如果该点没有被染色，那么就将其染为 3 - c
            if (!dfs(j, 3 - c)) return false;
        }
        else if (color[j] == c) return false; // 如果出现矛盾，说明不是二分图
    }

    return true;
}

int main() {
    // ---- step 1. 初始化无向图 ---- //
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m -- ) {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b), add_edge(b, a);
    }
    
    // ---- step 2. 进行染色并判断 ---- //
    bool flag = true;
    for (int i = 1; i <= n; i ++ ) {
        if (!color[i]) { // 如果该点没被染过色，就进行染色
            if (!dfs(i, 1)) { // 从 1 号颜色开始染色
                flag = false;
                break;
            }
        }
    }
    if (flag) cout << "Yes";
    else cout << "No";

    return 0;
}
```

#### [Hungarian](https://www.acwing.com/problem/content/863/)【二分图的最大匹配】

所谓匹配，是指选出具有以下性质的**<u>边</u>**，选出的任意一条边的两个端点都不可能在二分图的同一个部分中。所谓最大匹配，就是问最多可以找到多少条具有该性质的边。

y 总强大的找月老牵线类比，让我们认识到了匈牙利算法的好处，匈牙利算法的核心在于点是**<u>可以等待和变换</u>**的。从二分图的一个点集出发对点进行遍历，依次找到与其匹配的另一点集中的点：

- 如果另一个点集中的点没有被匹配到，那就完成了匹配
- 如果已经被匹配了，那也不会就此放弃，而是递归查询与该点匹配的在同一个集合的点还有没有可以变换的余地，如果可以变换，那就皆大欢喜（新的点可以匹配，老的点也可以匹配）。

==如果有一个困难摆在面前，没关系！而是坚持等待，直至终点！==

整体的代码思路也是如此：

- step 1. 遍历二分图集合 1 中的所有点（“男生”）为这些点寻找集合 2 中的匹配点（“女生”）
- step 2. 对状态进行判断
  - 如果女生没有被匹配过，那就直接匹配成功
  - 如果女生被匹配过了，那就对贵寻找匹配他的男生是否还能找到新的女生，如果能找到，那也是匹配成功。

```c++
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
```

9 月 8 日到 9 月 22 日 连续十五天没写

### 4. MATH

这一部分主要是为了讲清楚相关的数学概念。
