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

#ifndef WRENCH_OUT_HPP
#define WRENCH_OUT_HPP

#include <wrench/config.hpp>

#include <iterator>
#include <iostream>

#include <wrench/impl/begin_header.hpp>

namespace wrench {

	template<class T> ::std::ostream_iterator<T> out(const char* sep = ", ") { return ::std::ostream_iterator<T>(::std::cout, sep); }

#if defined(UNICODE)
	template<class T> ::std::ostream_iterator<T, wchar_t> wout(const wchar_t* sep = L", ") { return ::std::ostream_iterator<T, wchar_t>(::std::wcout, sep); }
#endif

}

#include <wrench/impl/end_header.hpp>

#endif

