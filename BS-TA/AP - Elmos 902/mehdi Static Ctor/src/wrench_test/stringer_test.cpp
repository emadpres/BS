#include <iostream>
using std::cout;
using std::endl;
using std::flush;

#include <wrench/stringer.hpp>
using wrench::stringer;

#include <string>
using std::string;


int main() {

	string s;

	stringer buff;
	buff << "your income is: " << 10;
	cout << buff << endl;

}
