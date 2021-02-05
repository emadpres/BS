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

#ifndef WRENCH_SEQUENCE_SORT_HPP
#define WRENCH_SEQUENCE_SORT_HPP

#include <wrench/config.hpp>

#include <wrench/sequence/sequence.hpp>
#include <wrench/sequence/copy.hpp>
#include <boost/container/vector.hpp>
#include <boost/move/move.hpp>
#include <boost/iterator.hpp>
#include <boost/range/algorithm/sort.hpp>

#include <wrench/impl/begin_header.hpp>

namespace wrench { namespace sequence {

	namespace impl { namespace sort {

		template<class Predicate>
		struct sort_object_predicate {

			Predicate predicate;
			sort_object_predicate(Predicate const& _predicate) : predicate(_predicate) { }

		};

		struct sort_object { };

	} }

	template<class Predicate> ::wrench::sequence::impl::sort::sort_object_predicate<Predicate> $sort(Predicate const& out) {
		return out;
	}

	::wrench::sequence::impl::sort::sort_object $sort() { 
		return ::wrench::sequence::impl::sort::sort_object();
	}

} }


template<class ForwardRange, class Predicate> ::wrench::sequence::sequence< BOOST_RV_REF(::boost::container::vector< typename ::wrench::sequence::sequence<ForwardRange>::value_type >) > const operator > (::wrench::sequence::sequence<ForwardRange> const& _, ::wrench::sequence::impl::sort::sort_object_predicate<Predicate>& instruction) {
	::boost::container::vector< typename ::wrench::sequence::sequence<ForwardRange>::value_type > temp;
	_ > ::wrench::sequence::$copy( ::std::back_inserter(temp) );
	::boost::sort( temp , instruction.predicate );
	return ::boost::move( temp );
}

template<class ForwardRange> ::wrench::sequence::sequence< BOOST_RV_REF(::boost::container::vector< typename ::wrench::sequence::sequence<ForwardRange>::value_type >) > const operator > (::wrench::sequence::sequence<ForwardRange> const& _, ::wrench::sequence::impl::sort::sort_object& instruction) {
	::boost::container::vector< typename ::wrench::sequence::sequence<ForwardRange>::value_type > temp;
	_ > ::wrench::sequence::$copy( ::std::back_inserter(temp) );
	::boost::sort( temp );
	return ::boost::move( temp );
}

#include <wrench/impl/end_header.hpp>

#endif

