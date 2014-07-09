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

    static JsonValue FromString( const std::string& text );

    
    /// Converters ///

    std::string AsString() const;


    /// Children Accessors ///

    Bool HasValue( const std::string& name ) const;
    Bool HasValue( const Char* name ) const;

    JsonValue operator[] ( const std::string& name ) const;


    // Get Functions
    // - Returns false if the value doesn't exist.
    //   Throws if the value can't be converted to the type.

    Bool GetBoolValue ( const std::string& name, Bool&  value ) const;
    Bool GetFloatValue( const std::string& name, Float& value ) const;

    Bool GetStringValue( const std::string& name, std::string& value ) const;


private:

    explicit JsonValue( std::shared_ptr< JsonValueImpl > impl );

    std::shared_ptr< JsonValueImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_VALUE_H
