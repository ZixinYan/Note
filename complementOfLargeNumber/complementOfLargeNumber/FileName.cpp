#include <iostream>
#include <windows.h>
using namespace std;

int main() {
	int b, n, m,nums[20];
	cout << "Please enter b: ";
	cin >> b;
	cout << "Please enter n: ";
	cin >> n;
	cout << "Please enter m: ";
	cin >> m;
	int count = 0;
	int a = 1;
	while (n / 2 != 0) {
		if (n % 2 == 1) {
			nums[count] = 1;
		}
		else {
			nums[count] = 0;
		}
		n = n / 2;
		count++;
	};
	nums[count] = 1;
	for (int i = 0;i <= count;i++) {
		n = nums[i];
		if (n == 0) {
			a = a;
			b = (b * b) % m;
			//cout << a << "  " << b << endl;
		}
		else {
			a = (a * b) % m;
			b = (b * b) % m;
			//cout << a << "  " << b << endl;
		}
	}
	cout << "Result is : " << a << endl;
	return 0;
}