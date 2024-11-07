/*
 * @Time    : 2024/11/07 15:56
 * @Author  : Karry Ren
 * @Comment : Compute the index of number from a sortable array.
 * @LeetCode: 704
*/

#include <iostream>
#include <vector>

using namespace std;

// define the nums
vector<int> nums = {-1, 0, 3, 5, 9, 12};
int target = 9;


int main() {
    // get the length
    int length = nums.size();

    // DICHOTOMY finding
    int l = 0, r = length - 1; // the boundary

    // - find the index
    while (l < r) {
        // -- step 1. set mid
        int mid = l + r >> 1;
        // -- step 2. check and adjust the l and r
        if (nums[mid] >= target)
            r = mid;
        else
            l = mid + 1;
    }

    // - judge the answer
    if (nums[l] != target) {
        printf("-1\n");
    } else {
        printf("%d ", l);
    }

    return 0;
}