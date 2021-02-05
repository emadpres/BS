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

#ifndef WRENCH_FCMP_H
#define WRENCH_FCMP_H

#include <wrench/config.hpp>

#include <wrench/impl/begin_header.hpp>

namespace wrench {

	namespace impl { namespace fcmp {

		template<class T> struct_ epsilon { };
		template<> struct_ epsilon<float> { static float value; };
		template<> struct_ epsilon<double> { static double value; };
	}}

#undef trivial_op_
#undef eps_
#undef cond_op_
#undef op_
#undef functor_
#undef gen_


#define trivial_op_(name, oper) template<class T> struct name { static bool op(T const& lhs, T const& rhs) { return lhs oper rhs; } };
#define eps_ (::wrench::impl::fcmp::epsilon<type>::value)
#define cond_op_(name,cond) template<> struct name <float> { typedef float type; static bool op(float lhs, float rhs) { return cond; } }; template<> struct name <double> { typedef double type; static bool op(double lhs, double rhs) { return cond; } };
#define op_(name,oper,cond) trivial_op_(name,oper); cond_op_(name,cond);
#define functor_(name) template<class T> bool name(T const& lhs, T const& rhs) { return ::wrench::impl::fcmp:: name <T>::op(lhs, rhs); }
#define gen_(name,oper,cond) namespace impl { namespace fcmp { op_(name,oper,cond); } } functor_(name);

		gen_(lt, <, (lhs + eps_) < rhs);
		gen_(lte, <=, (lhs - eps_) < rhs);
		gen_(gt, >, (rhs + eps_) < lhs);
		gen_(gte, >=, (rhs - eps_) < lhs);
		gen_(eq, ==, (lhs - eps_) < rhs && (rhs - eps_) < lhs);
		gen_(neq, !=, (lhs + eps_) < rhs || (rhs + eps_) < lhs);


#undef trivial_op_
#undef eps_
#undef epsf_
#undef cond_op_
#undef op_
#undef functor_
#undef gen_
	

}

#include <wrench/impl/end_header.hpp>

#endif
