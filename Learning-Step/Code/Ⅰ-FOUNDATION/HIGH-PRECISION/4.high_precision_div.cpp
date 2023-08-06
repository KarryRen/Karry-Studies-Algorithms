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

    // now the length of C is equal to A, so there has a situation '003', which is not good enough
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
