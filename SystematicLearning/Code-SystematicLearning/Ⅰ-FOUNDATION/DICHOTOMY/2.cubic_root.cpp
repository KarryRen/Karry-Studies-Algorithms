/*
	Day 3
	Karry
*/

#include<iostream>

using namespace std;

int main(){
	double num; // the num needed to be computed the cubic root
	cin >> num;
	
	double l = -1e5, r = 1e5; // the l and r boundary
	while(l < r - 1e-8){ // 1e-8 is from the experience
		double mid = (l + r) / 2;
		
		if(mid * mid * mid >= num) r = mid;
		else l = mid;
	}

	printf("%lf\n", l);
	
	return 0;
}
