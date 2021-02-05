/******************************************************************************************************************************
*                                                                                                                             *
*	WRENCH - Portable |Wrench|iii Tools :)                                                                                    *
*		by Mohamad Mehdi Kharatizadeh                                                                                         *
*		m_kharatizadeh@yahoo.com                                                                                              *
*		Copyright(C) 2012, Mohamad Mehdi Kharatizadeh                                                                         *
*		                                                                                                                      *
*   This software is provided 'as-is', without any express or implied warranty.                                               *
*   In no event will the authors be held liable for any damages arising from the use of this software.                        *
*                                                                                                                             *
*   Permission is granted to anyone to use this software for any purpose,                                                     *
*   including commercial applications, and to alter it and redistribute it freely,                                            *
*   subject to the following restrictions:                                                                                    *
*                                                                                                                             *
*   1. The origin of this software must not be misrepresented;                                                                *
*      you must not claim that you wrote the original software.                                                               *
*      If you use this software in a product, an acknowledgment                                                               *
*      in the product documentation would be appreciated but is not required.                                                 *
*                                                                                                                             *
*   2. Altered source versions must be plainly marked as such,                                                                *
*      and must not be misrepresented as being the original software.                                                         *
*                                                                                                                             *
*   3. This notice may not be removed or altered from any source distribution.                                                *
*                                                                                                                             *
*******************************************************************************************************************************/

#ifndef WRENCH_PAIR_HPP
#define WRENCH_PAIR_HPP

#include <wrench/config.hpp>

#include <iostream>

#include <wrench/impl/begin_header.hpp>

namespace wrench {

	namespace impl { namespace pair {

		template <class T>
		struct param
		{
			typedef const T& type;
		};

		template <class T>
		struct param<T&>
		{
			typedef T& type;
		};

	} }

	template<class _First, class _Second> 
	struct pair {
	public:

		typedef typename ::wrench::impl::pair::param<_First>::type first_type;
		typedef typename ::wrench::impl::pair::param<_Second>::type second_type;

		first_type first;
		second_type second;

		pair(first_type first_value, second_type second_value) : first(first_value), second(second_value) { }
		pair() : first(), second() { }
	};
}

template<class _First, class _Second, class _traits> ::std::basic_ostream<char, _traits>& operator << (::std::basic_ostream<char, _traits>& _, ::wrench::pair<_First, _Second> const& value) {
	return _ << "(" << value.first << ", " << value.second << ")";
}

#if defined(UNICODE)
template<class _First, class _Second, class _traits> ::std::basic_ostream<wchar_t, _traits>& operator << (::std::basic_ostream<wchar_t, _traits>& _, ::wrench::pair<_First, _Second> const& value) {
	return _ << L"(" << value.first << L", " << value.second << L")";
}
#endif


#include <wrench/impl/end_header.hpp>

#endif

