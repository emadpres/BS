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

#ifndef WRENCH_TYPE_DESCRIPTOR_HPP
#define WRENCH_TYPE_DESCRIPTOR_HPP

#include <wrench/config.hpp>

#include <iostream>
#include <boost/type_traits/remove_all_extents.hpp>

#include <wrench/impl/begin_header.hpp>

namespace wrench {

	namespace impl { namespace type_descriptor {


#undef signature
#define signature template<class _char, class _traits> static ::std::basic_ostream<_char, _traits>& print(::std::basic_ostream<_char, _traits>& _)

		template<class T>
		struct printer {
			signature {
				return _ << typeid(T).name();
			}
		};


#undef specialize
#undef cascade

#define cascade(type) printer< type >::print(_)

#define specialize(spec) \
		struct printer< spec > { \
			signature

		template<class T>
		specialize(T&) {
			cascade(T);
			return _ << "&";
		}};

		template<class T>
		specialize(T&&) {
			cascade(T);
			return _ << "&&";
		}};

		template<class T>
		specialize(T const) {
			cascade(T);
			return _ << " const";
		}};

		template<class T>
		specialize(T*) {
			cascade(T);
			return _ << "*";
		}};

		template<class T>
		specialize(T volatile) {
			cascade(T);
			return _ << " volatile";
		}};

		template<class T>
		specialize(T const volatile) {
			cascade(T);
			return _ << " const volatile";
		}};

		template<class T>
		struct arity_printer { 
			signature { return _; }
		};
		template<class T, int N>
		struct arity_printer<T[N]> {
			signature {
				_ << "[" << N << "]";
				return arity_printer<T>::print(_);
			}
		};
		template<class T>
		struct arity_printer<T[]> {
			signature {
				_ << "[]";
				return arity_printer<T>::print(_);
			}
		};

		template<class T, int N>
		specialize(T[N]) {
			cascade( typename ::boost::remove_all_extents<T>::type );
			_ << " ";
			return arity_printer< T[N] >::print(_);
		}};

		template<class T>
		specialize(T[]) {
			cascade( typename ::boost::remove_all_extents<T>::type );
			_ << " ";
			return arity_printer< T[] >::print(_);
		}};

		template<
			class a0 = ::wrench::na,
			class a1 = ::wrench::na,
			class a2 = ::wrench::na,
			class a3 = ::wrench::na,
			class a4 = ::wrench::na,
			class a5 = ::wrench::na,
			class a6 = ::wrench::na
		>
		struct param_printer {
			signature { return _; }
		};

		template<class a0>
		struct param_printer<a0> {
			signature {
				return cascade(a0);
			}
		};

		template<class a0, class a1>
		struct param_printer<a0, a1> {
			signature {
				param_printer<a0>::print(_);
				_ << ", ";
				return cascade(a1);
			}
		};

		template<class a0, class a1, class a2>
		struct param_printer<a0, a1, a2> {
			signature {
				param_printer<a0,a1>::print(_);
				_ << ", ";
				return cascade(a2);
			}
		};

		template<class a0, class a1, class a2, class a3>
		struct param_printer<a0,a1,a2,a3> {
			signature {
				param_printer<a0,a1,a2>::print(_);
				_ << ", ";
				return cascade(a3);
			}
		};

		template<class a0, class a1, class a2, class a3, class a4>
		struct param_printer<a0,a1,a2,a3,a4> {
			signature {
				param_printer<a0,a1,a2,a3>::print(_);
				_ << ", ";
				return cascade(a4);
			}
		};

		template<class a0, class a1, class a2, class a3, class a4, class a5>
		struct param_printer<a0,a1,a2,a3,a4,a5> {
			signature {
				param_printer<a0,a1,a2,a3,a4>::print(_);
				_ << ", ";
				return cascade(a5);
			}
		};

		template<class T>
		specialize( T (void) ) {
			cascade(T);
			_ << " (";
			param_printer<>::print(_);
			return _ << ")";
		}};

		template<class T>
		specialize( T (*)(void) ) {
			cascade(T);
			_ << " (*)(";
			param_printer<>::print(_);
			return _ << ")";
		}};

		template<class C, class T>
		specialize( T (C::*)(void) ) {
			cascade(T);
			_ << " (";
			cascade(C);
			_ << "::*)(";
			param_printer<>::print(_);
			return _ << ")";
		}};

		template<class T, class a0>
		specialize( T (a0) ) {
			cascade(T);
			_ << " (";
			param_printer<a0>::print(_);
			return _ << ")";
		}};

		template<class T, class a0>
		specialize( T (*)(a0) ) {
			cascade(T);
			_ << " (*)(";
			param_printer<a0>::print(_);
			return _ << ")";
		}};

		template<class C, class T, class a0>
		specialize( T (C::*)(a0) ) {
			cascade(T);
			_ << " (";
			cascade(C);
			_ << "::*)(";
			param_printer<a0>::print(_);
			return _ << ")";
		}};

		template<class T, class a0, class a1>
		specialize( T (a0, a1) ) {
			cascade(T);
			_ << " (";
			param_printer<a0,a1>::print(_);
			return _ << ")";
		}};

		template<class T, class a0, class a1>
		specialize( T (*)(a0, a1) ) {
			cascade(T);
			_ << " (*)(";
			param_printer<a0,a1>::print(_);
			return _ << ")";
		}};

		template<class C, class T, class a0, class a1>
		specialize( T (C::*)(a0, a1) ) {
			cascade(T);
			_ << " (";
			cascade(C);
			_ << "::*)(";
			param_printer<a0,a1>::print(_);
			return _ << ")";
		}};

		template<class T, class a0, class a1, class a2>
		specialize( T(a0, a1, a2) ) {
			cascade(T);
			_ << " (";
			param_printer<a0,a1,a2>::print(_);
			return _ << ")";
		}};

		template<class T, class a0, class a1, class a2>
		specialize( T (*) (a0,a1,a2) ) {
			cascade(T);
			_ << " (*)(";
			param_printer<a0,a1,a2>::print(_);
			return _ << ")";
		}};

		template<class C, class T, class a0, class a1, class a2>
		specialize( T (C::*)(a0,a1,a2) ) {
			cascade(T);
			_ << " (";
			cascade(C);
			_ << "::*)(";
			param_printer<a0,a1,a2>::print(_);
			return _ << ")";
		}};

		template<class T, class a0, class a1, class a2, class a3>
		specialize( T (a0,a1,a2,a3) ) {
			cascade(T);
			_ << " (";
			param_printer<a0,a1,a2,a3>::print(_);
			return _ << ")";
		}};

		template<class T, class a0, class a1, class a2, class a3>
		specialize( T (*)(a0,a1,a2,a3) ) {
			cascade(T);
			_ << " (*)(";
			param_printer<a0,a1,a2,a3>::print(_);
			return _ << ")";
		}};

		template<class C, class T, class a0, class a1, class a2, class a3>
		specialize( T (C::*)(a0,a1,a2,a3) ) {
			cascade(T);
			_ << " (";
			cascade(C);
			_ << "::*)(";
			param_printer<a0,a1,a2,a3>::print(_);
			return _ << ")";
		}};

		template<class T, class a0, class a1, class a2, class a3, class a4>
		specialize( T (a0,a1,a2,a3,a4) ) {
			cascade(T);
			_ << " (";
			param_printer<a0,a1,a2,a3,a4>::print(_);
			return _ << ")";
		}};
		
		template<class T, class a0, class a1, class a2, class a3, class a4>
		specialize( T (*)(a0,a1,a2,a3,a4) ) {
			cascade(T);
			_ << " (*)(";
			param_printer<a0,a1,a2,a3,a4>::print(_);
			return _ << ")";
		}};

		template<class C, class T, class a0, class a1, class a2, class a3, class a4>
		specialize( T (C::*) (a0,a1,a2,a3,a4) ) {
			cascade(T);
			_ << " (";
			cascade(C);
			_ << "::*)(";
			param_printer<a0,a1,a2,a3,a4>::print(_);
			return _ << ")";
		}};

		template<class T, class a0, class a1, class a2, class a3, class a4, class a5>
		specialize( T (a0,a1,a2,a3,a4,a5) ) {
			cascade(T);
			_ << " (";
			param_printer<a0,a1,a2,a3,a4,a5>::print(_);
			return _ << ")";
		}};

		template<class T, class a0, class a1, class a2, class a3, class a4, class a5>
		specialize( T (*)(a0,a1,a2,a3,a4,a5) ) {
			cascade(T);
			_ << " (*)(";
			param_printer<a0,a1,a2,a3,a4,a5>::print(_);
			return _ << ")";
		}};

		template<class C, class T, class a0, class a1, class a2, class a3, class a4, class a5>
		specialize( T (C::*)(a0,a1,a2,a3,a4,a5) ) {
			cascade(T);
			_ << " (";
			cascade(C);
			_ << "::*)(";
			param_printer<a0,a1,a2,a3,a4,a5>::print(_);
			return _ << ")";
		}};

#undef specialize
#undef cascade		
#undef signature
	} }

	template<class T>
	struct type_descriptor { typedef T type; };

}

template<class _char, class _traits, class _type> ::std::basic_ostream<_char, _traits>& operator << (::std::basic_ostream<_char, _traits>& _, ::wrench::type_descriptor<_type> __) {
	return ::wrench::impl::type_descriptor::printer<_type>::print(_);
}


#include <wrench/impl/end_header.hpp>

#endif
