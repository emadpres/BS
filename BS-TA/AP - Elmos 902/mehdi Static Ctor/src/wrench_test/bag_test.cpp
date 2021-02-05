#include <wrench/data/bag.hpp>
using wrench::data::bag;

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <wrench/out.hpp>
using wrench::out;

#include <boost/iterator/iterator_traits.hpp>

#include <boost/range/algorithm/copy.hpp>
using boost::copy;

#include <boost/range/adaptor/map.hpp>
using boost::adaptors::map_keys;
using boost::adaptors::map_values;

#include <boost/range/adaptor/filtered.hpp>

#include <wrench/any.hpp>
using wrench::any;

#include <wrench/pair.hpp>
using wrench::pair;

/***

            const range_detail::map_values_forwarder map_values =
                                           range_detail::map_values_forwarder();

**/

int main() {

	typedef bag::iterator iterator;

	bag d;
	d["x"] = 33.8;
	d["a"] = 54;
	d["z"] = false;
	d["kk"] = string("hereeeee !");
	
	copy(d | map_values, out<any>()); cout << endl;
}
