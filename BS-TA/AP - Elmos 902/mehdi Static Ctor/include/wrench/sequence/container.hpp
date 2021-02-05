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

#ifndef WRENCH_SEQUENCE_CONTAINER_HPP
#define WRENCH_SEQUENCE_CONTAINER_HPP

#include <wrench/config.hpp>

#include <boost/move/move.hpp>
#include <boost/iterator.hpp>
#include <wrench/sequence/copy.hpp>

#include <wrench/impl/begin_header.hpp>

namespace wrench { namespace sequence {

	namespace impl { namespace container {

		template<class _container>
		struct container_object {

		};

	} }

	template<class _container> ::wrench::sequence::impl::container::container_object<_container> $container() {
		return ::wrench::sequence::impl::container::container_object<_container>();
	}

} }

template<class ForwardRange, class _container> _container operator > (::wrench::sequence::sequence<ForwardRange> const& _, ::wrench::sequence::impl::container::container_object<_container>& instruction) {
	_container ret;
	_ > ::wrench::sequence::$copy( ::std::back_inserter(ret) );
	return ::boost::move(ret);
}

#include <wrench/impl/end_header.hpp>

#endif
