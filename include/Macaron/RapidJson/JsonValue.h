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


    /// Properties ///

    Bool IsNull()   const;
    Bool IsBool()   const;
    Bool IsNumber() const;
    Bool IsString() const;
    Bool IsObject() const;
    Bool IsArray()  const;

    Bool IsInt()    const;
    Bool IsUint()   const;

    
    /// Converters ///

    Int    AsInt()    const;
    Uint   AsUint()   const;
    Float  AsFloat()  const;
    Double AsDouble() const;

    std::string AsString() const;


    /// Serialize to a string representing the JSON ///

    std::string ToString() const;


    /// Object Children Accessors ///

    Bool HasValue( const std::string& name ) const;
    Bool HasValue( const Char* name ) const;

    JsonValue operator[] ( const std::string& name ) const;


    // Get Functions
    // - Returns false if the value doesn't exist.
    //   Throws if the value can't be converted to the type.

    Bool GetBoolValue  ( const std::string& name, Bool&   value ) const;
    Bool GetIntValue   ( const std::string& name, Int&    value ) const;
    Bool GetUintValue  ( const std::string& name, Uint&   value ) const;
    Bool GetFloatValue ( const std::string& name, Float&  value ) const;
    Bool GetDoubleValue( const std::string& name, Double& value ) const;

    Bool GetStringValue( const std::string& name, std::string& value ) const;


private:

    explicit JsonValue( std::shared_ptr< JsonValueImpl > impl );

    std::shared_ptr< JsonValueImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_VALUE_H
