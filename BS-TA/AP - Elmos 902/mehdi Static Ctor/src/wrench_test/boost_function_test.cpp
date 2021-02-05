#include <wrench/callback.hpp>
using wrench::callback;

#include <boost/move/move.hpp>
#include <boost/function.hpp>
using boost::move;
using boost::function;

#include <iostream>
#include <functional>
using namespace std;

int func_a() { return 5; }

int myplus(int a, int b) { return a + b; }

//callback<int> gen_rand() { return move( callback<int>( bind(&rand) ) ); }



int main() {

	function< int () > f(func_a);
	function< int () > g = f;

	cout << f() << endl;
	cout << g() << endl;
	
}
