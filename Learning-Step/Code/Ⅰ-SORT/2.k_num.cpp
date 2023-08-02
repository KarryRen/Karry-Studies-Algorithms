/*
	Day 1
	Karry 2023.8.11 
*/
#include<iostream>

using namespace std;

const int N = 1e5 + 10;
int n, k;
int q[N];

int quick_k_num(int q[], int l, int r, int k) {
	if (l == r) return q[l]; // ���ֻ��һ�������������һ���ǵ� k С��

	int x = q[l + r >> 1];
	int i = l - 1, j = r + 1;

	while (i < j) {
		do i ++;
		while (q[i] < x);
		do j --;
		while (q[j] > x);
		if (i < j) swap(q[i], q[j]);
	}

	int sl = j - l + 1; // ������ֵĸ���
	if (k <= sl) {
		return quick_k_num(q, l, j, k); // ����� 
	} else {
		return quick_k_num(q, j + 1, r, k - sl); // ���ұ� 
	}
}

int main() {
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) scanf("%d", &q[i]);

	printf("%d", quick_k_num(q, 0, n - 1, k));
}
