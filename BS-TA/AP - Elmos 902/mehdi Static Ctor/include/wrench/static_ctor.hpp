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

#ifndef WRENCH_STATIC_CTOR_HPP
#define WRENCH_STATIC_CTOR_HPP

#include <wrench/config.hpp>

#include <wrench/impl/begin_header.hpp>

namespace wrench { namespace impl {
	struct __static_ctor_object { };
} }

#define STATIC_CONSTRUCTOR(classname) \
	public: \
		classname(::wrench::impl::__static_ctor_object*); \
	private:

#define STATIC_CONSTRUCTOR_TAG(classname,tag) \
	public: struct __wrench_static_ctor_object_##tag##__ { }; \
		classname(__wrench_static_ctor_object_##tag##__*); \
	private: 

#define static_(classname) namespace wrench { namespace impl { classname __##classname##__static_ctor((::wrench::impl::__static_ctor_object*)0L); } } classname::classname(::wrench::impl::__static_ctor_object*)
#define static_tag_(classname,tag) namespace wrench { namespace impl { classname __##classname##__static_ctor__with_tag_##tag##__ ((classname::__wrench_static_ctor_object_##tag##__*)0L); } } classname::classname(classname::__wrench_static_ctor_object_##tag##__*)

#define $declare_static_constructor(classname) STATIC_CONSTRUCTOR(classname)
#define $define_static_constructor(classname) static_(classname)
#define $delcare_static_constructor_tag(classname,tag) STATIC_CONSTRUCTOR_TAG(classname,tag)
#define $define_static_constructor_tag(classname,tag) static_tag_(classname,tag)

#include <wrench/impl/end_header.hpp>

#endif

