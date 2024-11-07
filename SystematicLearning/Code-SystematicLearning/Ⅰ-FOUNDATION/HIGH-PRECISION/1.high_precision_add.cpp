/*
 * @Time    : 2024/10/27 15:16
 * @Author  : Karry Ren
 * @Comment : Compute the adding large number of str.
 * @LeetCode: 415
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> high_precision_add(vector<int> &A, vector<int> &B) {
    // using the '&' can reduce the time

    // define C as the result
    vector<int> C;

    int t = 0; // define the t as the temp number to store the important number (存储进位) 一定要初始化为 0
    for (int i = 0; i < A.size() || i < B.size(); i++) {
        if (i < A.size()) t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10); // 存储下来个位
        t /= 10; // 存储下来进位
    }

    if (t) C.push_back(1); // 最后一位如果还有进位, 就再多一个 1

    return C;
}

int main() {
    // define string to store the input number, so that it won't overfit
    // let a = '123456'
    // let b = '654329'
    string a, b;
    cin >> a >> b;

    // define two vectors to store the input num
    vector<int> A, B;
    // read them in a right to left way
    for (int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0'); // A = [6, 5, 4, 3, 2, 1]
    for (int i = b.size() - 1; i >= 0; i--)
        B.push_back(b[i] - '0'); // B = [9, 2, 3, 4, 5, 6]

    // do the high precision add
    vector<int> C = high_precision_add(A, B);

    // print the result (revert)
    string ans = "";
    for (int i = C.size() - 1; i >= 0; i--) {
        ans.push_back(C[i] + '0');
    }
    cout << ans;

    return 0;
}

