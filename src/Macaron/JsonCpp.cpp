// Macaron C++ Library - JsonCpp Implementation

#include <Macaron/MacaronPch.h>

#include <Macaron/JsonCpp/JsonValueImpl.h>
#include <Caramel/FileSystem/FileInfo.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>
#include <JsonCpp/json.h>


namespace Macaron
{

namespace JsonCpp
{

//
// Contents
//
//   JsonValue
//

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
//

JsonValue::JsonValue()
    : m_impl( new JsonValueImpl )
{
}


JsonValue::JsonValue( JsonValuePtr impl )
    : m_impl( impl )
{
}


//
// Create Functions
//

JsonValue JsonValue::FromFile( const std::string& fileName )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8FileName, fileName );

    return FromFile( u8FileName );
}


JsonValue JsonValue::FromFile( const Utf8String& fileName )
{
    if ( ! FileInfo( fileName ).Exists() )
    {
        CARAMEL_THROW( "File not found: %s", fileName );
    }

    InputFileStream file( fileName );
    TextStreamReader reader( file );

    return FromString( reader.ReadAll() );
}


JsonValue JsonValue::FromString( const std::string& text )
{
    Json::Value value;
    Json::Reader reader;
    const Bool ok = reader.parse( text, value );
    if ( ! ok )
    {
        CARAMEL_THROW( "Parse JSON failed : %s", reader.getFormatedErrorMessages() );
    }
    return JsonValue( std::make_shared< JsonValueImpl >( value ));
}


//
// Properties
//

JsonValueType JsonValue::Type() const
{
    return static_cast< JsonValueType >( m_impl->type() );
}


Bool JsonValue::IsEmpty() const
{
    return m_impl->empty();
}


//
// Implementation
//

JsonValueImpl::JsonValueImpl( const Json::Value& value )
    : Json::Value( value )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Constants Validation
//

static_assert( Json::nullValue    == JSON_VALUE_NULL,    "0" );
static_assert( Json::intValue     == JSON_VALUE_INT,     "1" );
static_assert( Json::uintValue    == JSON_VALUE_UINT,    "2" );
static_assert( Json::realValue    == JSON_VALUE_DOUBLE,  "3" );
static_assert( Json::stringValue  == JSON_VALUE_STRING,  "4" );
static_assert( Json::booleanValue == JSON_VALUE_BOOLEAN, "5" );
static_assert( Json::arrayValue   == JSON_VALUE_ARRAY,   "6" );
static_assert( Json::objectValue  == JSON_VALUE_OBJECT,  "7" );


///////////////////////////////////////////////////////////////////////////////

} // namespace JsonCpp

} // namespace Macaron
