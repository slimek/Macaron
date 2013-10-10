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

class JsonNode;
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

    // Number of children.
    Uint Size() const;


    /// Converters ///

    Bool  AsBool() const;
    Int   AsInt()  const;
    Float AsFloat() const;

    std::string AsString() const;


    /// Children Accessors ///

    Bool HasValue( const std::string& name ) const;
    
    Bool  GetBoolValue ( const std::string& name ) const;
    Int   GetIntValue  ( const std::string& name ) const;
    Float GetFloatValue( const std::string& name ) const;

    std::string GetStringValue( const std::string& name ) const;

    JsonValue GetValue( const std::string& name ) const;

    JsonValue operator[]( const std::string& name ) const;
    JsonValue operator[]( const Char* name ) const;


    /// Array Element Accessors ///

    JsonValue GetValueAt( Uint index ) const;

    JsonValue operator[]( Uint index ) const;
    JsonValue operator[]( Int  index ) const;


private:

    explicit JsonValue( std::shared_ptr< JsonNode > node );

    std::shared_ptr< JsonNode > m_node;
};


///////////////////////////////////////////////////////////////////////////////
//
// Enumerations
//

//
// JSON Value Type
// - Values are equivalent to libjson's value types.

enum JsonValueType : Int8
{
    JSON_VALUE_NULL     = 0,
    JSON_VALUE_STRING   = 1,
    JSON_VALUE_NUMBER   = 2,
    JSON_VALUE_BOOLEAN  = 3,
    JSON_VALUE_ARRAY    = 4,
    JSON_VALUE_OBJECT   = 5,
};


///////////////////////////////////////////////////////////////////////////////

} // namespace LibJson

} // namespace Macaron

#endif // __MACARON_LIB_JSON_JSON_VALUE_H