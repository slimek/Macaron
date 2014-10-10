// Macaron C++ Library - RapidJson - JSON Value Header

#ifndef __MACARON_RAPID_JSON_JSON_VALUE_H
#define __MACARON_RAPID_JSON_JSON_VALUE_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Caramel/String/Utf8String.h>
#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <iterator>


namespace Macaron
{

namespace RapidJson
{

// Forwards Declaration
class JsonArray;
class JsonValueImpl;

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
//

class JsonValue
{
public:

    JsonValue();
    explicit JsonValue( std::shared_ptr< JsonValueImpl > impl );

    /// Parsing ///

    static JsonValue FromFile  ( const std::string& filePath );
    static JsonValue FromString( const std::string& text );

    // NOTES: If you need to return false when parsing failed, use JsonReader class.


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

    Bool   AsBool()   const;
    Int    AsInt()    const;
    Uint   AsUint()   const;
    Float  AsFloat()  const;
    Double AsDouble() const;

    std::string AsString() const;

    JsonArray AsArray() const;


    /// Serialize to a string representing the JSON ///

    std::string ToString() const;


    /// Object Children Accessors ///

    Bool HasValue( const std::string& name ) const;
    Bool HasValue( const Char* name ) const;

    JsonValue operator[] ( const std::string& name ) const;
    JsonValue operator[] ( const Char* name ) const;


    // Get Functions
    // - Returns false if the value doesn't exist.
    //   Throws if the value can't be converted to the type.

    Bool GetBool  ( const std::string& name, Bool&   value ) const;
    Bool GetInt   ( const std::string& name, Int&    value ) const;
    Bool GetUint  ( const std::string& name, Uint&   value ) const;
    Bool GetFloat ( const std::string& name, Float&  value ) const;
    Bool GetDouble( const std::string& name, Double& value ) const;
    
    Bool GetString( const std::string& name, std::string& value ) const;

    Bool GetValue( const std::string& name, JsonValue& value ) const;
    Bool GetArray( const std::string& name, JsonArray& value ) const;


    // Get Functions - Return optionals

    boost::optional< std::string > GetString( const std::string& name ) const;


    /// Extention Properties ///

    // Tag
    // - For tracing and error messages.

    void SetTag( const std::string& tag );
    std::string GetTag() const;


protected:

    friend class JsonReader;
    friend class JsonArray;

    std::shared_ptr< JsonValueImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////
//
// JSON Array
//

class JsonArrayConstIterator;

class JsonArray : public JsonValue
{
    friend class JsonValue;

public:

    JsonArray();

    // Throws if the file is not a JSON array, even if it is a valid JSON.
    static JsonArray FromFile( const std::string& filePath );

    // Throws if 'text' is not a JSON array, even if it is a valid JSON.
    static JsonArray FromString( const std::string& text );


    /// Array Elemenet Accessors ///

    Uint Size() const;

    JsonValue operator[]( Uint index ) const;


    /// Array Iterator Accessors ///

    JsonArrayConstIterator Begin() const;
    JsonArrayConstIterator End()   const;

    
    /// STL Compatible ///

    typedef JsonArrayConstIterator const_iterator;

    const_iterator begin() const;
    const_iterator end()   const;


private:

    explicit JsonArray( std::shared_ptr< JsonValueImpl > impl );
};


///////////////////////////////////////////////////////////////////////////////
//
// JSON Array Const Iterator
//

class JsonArrayConstIterator
    : public std::iterator< std::forward_iterator_tag, JsonValue >
    , public boost::equality_comparable< JsonArrayConstIterator >
{
    friend class JsonArray;
    class Impl;

public:

    /// Operators ///

    JsonArrayConstIterator& operator++();

    Bool operator==( const JsonArrayConstIterator& other ) const;

    std::unique_ptr< const JsonValue > operator->() const;
    JsonValue operator*() const;


private:

    explicit JsonArrayConstIterator( std::shared_ptr< Impl > impl );

    std::shared_ptr< Impl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_VALUE_H
