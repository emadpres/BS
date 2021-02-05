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

#ifndef WRENCH_SEQUENCE_SEQUENCE_HPP
#define WRENCH_SEQUENCE_SEQUENCE_HPP

#include <wrench/config.hpp>

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_rvalue_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/irange.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/move/move.hpp>

#include <wrench/impl/begin_header.hpp>

namespace wrench { namespace sequence {

	namespace impl { namespace sequence {

		template<class T>
		struct store_type
			: ::boost::mpl::eval_if<
				::boost::is_rvalue_reference<T>,
				::boost::remove_reference<T>,
				::boost::add_reference< typename ::boost::add_const<T>::type >
			> { };

		template<class T>
		struct arg_type
			: ::boost::mpl::eval_if<
				::boost::is_rvalue_reference<T>,
				::boost::mpl::identity<T>,
				::boost::add_reference< typename ::boost::add_const<T>::type >
			> { };
	} }

	template<class ForwardRange>
		class sequence {
			
			typedef sequence<ForwardRange> self_;

		public:

			typedef typename ::wrench::sequence::impl::sequence::store_type<ForwardRange>::type range_type;
			typedef typename ::wrench::sequence::impl::sequence::arg_type<ForwardRange>::type argument_type;

			typedef typename ::boost::range_iterator< typename ::boost::add_const< typename ::boost::remove_reference<ForwardRange>::type >::type >::type iterator;
			typedef iterator const_iterator;
			typedef typename ::boost::iterator_value<const_iterator>::type value_type;
			typedef typename ::boost::iterator_pointer<const_iterator>::type pointer;
			typedef pointer const_pointer;
			typedef typename ::boost::iterator_reference<const_iterator>::type reference;
			typedef reference const_reference;
			typedef typename ::boost::iterator_difference<const_iterator>::type difference_type;

		private:

			range_type _range;

		public:

			sequence() : _range() { }
			sequence(argument_type range) : _range(range) { 
			}

			const_iterator begin() const { return ::boost::begin(_range); }
			const_iterator end() const { return ::boost::end(_range); }
		};

	template<class ForwardRange>
	const ::wrench::sequence::sequence<ForwardRange> $(ForwardRange const& range) {
		return ::wrench::sequence::sequence<ForwardRange>(range);
	}

	template<class ForwardRange>
	const ::wrench::sequence::sequence< BOOST_RV_REF(ForwardRange) > $(BOOST_RV_REF(ForwardRange) range) {
		return ::wrench::sequence::sequence< BOOST_RV_REF(ForwardRange) >(range);
	}

	template<class Integer>
	const ::wrench::sequence::sequence< BOOST_RV_REF( ::boost::iterator_range< ::boost::range_detail::integer_iterator<Integer> > ) > $(Integer from, Integer to) {
		return ::boost::move( ::boost::iterator_range< ::boost::range_detail::integer_iterator<Integer> >(from, to) );
	}

	template<class Integer, class StepSize>
	const ::wrench::sequence::sequence< BOOST_RV_REF( ::boost::strided_integer_range<Integer> ) >
	$(Integer first, Integer last, StepSize step_size) {
		return ::boost::move( ::boost::irange(first, last, step_size) );
	}

} }


namespace boost
{
    template<class ForwardRange>
    struct range_mutable_iterator< ::wrench::sequence::sequence<ForwardRange> >
    {
        typedef typename ::wrench::sequence::sequence<ForwardRange>::iterator type;
    };

    template<class ForwardRange>
    struct range_const_iterator< ::wrench::sequence::sequence<ForwardRange> >
    {
        typedef typename ::wrench::sequence::sequence<ForwardRange>::const_iterator type;
    };
}

#include <wrench/impl/end_header.hpp>

#endif
