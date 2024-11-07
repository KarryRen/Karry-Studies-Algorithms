/*
 * @Time    : 2024/10/27 16:12
 * @Author  : Karry Ren
 * @Comment : Compute the cubic root of number.
 * @LeetCode: 69
*/

#include <iostream>

using namespace std;

int num = 24;

int main() {
    // set the bound
    long l = 0, r = num;

    // find the number result
    while (l < r - 1) {
        long mid = (l + r) >> 1;
        if (mid * mid >= num) {
            r = mid;
        } else {
            l = mid;
        }
    }

    // check the result
    if (r * r == num)
        cout << r;
    else
        cout << l;
    return 0;
}