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

#ifndef WRENCH_CONFIG_HPP
#define WRENCH_CONFIG_HPP

#include <wrench/impl/begin_header.hpp>

#define WRENCH_VERSION_MAJOR 1
#define WRENCH_VERSION_MINOR 0

#if !defined(NDEBUG) || defined(_DEBUG)

    #define WRENCH_DEBUG

#endif

#if defined(_WIN32) || defined(__WIN32__)

    #define WRENCH_SYSTEM_WINDOWS
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

#elif defined(linux) || defined(__linux)

    #define WRENCH_SYSTEM_LINUX

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

    #define WRENCH_SYSTEM_MACOS

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

    #define WRENCH_SYSTEM_FREEBSD

#else

    #error This operating system is not supported by SFML library

#endif

#if defined(WRENCH_SYSTEM_WINDOWS)

    #ifdef WRENCH_DYNAMIC

        #ifdef WRENCH_EXPORTS

            #define WRENCH_API __declspec(dllexport)

        #else

            #define WRENCH_API __declspec(dllimport)

        #endif

        #ifdef _MSC_VER

            #pragma warning(disable : 4251)

        #endif

    #else

        #define WRENCH_API

    #endif

#else

    #define WRENCH_API

#endif


#if !defined(WRENCH_EXPORTS) && defined(_MSC_VER)

#if defined(WRENCH_DEBUG)
#define WRENCH_AUTOIMPORT_DEBUG
#else
#define WRENCH_AUTOIMPORT_RELEASE
#endif

#endif

#if defined(WRENCH_AUTOIMPORT_DEBUG)
#pragma comment(lib, "wrench-d.lib")
#endif

#if defined(WRENCH_AUTOIMPORT_RELEASE)
#pragma comment(lib, "wrench.lib")
#endif

namespace wrench { struct na { }; }

#include <wrench/impl/end_header.hpp>

#endif
