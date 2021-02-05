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

#ifndef WRENCH_DATA_BAG_HPP
#define WRENCH_DATA_BAG_HPP

#include <wrench/config.hpp>

#include <boost/container/vector.hpp>
#include <boost/container/map.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/const_iterator.hpp>
#include <wrench/stddef.hpp>
#include <wrench/any.hpp>
#include <wrench/pair.hpp>
#include <string>
#include <assert.h>

#include <wrench/impl/begin_header.hpp>

namespace wrench { namespace data {

	class bag {

		::boost::container::vector< ::wrench::any > _vals;
		::boost::container::map< ::std::string, int > _m;
		::boost::container::vector<bool> _isrem;
		::boost::container::vector< ::std::string > _k;

		class Iterator 
			: public ::boost::iterator_facade< 
				::wrench::data::bag::Iterator,
				::wrench::pair< ::std::string const&, ::wrench::any& > ,
				::boost::forward_traversal_tag> {

				::wrench::data::bag* _bag;
				::wrench::size_t _index;

				friend class ::boost::iterator_core_access;

				bool null() const {
					return _bag == NULL || _index < 0 || _index >= _bag->_vals.size();
				}

				void increment() {
					assert( !null() );
					++ _index;
					while( _index < _bag->_isrem.size() && _bag->_isrem[_index] ) ++ _index;
				}

				bool equal(Iterator const& other) const {
					return (null() && other.null()) || ( _bag == other._bag && _index == other._index );
				}

				::wrench::pair< ::std::string const&, ::wrench::any& > dereference() const { 
					assert( !null() );
					return ::wrench::pair< ::std::string const&, ::wrench::any& >( _bag->_k.at(_index), _bag->_vals.at(_index) );
				}

		public:

				Iterator() : _bag(NULL) , _index(-1) { }
				Iterator(::wrench::data::bag* object, ::wrench::size_t index) : _bag(object) , _index(index) { }
		};

		class ReverseIterator
			: public ::boost::iterator_facade< 
				::wrench::data::bag::ReverseIterator,
				::wrench::pair< ::std::string const&, ::wrench::any& > ,
				::boost::forward_traversal_tag> {

				::wrench::data::bag* _bag;
				::wrench::size_t _index;

				friend class ::boost::iterator_core_access;

				bool null() const {
					return _bag == NULL || _index < 0 || _index >= _bag->_vals.size();
				}

				void increment() {
					assert( !null() );
					-- _index;
					while( _index >= 0 && _bag->_isrem[_index] ) -- _index;
				}

				bool equal(ReverseIterator const& other) const {
					return (null() && other.null()) || ( _bag == other._bag && _index == other._index );
				}

				::wrench::pair< ::std::string const&, ::wrench::any& > dereference() const { 
					assert( !null() );
					return ::wrench::pair< ::std::string const&, ::wrench::any& >( _bag->_k.at(_index), _bag->_vals.at(_index) );
				}

		public:

				ReverseIterator() : _bag(NULL) , _index(-1) { }
				ReverseIterator(::wrench::data::bag* object, ::wrench::size_t index) : _bag(object) , _index(index) { }
		};

		class ConstIterator 
			: public ::boost::iterator_facade< 
				::wrench::data::bag::ConstIterator,
				::wrench::pair< ::std::string const&, ::wrench::any const& > ,
				::boost::forward_traversal_tag> {

				::wrench::data::bag const* _bag;
				::wrench::size_t _index;

				friend class ::boost::iterator_core_access;

				bool null() const {
					return _bag == NULL || _index < 0 || _index >= _bag->_vals.size();
				}

				void increment() {
					assert( !null() );
					++ _index;
					while( _index < _bag->_isrem.size() && _bag->_isrem[_index] ) ++ _index;
				}

				bool equal(ConstIterator const& other) const {
					return (null() && other.null()) || ( _bag == other._bag && _index == other._index );
				}

				::wrench::pair< ::std::string const&, ::wrench::any const& > dereference() const { 
					assert( !null() );
					return ::wrench::pair< ::std::string const&, ::wrench::any const& >( _bag->_k.at(_index), _bag->_vals.at(_index) );
				}

		public:

				ConstIterator() : _bag(NULL) , _index(-1) { }
				ConstIterator(::wrench::data::bag const* object, ::wrench::size_t index) : _bag(object) , _index(index) { }
		};

		class ConstReverseIterator 
			: public ::boost::iterator_facade< 
				::wrench::data::bag::ConstReverseIterator,
				::wrench::pair< ::std::string const&, ::wrench::any const& > ,
				::boost::forward_traversal_tag> {

				::wrench::data::bag const* _bag;
				::wrench::size_t _index;

				friend class ::boost::iterator_core_access;

				bool null() const {
					return _bag == NULL || _index < 0 || _index >= _bag->_vals.size();
				}

				void increment() {
					assert( !null() );
					-- _index;
					while( _index < _bag->_isrem.size() && _bag->_isrem[_index] ) -- _index;
				}

				bool equal(ConstReverseIterator const& other) const {
					return (null() && other.null()) || ( _bag == other._bag && _index == other._index );
				}

				::wrench::pair< ::std::string const&, ::wrench::any const& > dereference() const { 
					assert( !null() );
					return ::wrench::pair< ::std::string const&, ::wrench::any const& >( _bag->_k.at(_index), _bag->_vals.at(_index) );
				}

		public:

				ConstReverseIterator() : _bag(NULL) , _index(-1) { }
				ConstReverseIterator(::wrench::data::bag const* object, ::wrench::size_t index) : _bag(object) , _index(index) { }
		};

	public:

		typedef Iterator iterator;
		typedef ConstIterator const_iterator;
		typedef ReverseIterator reverse_iterator;
		typedef ConstReverseIterator const_reverse_iterator;

		::wrench::any& at(::std::string const& key);
		::wrench::any const& at(::std::string const& key) const;

		::wrench::any& operator [] (std::string const& key);
		::wrench::any const& operator [] (::std::string const& key) const;

		bool removeKey(::std::string const& key);
		bool hasKey(::std::string const& key) const;
		::wrench::size_t size() const { return _m.size(); }
		void clear();
	
		iterator begin() { return iterator(this, 0); }
		iterator end() { return iterator(this, -1); }

		const_iterator begin() const { return const_iterator(this, 0); }
		const_iterator end() const { return const_iterator(this, -1); }

		reverse_iterator rbegin() { return reverse_iterator(this, _vals.size()-1); }
		reverse_iterator rend() { return reverse_iterator(this, -1); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(this, _vals.size()-1); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this, -1); }
	};

} }

namespace boost
{
	template<>
    struct range_mutable_iterator< ::wrench::data::bag >
    {
        typedef ::wrench::data::bag::iterator type;
    };

	template<>
    struct range_const_iterator< ::wrench::data::bag >
    {
        typedef ::wrench::data::bag::const_iterator type;
    };
}


#include <wrench/impl/end_header.hpp>

#endif
