#include <wrench/except.hpp>

#include <iostream>
using std::cout;
using std::endl;

void func(int arg1, int arg2) {
	throw_runtime_error_("test exception with arg1 = " << arg1 << ", and arg2 = " << arg2 << "! :P");
}

int main() {

	try {
		func(2, 6);
	} catch(::std::exception& e) {
		cout << e.what() << endl;
	}

}