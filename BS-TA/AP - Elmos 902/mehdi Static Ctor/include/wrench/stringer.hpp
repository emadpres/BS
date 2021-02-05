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

#ifndef WRENCH_STRINGER_HPP
#define WRENCH_STRINGER_HPP

#include <wrench/config.hpp>

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/move/move.hpp>
#include <iostream>
#include <vector>
#include <string>

#include <wrench/impl/begin_header.hpp>

namespace wrench {

	template<class _char, class _container = ::std::vector<_char> >
	class basic_stringer : public ::boost::iostreams::stream< ::boost::iostreams::back_insert_device< _container > >  {
		_container _data;

	public:

		typedef typename _container::iterator iterator;
		typedef typename _container::const_iterator const_iterator;
		typedef typename _container::reverse_iterator reverse_iterator;
		typedef typename _container::const_reverse_iterator const_reverse_iterator;
		typedef typename _container::value_type value_type;
		typedef typename _container::size_type size_type;
		typedef typename _container::reference reference;
		typedef typename _container::pointer pointer;
		typedef typename _container::const_reference const_reference;
		typedef typename _container::const_pointer const_pointer;

		basic_stringer() { 
			open( ::boost::iostreams::back_inserter(_data) ); 
			setf( flags() | ::std::ios::unitbuf );
		}
		operator ::std::basic_string<_char> () const { return ::std::basic_string<_char> (_data.begin(), _data.end()); }

		iterator begin() { return _data.begin(); }
		iterator end() { return _data.end(); }
		const_iterator begin() const { return _data.begin(); }
		const_iterator end() const { return _data.end(); }

		void clear() {
			close();
			_data = _container();
			open( ::boost::iostreams::back_inserter(_data) );
			setf( flags() | ::std::ios::unitbuf );
		}

		size_type size() const { return _data.size(); }

		_container& container() { return _data; }
		_container const& container() const { return _data; }
	};


	template<class _char, class _traits, class _container>
	::std::basic_ostream<_char, _traits>& operator << (::std::basic_ostream<_char, _traits>& _, const ::wrench::basic_stringer<_char, _container>& __) {
		typedef ::wrench::basic_stringer<_char, _container>::const_iterator iterator;
		for(iterator i=__.begin(), end=__.end(); i != end; ++i) _ << *i;
		return _;
	}

	typedef ::wrench::basic_stringer<char> stringer;

#if defined(UNICODE)
	typedef ::wrench::basic_stringer<wchar_t> wstringer;
#endif

}

namespace boost
{
    template<class C>
	struct range_mutable_iterator< ::wrench::basic_stringer<C> >
    {
        typedef typename ::wrench::basic_stringer<C>::iterator type;
    };

    template<class C>
    struct range_const_iterator< ::wrench::basic_stringer<C> >
    {
        typedef typename ::wrench::basic_stringer<C>::const_iterator type;
    };
}

#define stringify(expression)  ::boost::move( (::std::string) ( static_cast<::wrench::stringer&>( ::wrench::stringer() << expression ) ) )

#if defined(UNICODE)
#define wstringify(expression) ::boost::move( (::std::string) ( static_cast<::wrench::stringer&>( ::wrench::wstringer() << expression ) ) )
#endif

#include <wrench/impl/end_header.hpp>

#endif
