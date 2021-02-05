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

#ifndef WRENCH_STDINT_HPP
#define WRENCH_STDINT_HPP

#include <wrench/config.hpp>

#include <wrench/impl/begin_header.hpp>

#if defined(_MSC_VER) && _MSC_VER < 1600

namespace wrench {

	typedef __int8 int8_t;
	typedef unsigned __int8 uint8_t;
	typedef __int16 int16_t;
	typedef unsigned __int16 uint16_t;
	typedef __int32 int32_t;
	typedef unsigned __int32 uint32_t;
	typedef __int64 int64_t;
	typedef unsigned __int64 uint64_t;
}

#else
#	include <stdint.h>

namespace wrench {
	
	typedef ::int8_t int8_t;
	typedef ::uint8_t uint8_t;
	typedef ::int16_t int16_t;
	typedef ::uint16_t uint16_t;
	typedef ::int32_t int32_t;
	typedef ::uint32_t uint32_t;
	typedef ::int64_t int64_t;
	typedef ::uint64_t uint64_t;

}

#endif

#include <wrench/impl/end_header.hpp>

#endif