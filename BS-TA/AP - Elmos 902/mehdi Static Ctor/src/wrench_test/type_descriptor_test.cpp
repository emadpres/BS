#include <iostream>
using std::cout;
using std::wcout;
using std::endl;

#include <string>
using std::string;

#include <wrench/type_descriptor.hpp>
using wrench::type_descriptor;

#include <boost/type_traits/is_scalar.hpp>

int main() {

	wcout << type_descriptor< const int** (*)(float, int const * const&, int [1][2][3][4][5][6])  >() << endl;

}
