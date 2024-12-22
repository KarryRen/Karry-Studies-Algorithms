/*
 * @Time    : 2024/12/22 14:29
 * @Author  : Karry Ren
 * @Comment : Find the number of one in number n.
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
