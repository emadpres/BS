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

#include <wrench/except.hpp>

namespace wrench {

	exception::exception(const char* msg, int line, const char* file, const char* function) : ::std::runtime_error( ::wrench::exception::format(msg, line, file, function) ), _line(line), _file(file), _function(function) { }
	exception::exception(::std::string const& msg, int line, const char* file, const char* function) : ::std::runtime_error( ::wrench::exception::format(msg, line, file, function) ), _line(line), _file(file), _function(function) { }

	int exception::line() const { return _line; }
	const char* exception::file() const { return _file; }
	const char* exception::function() const { return _function; }

	runtime_error::runtime_error(const char* msg, int line, const char* file, const char* function) : ::wrench::exception(msg, line, file, function) { }
	runtime_error::runtime_error(::std::string const& msg, int line, const char* file, const char* function) : ::wrench::exception(msg, line, file, function) { }

}
