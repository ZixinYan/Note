#include<iostream>
#include<Windows.h>
using namespace std;


int gcd(int a, int b) {
	int temp = 1;
	if (a < b) {
		temp = a;
		a = b;
		b = temp;
	}
	//a = abs(a);
	//b = abs(b);
	int r;
	while (a != 0 && b != 0) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

//计算a/(a,m)与1模m同余
int step1(int a, int m) {
	int x0;
	int i = 1;
	int c = gcd(a, m);
	while (((m / c)*i + 1) % (a / c) != 0) {
		i++;
	}
	x0 = ((m / c)*i + 1) / (a / c);
	return x0;
}
//计算a/(a,m)与b*x0/(a,m)模m同余
int step2(int x0,int a,int b,int m) {
	int x = 0;
	int c = gcd(a, m);
	if (((b * x0) / c) < (m / c) ) {
		x = (b * x0) / c;
	}
	else {
		x = ((b * x0) / c) % (m / c);
	}
	return x;
}
int main() {
	int a, b, m;
	cout << "Like ax = b(mod m) " << endl;
	cout << "Enter a: ";
	cin >> a;
	cout << "Enter b: ";
	cin >> b;
	cout << "Enter m: ";
	cin >> m;
	if (b % gcd(a, m) != 0) {
		cout << "No solution" << endl;
		return 0;
	}
	int result[100];
	int x1 = step2(step1(a, m), a, b, m);
	//cout << step1(a, m) << endl;
	//cout << x1 << endl;
	//cout << gcd(a, m) << endl;
	for (int i = 0; i < gcd(a, m); i++) {
		result[i] = x1 + ((m / gcd(a, m)) * i);
		cout << result[i] << "  ";
	}
}