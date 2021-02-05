#include <iostream>
using namespace std;

#include <wrench/fcmp.h>
using namespace wrench;

int main() {
	cout << lt(1, 5) << endl;

	double a = 1.0;
	double b = 5.0;
	double c = b + 1e-7;
	double d = b - 1e-7;

	cout << lt(a, b) << endl;
	cout << lt(c, b) << endl;
	cout << lte(c, b) << endl;
	cout << (c <= b) << endl;
}