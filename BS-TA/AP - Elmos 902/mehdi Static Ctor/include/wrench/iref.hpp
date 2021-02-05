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

#ifndef WRENCH_IREF_HPP
#define WRENCH_IREF_HPP

#include <wrench/config.hpp>

#include <wrench/stddef.hpp>
#include <boost/move/move.hpp>

#include <wrench/impl/begin_header.hpp>

namespace wrench {

	template<class T>
	class iref {

		BOOST_COPYABLE_AND_MOVABLE(iref);

		T* _p;

	public:

		iref() : _p(NULL) { }
		iref(T* ptr) : _p(ptr) { }
		~iref() { if(_p) delete _p; }

		iref(iref<T> const& other) : _p(other._p ? other._p->clone() : NULL) { }
		iref<T>& operator = (BOOST_COPY_ASSIGN_REF(iref) rhs) {
			if(this != &rhs) {
				if(_p) delete _p;
				_p = rhs._p ? rhs._p->clone() : NULL;
			}
			return *this;
		}
		iref<T>& operator = (T* ptr) {
			if(_p) delete _p;
			_p = ptr;
			return *this;
		}

		iref(BOOST_RV_REF(iref) other) : _p(other._p) {
			other._p = NULL;
		}
		iref<T>& operator = (BOOST_RV_REF(iref) rhs) {
			if(this != &rhs) {
				if(_p) delete _p;
				_p = rhs._p;
				rhs._p = NULL;
			}
			return *this;
		}

		T* operator -> () { assert(_p); return _p; }
		T const* operator -> () const { assert(_p); return _p; }

		T& operator * () { assert(_p); return *_p; }
		T const& operator * () const { assert(_p); return *_p; }

		bool empty() const { return !_p; }

		T* get() { assert(_p); return _p; }
		T const* get() const { assert(_p); return _p; }

		void clear() { if(_p) delete _p; _p = NULL; }

		bool operator ! () const { return empty(); }
		operator bool () const { return !empty(); }
	};

}

#include <wrench/impl/end_header.hpp>

#endif
