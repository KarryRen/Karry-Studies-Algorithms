/*
    @author Karry 
    @date on 2023/8/8.
    @comment Day 8 the k bit of n
             just an equation => n >> k & 1
             we can also use this to transfer a number to bits
*/

#include<iostream>

using namespace std;

int main() {
    int n = 10;

    for (int k = 3; k >= 0; k--) cout << (n >> k & 1);

    return 0;
}
