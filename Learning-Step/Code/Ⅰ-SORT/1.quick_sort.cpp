/*
	Day 1
	Karry 2023.8.11 
*/
#include<iostream>

using namespace std;

const int N = 1e6 + 10;
int n;
int q[N];

void quick_sort(int q[], int l, int r){
    // break situation
    if (l >= r) return;
    
    // �ֳ�������
    int x = q[l + r >> 1];
    int i = l - 1;
    int j = r + 1;
    
    while(i < j){
        do i ++; while (q[i] < x);
        do j --; while (q[j] > x);
        if(i < j) swap(q[i], q[j]);
    }
    
    // �ݹ���������
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main(){
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) scanf("%d", &q[i]);
    
    quick_sort(q, 0, n - 1);
    
    for (int i = 0; i < n; i++) printf("%d ", q[i]);
}
