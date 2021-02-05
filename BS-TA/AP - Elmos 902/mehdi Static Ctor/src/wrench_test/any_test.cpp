#include <wrench/any.hpp>
using wrench::any;
using wrench::any_cast;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

int main() {

	any v = string("4.9");
	cout << v << endl;

	try {
		cout << any_cast<int>(v) << endl;
	} catch(std::exception &e) {
		cout << e.what() << endl;
	}

	cout << "----------------------" << endl;

	try {
		cout << "##################" << endl;
		cout << lexical_cast<double>(v) << endl;
		cout << lexical_cast<int>(v) << endl;
	} catch(std::exception &e) {
		cout << e.what() << endl;
	}
}
