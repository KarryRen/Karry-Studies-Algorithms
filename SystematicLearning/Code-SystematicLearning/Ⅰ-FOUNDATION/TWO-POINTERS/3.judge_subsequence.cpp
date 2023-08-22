/*
    @author Karry 
    @date on 2023/8/7.
    @Day 7 judge subsequence
*/

#include<iostream>

using namespace std;

const int N = 1e5 + 10;
int a[N], b[N]; // the two input array

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < m; i++) scanf("%d", &b[i]);

    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] == b[j]) i++; // i rightly move only equal
        j++; // j rightly move forever
    }

    // make the final judgement
    if (i == n) printf("Yes");
    else printf("No");

    return 0;
}
