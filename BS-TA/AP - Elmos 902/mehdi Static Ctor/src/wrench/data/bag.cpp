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

#include <wrench/data/bag.hpp>

#include <wrench/except.hpp>

::wrench::any& ::wrench::data::bag::at(::std::string const& key) {
	::boost::container::map< ::std::string, int >::iterator it = _m.find(key);
	if(it != _m.end()) {
		return _vals[it->second];
	} else {
		int next = -1;
		next = _vals.size();
		_vals.push_back(0.0);
		_isrem.push_back(false);
		_k.push_back(key);
		_m[key] = next;
		return _vals[next];
	}
}

::wrench::any const& ::wrench::data::bag::at(::std::string const& key) const {
	::boost::container::map< ::std::string, int >::const_iterator it = _m.find(key);
	if(it != _m.end()) {
		return _vals[it->second];
	} else {
		throw_runtime_error_("unable to find key in the bag with key = " << key);
	}
}

::wrench::any& ::wrench::data::bag::operator [] (::std::string const& key) { return at(key); }
::wrench::any const& ::wrench::data::bag::operator [] (::std::string const& key) const { return at(key); }

bool ::wrench::data::bag::removeKey(::std::string const& key) { 
	::boost::container::map< ::std::string, int >::iterator it = _m.find(key);
	if(it != _m.end()) {
		int idx = it->second;
		_m.erase(it);
		_isrem[idx] = true;
		_k[idx] = "";
		_vals[idx] = 0;

		while( !_isrem.empty() && _isrem.back() ) {
			_isrem.pop_back();
			_vals.pop_back();
			_k.pop_back();
		}

		return true;
	} else return false;
}

bool ::wrench::data::bag::hasKey(::std::string const& key) const {
	::boost::container::map< ::std::string, int >::const_iterator it = _m.find(key);
	if(it != _m.end()) return true;
	return false;
}

void ::wrench::data::bag::clear() {
	_vals.clear();
	_m.clear();
	_isrem.clear();
	_k.clear();
}

