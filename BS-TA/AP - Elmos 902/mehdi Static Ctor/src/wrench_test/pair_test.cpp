#include <wrench/pair.hpp>
using wrench::pair;

#include <iostream>
using std::cout;
using std::endl;

int main() {

	int a = 10;
	int b = 20;

	pair<int&, int&> p(a, b);
	p.first = 1;
	p.second = 2;

	cout << a << ", " << b << endl;
	
}
