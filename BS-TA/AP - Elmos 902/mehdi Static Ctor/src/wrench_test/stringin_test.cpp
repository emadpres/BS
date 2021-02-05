#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
using boost::iostreams::array_source;
using boost::iostreams::stream;

#include <iostream>
using std::istream_iterator;

#include <wrench/out.hpp>
using wrench::out;

#include <wrench/sout.hpp>
using wrench::sout;

#include <boost/range/istream_range.hpp>
using boost::range::istream_range;

#include <boost/range/algorithm/copy.hpp>
using boost::copy;

#include <wrench/stringin.hpp>
using wrench::stringin;

#include <wrench/stringer.hpp>
using wrench::stringer;

#include <boost/assign/list_of.hpp>
using boost::assign::list_of;

#include <vector>
using std::vector;

int main() {

	string source = "1 2 3 4 5";
	stringin s = source;

	copy( istream_range<int>(s) , out<int>() );

}
