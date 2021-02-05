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

#ifndef WRENCH_STRINGIN_HPP
#define WRENCH_STRINGIN_HPP

#include <wrench/config.hpp>

#include <wrench/stddef.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <string>
#include <iostream>

#include <wrench/impl/begin_header.hpp>

namespace wrench {

	template<class _char>
	class basic_stringin : public ::boost::iostreams::stream< ::boost::iostreams::basic_array_source<_char> > {

	public:
		basic_stringin(_char const* begin, _char const* end)  {
			open(begin, end);
			setf( flags() | ::std::ios::unitbuf );
		}
		basic_stringin(_char const* begin, ::wrench::size_t length)  { 
			open(begin, length);
			setf( flags() | ::std::ios::unitbuf );
		}
		template<int N> basic_stringin(_char (&arr)[N]) {
			open(arr);
			setf( flags() | ::std::ios::unitbuf );
		}
		basic_stringin(::std::basic_string<_char> const& str) { 
			open( str.c_str(), str.size() );
			setf( flags() | ::std::ios::unitbuf );
		}

	};

	typedef basic_stringin<char> stringin;

#if defined(UNICODE)
	typedef basic_stringin<wchar_t> wstringin;
#endif

}

#include <wrench/impl/end_header.hpp>

#endif
