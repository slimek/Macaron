// Macaron C++ Library - LibJson - JSON Value Header

#ifndef __MACARON_LIB_JSON_JSON_VALUE_H
#define __MACARON_LIB_JSON_JSON_VALUE_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Macaron
{

namespace LibJson
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
//

class JsonValueImpl;

class JsonValue
{
public:

    JsonValue();
    explicit JsonValue( const std::string& fileName );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace LibJson

} // namespace Macaron

#endif // __MACARON_LIB_JSON_JSON_VALUE_H