/*
 * @Time    : 2024/12/22 15:02
 * @Author  : Karry Ren
 * @Comment : The interval consolidation.
 * @LeetCode: 56
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

