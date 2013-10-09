// Macaron C++ Library - LibJson - JSON Value Header

#ifndef __MACARON_LIB_JSON_JSON_VALUE_H
#define __MACARON_LIB_JSON_JSON_VALUE_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/Utf8String.h>


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
    virtual ~JsonValue();

    static JsonValue LoadFromFile( const std::string& fileName );
    static JsonValue LoadFromFile( const Utf8String&  fileName );

    static JsonValue LoadFromString( const std::string& text );


    //
    // Accessors
    //

    Int   AsInt()   const;
    Float AsFloat() const;

    std::string AsString() const;


    //
    // Children Accessors
    //

    JsonValue operator[]( const std::string& name ) const;


private:

    explicit JsonValue( JsonValueImpl* impl );

    std::shared_ptr< JsonValueImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace LibJson

} // namespace Macaron

#endif // __MACARON_LIB_JSON_JSON_VALUE_H