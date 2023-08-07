/*
    @author Karry 
    @date on 2023/8/7.
    @comment an example for two pointers -> split
*/

#include<iostream>
#include<string.h>

using namespace std;

const int N = 1e6 + 10;

int main() {
    char str[N];

    // input the string
    gets(str);

    int n = strlen(str);

    // a template for two pointers
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && str[j] != ' ') j++;

        // do the other operations
        for (int k = i; k < j; k++) cout << str[k]; // output the word
        cout << endl;

        i = j;
    }

    return 0;
}
