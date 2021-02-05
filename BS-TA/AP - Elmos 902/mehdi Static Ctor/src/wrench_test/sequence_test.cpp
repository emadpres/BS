#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <string>
using std::string;

#include <boost/assign.hpp>
using namespace boost::assign;

#include <boost/iterator.hpp>
using std::ostream_iterator;
using std::back_inserter;
using std::inserter;

#include <boost/functional.hpp>
using boost::ptr_fun;

#include <functional>
#include <boost/bind.hpp>

#include <wrench/foreach.h>
#include <wrench/auto.hpp>
#include <wrench/typeof.h>

#include <wrench/out.hpp>
using wrench::out;

#include <boost/range/algorithm/copy.hpp>
using boost::copy;

#include <boost/range/algorithm/sort.hpp>
using boost::sort;

#include <wrench/type_descriptor.hpp>
using wrench::type_descriptor;

#include <boost/function.hpp>
using boost::function;

#include <boost/range/adaptor/map.hpp>
using boost::adaptors::map_keys;

#include <wrench/sequence/sequence.hpp>
#include <wrench/sequence/container.hpp>
#include <wrench/sequence/copy.hpp>
#include <wrench/sequence/each.hpp>
#include <wrench/sequence/sort.hpp>
#include <wrench/sequence/filter.hpp>
#include <wrench/sequence/transform.hpp>
#include <wrench/sequence/map.hpp>
using namespace wrench::sequence;

#include <set>
using std::set;

void print(int v) { cout << v << ", "; }
void prints(string v) { cout << v << ", "; }
void println() { cout << "\n"; }

bool pred(int x, int y) { return y < x; }
bool is_even(int x) { return x % 2 == 0; }

int main() {

	map<int, int> m = map_list_of(1,10)(2,20)(3,30)(4,40)(5,50);

	
	
	$(m) > $map_keys() > $copy( out<int>() );
}

