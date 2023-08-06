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