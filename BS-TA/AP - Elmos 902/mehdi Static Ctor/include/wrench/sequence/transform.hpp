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

#ifndef WRENCH_SEQUENCE_TRANSFORM_HPP
#define WRENCH_SEQUENCE_TRANSFORM_HPP

#include <wrench/config.hpp>

#include <wrench/sequence/sequence.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/type_traits/add_rvalue_reference.hpp>
#include <boost/move/move.hpp>

#include <wrench/impl/begin_header.hpp>

namespace wrench { namespace sequence {

	namespace impl { namespace transform {

		template<class F>
		struct transform_object {
			F predicate;
			transform_object(F const& _predicate) : predicate(_predicate) { }
		};

	} }

	template<class F> ::wrench::sequence::impl::transform::transform_object<F> $transform(F const& predicate) {
		return predicate;
	}

	namespace detail { namespace transform {

		template<class ForwardRange, class F>
		struct result_type {
			typedef ::wrench::sequence::sequence< typename ::boost::add_rvalue_reference< ::boost::transformed_range<F, ::wrench::sequence::sequence<ForwardRange> const> >::type > const type;
		};

		template<class F>
		struct instruction_type {
			typedef ::wrench::sequence::impl::transform::transform_object<F> type;
		};
	} }

} }

template<class ForwardRange, class F> typename ::wrench::sequence::detail::transform::result_type<ForwardRange,F>::type operator > (::wrench::sequence::sequence<ForwardRange> const& _, ::wrench::sequence::impl::transform::transform_object<F>& instruction) {
	return _ | ::boost::adaptors::transformed( instruction.predicate );
}


#include <wrench/impl/end_header.hpp>

#endif
