#include <wrench/interface.hpp>
using wrench::$interface;

#include <iostream>
using std::cout;
using std::endl;

#include <boost/uuid/uuid_io.hpp>

class FirstClass : public $interface {

	$declare_interface(FirstClass);

};

class SecondClass : public FirstClass {

	$declare_interface(SecondClass);

};

$define_interface(FirstClass, "{6A6DEA37-F75A-41F7-8D53-0378B7E5FC0B}")  {
	cout << "an object of FirstClass created..." << endl;
}

$define_interface(SecondClass, "{0F8BD9C7-5BE8-461E-A341-5C71E223220D}") {
	cout << "an object of SecondClass created..." << endl;
}

int main() {

	$interface* x = $class.create< FirstClass >();
	cout << "uuid of x is " << x->uuid() << endl;
	cout << "type of x is " << x->type().name() << endl;
	$interface* y = $class.create< SecondClass >();
	cout << "uuid of y is " << y->uuid() << endl;
	cout << "type of y is " << y->type().name() << endl;
	delete x;
	delete y;
}
