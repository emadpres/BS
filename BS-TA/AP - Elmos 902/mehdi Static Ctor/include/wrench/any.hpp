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

#ifndef WRENCH_ANY_HPP
#define WRENCH_ANY_HPP

#include <wrench/config.hpp>

#include <boost/move/move.hpp>
#include <boost/swap.hpp>
#include <wrench/except.hpp>
#include <iostream>
#include <typeinfo>

#include <wrench/impl/begin_header.hpp>

namespace wrench {

	namespace impl { namespace any {

		struct value_holder_base {
			virtual ~value_holder_base() { }
			virtual value_holder_base* clone() const = 0;
			virtual ::std::type_info const& type() const = 0;
			virtual ::std::basic_ostream<char>& output(::std::basic_ostream<char>& stream) const = 0;

#if defined(UNICODE)
			virtual ::std::basic_ostream<wchar_t>& output(::std::basic_ostream<wchar_t>& stream) const = 0;
#endif
		};

		template<class T>
		struct value_holder : public value_holder_base {
			T _value;

			value_holder() : _value() { }
			value_holder(T const& value) : _value(value) { }
			value_holder(BOOST_RV_REF(T) value) : _value(value) { }

			value_holder_base* clone() const { return new value_holder<T>(*this); }
			::std::type_info const& type() const { return typeid(T); }
			::std::basic_ostream<char>& output(::std::basic_ostream<char>& stream) const { 
				return stream << _value;
			}

#if defined(UNICODE)
			::std::basic_ostream<wchar_t>& output(::std::basic_ostream<wchar_t>& stream) const {
				return stream << _value;
			}
#endif
		};
	} }


	class any {

		::wrench::impl::any::value_holder_base* _value;

		BOOST_COPYABLE_AND_MOVABLE(any);

		template<class T>
		friend T* any_cast(any *);

		template<class T>
		friend T const* any_cast(any const*);

		template<class _char>
		friend ::std::basic_ostream<_char>& operator << (::std::basic_ostream<_char>& _, any const& value);

	public:

		any() : _value(NULL) { }
		template<class T> any(T const& value) : _value( new ::wrench::impl::any::value_holder<T>(value) ) { }
		~any() { if(_value) delete _value; }

		any(any const& other) : _value(other._value ? other._value->clone() : NULL) { }
		any(BOOST_RV_REF(any) other) : _value(other._value) { other._value = NULL; }

		any& operator = (BOOST_COPY_ASSIGN_REF(any) other) {
			if(this != &other) {
				if(_value) delete _value;
				_value = other._value ? other._value->clone() : NULL;
			}
			return *this;
		}
		any& operator = (BOOST_RV_REF(any) other) {
			if(this != &other) {
				if(_value) delete _value;
				_value = other._value;
				other._value = NULL;
			}
			return *this;
		}

		template<class T>
		any& operator = (T const& value) {
			if(_value) delete _value;
			_value = new ::wrench::impl::any::value_holder<T>(value);
			return *this;
		}

		template<class T>
		any& operator = (BOOST_RV_REF(T) value) {
			if(_value) delete _value;
			_value = new ::wrench::impl::any::value_holder<T>(value);
			return *this;
		}

		bool empty() const { return !_value; }

		::std::type_info const& type() const { return _value ? _value->type() : typeid(void); }

		any& swap(any& rhs) {
			::boost::swap(_value, rhs._value);
			return *this;
		}
	};

	class bad_any_value : public ::wrench::runtime_error {
	public:
		bad_any_value(const char* msg, int line, const char* file, const char* function) : ::wrench::runtime_error(msg, line, file, function) { }
		bad_any_value(::std::string const& msg, int line, const char* file, const char* function) : ::wrench::runtime_error(msg, line, file, function) { }
	};

	template<class _char>
	::std::basic_ostream<_char>& operator << (::std::basic_ostream<_char>& _, any const& value) {
		if(value.empty()) throw_(::wrench::bad_any_value, "can not output value to stream because value is empty.");
		return value._value->output(_);
	}

	class bad_any_cast : public ::wrench::runtime_error {
	public:
		bad_any_cast(const char* msg, int line, const char* file, const char* function) : ::wrench::runtime_error(msg, line, file, function) { }
		bad_any_cast(::std::string const& msg, int line, const char* file, const char* function) : ::wrench::runtime_error(msg, line, file, function) { }
	};

	template<class T>
	T* any_cast(any* value) {
		return value->type() == typeid(T) ? & ( static_cast<::wrench::impl::any::value_holder<T>*>( value->_value )->_value ) : NULL;
	}
	
	template<class T>
	T const* any_cast(any const*) {
		return value->type() == typeid(T) ? & ( static_cast<::wrench::impl::any::value_holder<T> const*>( value->_value )->_value ) : NULL;
	}

	template<class T>
	T& any_cast(any& value) {
		T* result = any_cast<T>(&value);
		if(!result)
			throw_(::wrench::bad_any_cast, "unable to cast value from type " << value.type().name() << " to " << typeid(T).name() << ".");
		return *result;
	}

	template<class T>
	T const& any_cast(any const& value) {
		T const* result = any_cast<T>(&value);
		if(!result)
			throw_(::wrench::bad_any_cast, "unable to cast value from type " << value.type().name() << " to " << typeid(T).name() << ".");
		return *result;
	}
}

#include <wrench/impl/end_header.hpp>

#endif
