#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include <map>
#include <vector>
using std::map;
using std::vector;

#include <boost/assign.hpp>
using namespace boost::assign;

#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/irange.hpp>
using namespace boost::range;
using namespace boost::adaptors;

#include <boost/algorithm/string.hpp>
using boost::algorithm::to_upper_copy;

#include <boost/iterator.hpp>
using std::ostream_iterator;

#include <boost/functional.hpp>

int getsize(string x) { return x.size(); }

#include <wrench/auto.hpp>
#include <wrench/typeof.h>

int main() {

	map<string, int> m = map_list_of("john", 5)("wendy", 19)("jack", 24);
	
	auto_(x, m | map_keys | transformed( boost::ptr_fun(getsize) ));
	copy(x, ostream_iterator<int>(cout, ", ")); cout << endl;

	typedef boost::range_iterator< typeof_(x) >::type iterator_type;

	for(iterator_type i = boost::begin(x), end = boost::end(x); i != end; ++i) {
		cout << *i << endl;
		*i = 45;
	}

	//::boost::range::range_detail:

	

	//map<string, int>::

	//copy(m | map_keys, ostream_iterator<string>(cout, ", ")); cout << endl;
}
