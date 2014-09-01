// Macaron C++ Library - CppRest - Utility Header

#ifndef __MACARON_CPP_REST_UTILITY_H
#define __MACARON_CPP_REST_UTILITY_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <cpprest/uri.h>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Caramel/String/Utf8String.h>
#endif


namespace Macaron
{

namespace CppRest
{

///////////////////////////////////////////////////////////////////////////////
//
// Unicode String
// - Convert std::string to C++ REST utility::string_t.
//

utility::string_t ToUstr( const std::string& s )
{
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        return Utf8String( s ).ToWstring();
    }
    #else
    {
        return s;
    }
    #endif
}


std::string FromUstr( const utility::string_t& s )
{
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        return Utf8String( s ).ToString();
    }
    #else
    {
        return s;
    }
    #endif
}


///////////////////////////////////////////////////////////////////////////////

} // namespace CppRest

} // namespace Macaron


#endif // __MACARON_CPP_REST_UTILITY_H
