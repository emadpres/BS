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

#ifndef WRENCH_EXCEPT_HPP
#define WRENCH_EXCEPT_HPP

#include <wrench/config.hpp>

#include <stdexcept>
#include <string>
#include <iostream>
#include <wrench/stringer.hpp>

#include <wrench/impl/begin_header.hpp>

namespace wrench {

	class exception : public ::std::runtime_error {

		int _line;
		const char* _file;
		const char* _function;

		template<class T> static ::std::string format(T message, int line, const char* file, const char* function) {
			return stringify( "exception @" << function << " in file \"" << file << "\" at line " << line << ":" << ::std::endl << "\t" << message );
		}

	public:

		exception(const char* msg, int line = -1, const char* file = "", const char* function = "");
		exception(::std::string const& msg, int line = -1, const char* file = "", const char* function = "");

		int line() const;
		const char* file() const;
		const char* function() const;
	};

	class runtime_error : public ::wrench::exception {

	public:

		runtime_error(const char* msg, int line, const char* file, const char* function);
		runtime_error(::std::string const& msg, int line, const char* file, const char* function);

	};

}

#define throw_(exception_type, expression) throw exception_type ( stringify(expression) , __LINE__, __FILE__, __FUNCTION__)
#define throw_runtime_error_(expression) throw_(::wrench::runtime_error, expression)

#define $throw(exception_type, expression) throw_(exception_type, expression)
#define $throw_runtime_error(expression) throw_runtime_error_(expression)

#include <wrench/impl/end_header.hpp>

#endif
