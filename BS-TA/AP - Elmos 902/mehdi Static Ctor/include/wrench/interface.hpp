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

#ifndef WRENCH_INTERFACE_HPP
#define WRENCH_INTERFACE_HPP

#include <wrench/config.hpp>

#include <boost/function.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/container/map.hpp>
#include <wrench/except.hpp>
#include <wrench/static_ctor.hpp>
#include <typeinfo>
#include <string>

#include <wrench/impl/begin_header.hpp>

namespace wrench {

	struct $interface;
	
	class unregistered_class_error : public ::wrench::runtime_error {
	public:
		unregistered_class_error(const char* msg, int line, const char* file, const char* function) : ::wrench::runtime_error(msg, line, file, function) { }
		unregistered_class_error(::std::string const& msg, int line, const char* file, const char* function) : ::wrench::runtime_error(msg, line, file, function) { }
	};

	typedef ::boost::function< $interface* () > interface_factory;

	namespace impl { namespace interface_tag {

		struct class_object_type {
			::boost::container::map< ::std::string , ::boost::uuids::uuid > *type_to_uuid;
			::boost::container::map< ::boost::uuids::uuid , ::std::string > *uuid_to_type;
			::boost::container::map< ::boost::uuids::uuid , ::wrench::interface_factory > *uuid_to_factory;

			::wrench::$interface* create(::std::type_info const& type) const;
			::wrench::$interface* create(::std::string const& type) const;
			::wrench::$interface* create(::boost::uuids::uuid const& uuid) const;
			
			template<class T> ::wrench::$interface* create() const {
				return create(typeid(T));
			}
		};

	} }

	struct $interface {
		virtual ~$interface() { }

		virtual ::std::type_info const& type() const = 0;
		virtual ::boost::uuids::uuid const& uuid() const = 0;
		virtual $interface* clone() const = 0;
		virtual ::wrench::interface_factory factory() const = 0;
	};
}

#define $declare_interface(classname) \
	STATIC_CONSTRUCTOR_TAG(classname, __interface_initialization__); \
	static ::boost::uuids::uuid ____wrench___##classname##__uuid; \
	static ::wrench::$interface*  ____wrench___##classname##__factory (); \
	public: \
		classname(); \
		::std::type_info const& type() const; \
		::boost::uuids::uuid const& uuid() const; \
		::wrench::$interface* clone() const; \
		::wrench::interface_factory factory() const; \
	private:

#define $define_interface(classname, class_uuid) \
	::boost::uuids::uuid classname::____wrench___##classname##__uuid; \
	::std::type_info const& classname::type() const { return typeid(classname); } \
	::boost::uuids::uuid const& classname::uuid() const { return ____wrench___##classname##__uuid; } \
	::wrench::$interface* classname::clone() const { return new classname(*this); } \
	::wrench::interface_factory classname::factory() const { return &classname::____wrench___##classname##__factory; } \
	::wrench::$interface*  classname::____wrench___##classname##__factory () { return new classname(); } \
	static_tag_(classname, __interface_initialization__) { \
		if(!::$class.type_to_uuid) ::$class.type_to_uuid = new ::boost::container::map< ::std::string , ::boost::uuids::uuid >(); \
		if(!::$class.uuid_to_type) ::$class.uuid_to_type = new ::boost::container::map< ::boost::uuids::uuid , ::std::string >(); \
		if(!::$class.uuid_to_factory) $class.uuid_to_factory = new ::boost::container::map< ::boost::uuids::uuid , ::wrench::interface_factory >(); \
		::boost::uuids::string_generator gen; \
		____wrench___##classname##__uuid = gen(class_uuid); \
		(*::$class.type_to_uuid)[ typeid(classname).name() ] = ____wrench___##classname##__uuid; \
		(*::$class.uuid_to_type)[ ____wrench___##classname##__uuid ] = typeid(classname).name(); \
		(*::$class.uuid_to_factory)[ ____wrench___##classname##__uuid ] = &classname::____wrench___##classname##__factory; \
	} \
	classname::classname()


extern ::wrench::impl::interface_tag::class_object_type $class;

#include <wrench/impl/end_header.hpp>

#endif
