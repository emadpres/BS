#include <iostream>
using namespace std;

#include <wrench/static_ctor.hpp>

class A {

	STATIC_CONSTRUCTOR(A);

};

class B {

	STATIC_CONSTRUCTOR(B);

	STATIC_CONSTRUCTOR_TAG(B, test);

};

static_(A) {
	cout << "hello from A!" << endl;
}

static_(B) {
	cout << "hello from B!" << endl;
}

static_tag_(B,test) {
	cout << "another hello from B!" << endl;
}

int main() {
	
}
