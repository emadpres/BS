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

#ifndef WRENCH_SEQUENCE_COPY_HPP
#define WRENCH_SEQUENCE_COPY_HPP

#include <wrench/config.hpp>

#include <wrench/sequence/sequence.hpp>
#include <boost/range/algorithm/copy.hpp>

#include <wrench/impl/begin_header.hpp>

namespace wrench { namespace sequence {
	
	namespace impl { namespace copy {

		template<class OutIterator>
		struct copy_object {

			OutIterator& _out;
			copy_object(OutIterator& out) : _out(out) { }

		};

	} }

	template<class OutIterator> ::wrench::sequence::impl::copy::copy_object<OutIterator> $copy(OutIterator& out) {
		return out;
	}

} }

template<class ForwardRange, class OutIterator> ::wrench::sequence::sequence<ForwardRange> const& operator > (::wrench::sequence::sequence<ForwardRange> const& _, ::wrench::sequence::impl::copy::copy_object<OutIterator>& instruction) {
	::boost::copy(_, instruction._out);
	return _;
}

#include <wrench/impl/end_header.hpp>

#endif
