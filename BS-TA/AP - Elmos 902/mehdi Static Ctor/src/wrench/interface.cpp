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

#include <wrench/interface.hpp>
#include <boost/uuid/uuid_io.hpp>

::wrench::impl::interface_tag::class_object_type $class;

::wrench::$interface* ::wrench::impl::interface_tag::class_object_type::create(::boost::uuids::uuid const& uuid) const {
	::boost::container::map< ::boost::uuids::uuid , ::wrench::interface_factory >::const_iterator i = uuid_to_factory->find(uuid);
	if(i == uuid_to_factory->end()) {
		throw_(::wrench::unregistered_class_error, "unregistered class requested with uuid " << uuid);
	}
	return i->second();
}

::wrench::$interface* ::wrench::impl::interface_tag::class_object_type::create(::std::string const& type) const {
	::boost::container::map< ::std::string , ::boost::uuids::uuid >::const_iterator i = type_to_uuid->find(type);
	if(i == type_to_uuid->end()) {
		throw_(::wrench::unregistered_class_error, "unregistered class requested with type " << type);
	}
	return create(i->second);
}

::wrench::$interface* ::wrench::impl::interface_tag::class_object_type::create(::std::type_info const& type) const {
	return create( type.name() );
}

