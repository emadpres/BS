#include <boost/phoenix.hpp>
#include <boost/iterator/counting_iterator.hpp>
using namespace boost::phoenix;
using namespace boost::phoenix::arg_names;
using namespace boost::phoenix::local_names;
using boost::make_counting_iterator;

#include <iostream>
#include <vector>
using namespace std;

/**

 BOOST_PHOENIX_ADAPT_CALLABLE(push_back, stl::push_back, 2)

 struct push_back
        {
            typedef void result_type;

            template <typename C, typename Arg>
            void operator()(C& c, Arg const& data) const
            {
                return c.push_back(data);
            }
        };

		as seen in the second argument !!

**/

class point {
	int _x, _y;

public:

	point(int x, int y) : _x(x), _y(y) { }

	int x() const { return _x; }
	void setX(int value) { _x = value; }

	int y() const { return _y; }
	void setY(int value) { _y = value; }

	struct get_x_ {
		template<typename Sig> struct result { };

		template<typename This, typename Arg> struct result< This(Arg) > { typedef int type; };

		int operator () (point const& _) {
			return _.x();
		}
	};

};

BOOST_PHOENIX_ADAPT_CALLABLE(point_get_x_, point::get_x_, 1);

int main() {

	//std::vector<int> v;

	//for_each( make_counting_iterator(0), make_counting_iterator(10), (
	//	push_back(ref(v), arg1)
	//	));

	//for_each(v.begin(), v.end(), cout << arg1 << val("\n"));

	std::vector<point> v;
	for_each( make_counting_iterator(0), make_counting_iterator(10),
		push_back(ref(v), construct<point>(arg1, arg1*2)) );

	for_each(v.begin(), v.end(),
		cout << point_get_x_(arg1) << val("\n"));

	return 0;

}
