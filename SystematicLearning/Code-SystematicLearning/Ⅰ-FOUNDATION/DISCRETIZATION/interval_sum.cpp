/*
 * @Time    : 2024/12/22 15:02
 * @Author  : Karry Ren
 * @Comment : The sum of interval.
 * @LeetCode: None
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
        // same as top 或许你会有疑问，为什么还需要对 query 中的数字进行保留呢，其实很简单，
        // 因为后续还需要对这些下标进行操作，所以必须也把它们离散化了
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



