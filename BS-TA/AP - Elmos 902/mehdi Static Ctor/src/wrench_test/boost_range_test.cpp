#include <iostream>
using std::cout;
using std::endl;

#include <boost/container/vector.hpp>
#include <boost/container/map.hpp>
using boost::container::vector;
using boost::container::map;

#include <boost/assign/list_of.hpp>
using boost::assign::list_of;

#include <algorithm>

#include <iterator>
using std::ostream_iterator;

int main() {

	vector<int> v = list_of(7)(3)(10)(2)(20)(11);

	std::copy(v.begin(), v.end(), ostream_iterator<int>(cout, ", "));
	cout << endl;

	std::wcout << "helloooo !" << std::endl;
}
