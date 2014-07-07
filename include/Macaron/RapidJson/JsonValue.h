// Macaron C++ Library - RapidJson - JSON Value Header

#ifndef __MACARON_RAPID_JSON_JSON_VALUE_H
#define __MACARON_RAPID_JSON_JSON_VALUE_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Caramel/String/Utf8String.h>


namespace Macaron
{

namespace RapidJson
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

    static JsonValue FromFile( const std::string& fileName );
    static JsonValue FromFile( const Utf8String&  fileName );


private:

    explicit JsonValue( std::shared_ptr< JsonValueImpl > impl );

    std::shared_ptr< JsonValueImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_VALUE_H
