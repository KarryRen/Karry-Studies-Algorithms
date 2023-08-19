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