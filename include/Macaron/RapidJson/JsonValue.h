// Macaron C++ Library - RapidJson - JSON Value Header

#ifndef __MACARON_RAPID_JSON_JSON_VALUE_H
#define __MACARON_RAPID_JSON_JSON_VALUE_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/Utf8String.h>
#include <RapidJson/document.h>
#include <RapidJson/stringbuffer.h>
#include <RapidJson/writer.h>
#include <memory>


namespace Macaron
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
//

class JsonValue
{
public:

    JsonValue();


    /// String Output ///

    Utf8String  ToUtf8String() const;
    std::string ToString()     const;


    /// String & File Input ///

    struct ParseResult
    {
        ParseResult() : ok( false ) {}

        operator Bool() const { return ok; }

        Bool ok;
        std::string message;  // If parsing failed, get error message here.
    };

    ParseResult TryParse( const Utf8String&  input );
    ParseResult TryLoadFromFile( const Utf8String& fileName );



private:

    /// String I/O ///

    std::string DoToString() const;


    /// Data Members ///

    std::shared_ptr< rapidjson::Value > m_value;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline JsonValue::JsonValue()
    : m_value( new rapidjson::Value( rapidjson::kObjectType ))
{
}


//
// String Output
//

inline Utf8String  JsonValue::ToUtf8String() const { return Utf8String( this->DoToString() ); }
inline std::string JsonValue::ToString()     const { return this->DoToString(); }


inline std::string JsonValue::DoToString() const
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer< rapidjson::StringBuffer > writer( buffer );

    m_value->Accept( writer );

    return buffer.GetString();
}


//
// String & File Input
//

inline JsonValue::ParseResult JsonValue::TryParse( const Utf8String& input )
{
    std::shared_ptr< rapidjson::Document > document( new rapidjson::Document() );

    rapidjson::StringStream stream( input.ToCstr() );
    document->ParseStream< 0 >( stream );

    ParseResult result;

    if ( document->HasParseError() )
    {
        result.message = document->GetParseError();
    }
    else
    {
        m_value = document;
        result.ok = true;
    }

    return result;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_VALUE_H
