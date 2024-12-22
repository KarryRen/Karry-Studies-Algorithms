/*
 * @Time    : 2024/12/22 14:28
 * @Author  : Karry Ren
 * @Comment : Find the k bits of number n.
*/

#include<iostream>

using namespace std;

int main() {
    int n = 10;

    for (int k = 3; k >= 0; k--) cout << (n >> k & 1);

    return 0;
}
