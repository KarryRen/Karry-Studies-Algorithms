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