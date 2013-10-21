// Macaron C++ Library - JsonCpp - JSON Value Header

#ifndef __MACARON_JSON_CPP_JSON_VALUE_H
#define __MACARON_JSON_CPP_JSON_VALUE_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/Utf8String.h>


namespace Macaron
{

namespace JsonCpp
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
//

class JsonValueImpl;
enum JsonValueType : Int8;

class JsonValue
{
public:

    JsonValue();

    static JsonValue FromFile( const std::string& fileName );
    static JsonValue FromFile( const Utf8String&  fileName );

    static JsonValue FromString( const std::string& text );


    /// Properties ///

    JsonValueType Type() const;

    Bool IsEmpty() const;

    // Number of children nodes or array elements.
    Uint Size() const;


    /// Converters ///

    Bool IsConvertibleTo( JsonValueType type ) const;

    Bool  AsBool()  const;
    Int   AsInt()   const;
    Uint  AsUint()  const;
    Float AsFloat() const;

    std::string AsString() const;


    /// Children Accessors ///

    Bool HasValue( const std::string& name ) const;
    
    Bool  GetBoolValue ( const std::string& name ) const;
    Int   GetIntValue  ( const std::string& name ) const;
    Uint  GetUintValue ( const std::string& name ) const;
    Float GetFloatValue( const std::string& name ) const;

    std::string GetStringValue( const std::string& name ) const;

    JsonValue GetValue( const std::string& name ) const;

    JsonValue operator[]( const std::string& name ) const;
    JsonValue operator[]( const Char* name ) const;

    //
    // Query Functions
    // - Returns false if the value doesn't exist,
    //   Throws if the value can't cast to the type.
    //
    Bool QueryBoolValue ( const std::string& name, Bool&  value ) const;
    Bool QueryIntValue  ( const std::string& name, Int&   value ) const;
    Bool QueryUintValue ( const std::string& name, Uint&  value ) const;
    Bool QueryFloatValue( const std::string& name, Float& value ) const;
    
    Bool QueryStringValue( const std::string& name, std::string& value ) const;

    Bool QueryValue( const std::string& name, JsonValue& value ) const;


    /// Array Element Accessors ///

    JsonValue GetValueAt( Uint index ) const;

    JsonValue operator[]( Uint index ) const;
    JsonValue operator[]( Int  index ) const;


private:

    explicit JsonValue( std::shared_ptr< JsonValueImpl > impl );

    std::shared_ptr< JsonValueImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////
//
// Enumerations
//

//
// JSON Value Type
// - Values are equivalent to JsonCpp's value types.
//
enum JsonValueType : Int8
{
    JSON_VALUE_NULL     = 0,
    JSON_VALUE_INT      = 1,
    JSON_VALUE_UINT     = 2,
    JSON_VALUE_DOUBLE   = 3,  // Exchangeable to Float
    JSON_VALUE_STRING   = 4,
    JSON_VALUE_BOOL     = 5,
    JSON_VALUE_ARRAY    = 6,
    JSON_VALUE_OBJECT   = 7,
};


///////////////////////////////////////////////////////////////////////////////

} // namespace JsonCpp

} // namespace Macaron

#endif // __MACARON_JSON_CPP_JSON_VALUE_H
