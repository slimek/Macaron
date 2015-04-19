// Macaron C++ Library - JsonCpp Implementation

#include "MacaronPch.h"

#include "JsonCpp/JsonValueImpl.h"
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
        CARAMEL_THROW( "File not found: \"{0}\"", fileName );
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
        CARAMEL_THROW( "Parse JSON failed : {0}", reader.getFormattedErrorMessages() );
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


Uint JsonValue::Size() const
{
    return m_impl->size();
}


//
// Converters
//

Bool JsonValue::IsConvertibleTo( JsonValueType type ) const
{
    return m_impl->isConvertibleTo( static_cast< Json::ValueType >( type ));
}


Bool JsonValue::AsBool() const
{
    CARAMEL_CHECK_MSG(
        m_impl->isConvertibleTo( Json::booleanValue ), "Can't convert this value to boolean" );

    return m_impl->asBool();
}


Int JsonValue::AsInt() const
{
    CARAMEL_CHECK_MSG(
        m_impl->isConvertibleTo( Json::intValue ), "Can't convert this value to int" );

    return m_impl->asInt();
}


Uint JsonValue::AsUint() const
{
    CARAMEL_CHECK_MSG(
        m_impl->isConvertibleTo( Json::uintValue ), "Can't convert this value to uint" );

    return m_impl->asUInt();
}


Float JsonValue::AsFloat() const
{
    CARAMEL_CHECK_MSG(
        m_impl->isConvertibleTo( Json::realValue ), "Can't convert this value to float" );

    return static_cast< Float >( m_impl->asDouble() );
}


std::string JsonValue::AsString() const
{
    CARAMEL_CHECK_MSG(
        m_impl->isConvertibleTo( Json::stringValue ), "Can't convert this value to string" );

    return m_impl->asString();
}


//
// Children Accessors
//

Bool JsonValue::HasValue( const std::string& name ) const
{
    return m_impl->isMember( name );
}


Bool JsonValue::GetBoolValue( const std::string& name ) const
{
    Bool value = false;
    if ( ! this->QueryBoolValue( name, value ))
    {
        CARAMEL_THROW( "Value \"{0}\" not found", name );
    }
    return value;
}


Int JsonValue::GetIntValue( const std::string& name ) const
{
    Int value = 0;
    if ( ! this->QueryIntValue( name, value ))
    {
        CARAMEL_THROW( "Value \"{0}\" not found", name );
    }
    return value;
}


Uint JsonValue::GetUintValue( const std::string& name ) const
{
    Uint value = 0;
    if ( ! this->QueryUintValue( name, value ))
    {
        CARAMEL_THROW( "Value \"{0}\" not found", name );
    }
    return value;
}


Float JsonValue::GetFloatValue( const std::string& name ) const
{
    Float value = 0;
    if ( ! this->QueryFloatValue( name, value ))
    {
        CARAMEL_THROW( "Value \"{0}\" not found", name );
    }
    return value;
}


std::string JsonValue::GetStringValue( const std::string& name ) const
{
    std::string value;
    if ( ! this->QueryStringValue( name, value ))
    {
        CARAMEL_THROW( "Value \"{0}\" not found", name );
    }
    return value;
}


JsonValue JsonValue::GetValue( const std::string& name ) const
{
    JsonValue value;
    if ( ! this->QueryValue( name, value ))
    {
        CARAMEL_THROW( "Value \"{0}\" not found", name );
    }
    return value;
}


JsonValue JsonValue::operator[]( const std::string& name ) const
{
    return this->GetValue( name );
}


JsonValue JsonValue::operator[]( const Char* name ) const
{
    CARAMEL_ASSERT( name );
    return this->GetValue( name );
}


//
// Query Functions
//

Bool JsonValue::QueryBoolValue( const std::string& name, Bool& value ) const
{
    if ( ! m_impl->isMember( name )) { return false; }
    
    const Json::Value& jvalue = m_impl->At( name );

    CARAMEL_CHECK_MSG(
        jvalue.isConvertibleTo( Json::booleanValue ), "Can't convert value \"{0}\" to boolean", name );

    value = jvalue.asBool();
    return true;
}


Bool JsonValue::QueryIntValue( const std::string& name, Int& value ) const
{
    if ( ! m_impl->isMember( name )) { return false; }

    const Json::Value& jvalue = m_impl->At( name );

    CARAMEL_CHECK_MSG( 
        jvalue.isConvertibleTo( Json::intValue ), "Can't convert value \"{0}\" to int", name );

    value = jvalue.asInt();
    return true;
}


Bool JsonValue::QueryUintValue( const std::string& name, Uint& value ) const
{
    if ( ! m_impl->isMember( name )) { return false; }

    const Json::Value& jvalue = m_impl->At( name );

    CARAMEL_CHECK_MSG( 
        jvalue.isConvertibleTo( Json::uintValue ), "Can't convert value \"{0}\" to uint", name );

    value = jvalue.asUInt();
    return true;
}


Bool JsonValue::QueryFloatValue( const std::string& name, Float& value ) const
{
    if ( ! m_impl->isMember( name )) { return false; }

    const Json::Value& jvalue = m_impl->At( name );

    CARAMEL_CHECK_MSG( 
        jvalue.isConvertibleTo( Json::realValue ), "Can't convert value \"{0}\" to float", name );

    value = static_cast< Float >( jvalue.asDouble() );
    return true;
}


Bool JsonValue::QueryStringValue( const std::string& name, std::string& value ) const
{
    if ( ! m_impl->isMember( name )) { return false; }

    const Json::Value& jvalue = m_impl->At( name );

    CARAMEL_CHECK_MSG( 
        jvalue.isConvertibleTo( Json::stringValue ), "Can't convert value \"{0}\" to string", name );

    value = jvalue.asString();
    return true;
}


Bool JsonValue::QueryValue( const std::string& name, JsonValue& value ) const
{
    if ( ! m_impl->isMember( name )) { return false; }
    
    value.m_impl = std::make_shared< JsonValueImpl >( m_impl->At( name ));
    return true;
}


//
// Array Accessors
//

JsonValue JsonValue::GetValueAt( Uint index ) const
{
    CARAMEL_CHECK_MSG(
        Json::arrayValue == m_impl->type(), "This value is not an array" );

    CARAMEL_CHECK_MSG(
        m_impl->size() > index, "Index is out of range" );

    return JsonValue( std::make_shared< JsonValueImpl >( m_impl->At( index )));
}


JsonValue JsonValue::operator[]( Uint index ) const
{
    return this->GetValueAt( index );
}


JsonValue JsonValue::operator[]( Int index ) const
{
    return this->GetValueAt( index );
}


//
// Implementation
//

JsonValueImpl::JsonValueImpl( const Json::Value& value )
    : Json::Value( value )
{
}


const Json::Value& JsonValueImpl::At( const std::string& name ) const
{
    return this->operator[]( name );
}


const Json::Value& JsonValueImpl::At( Uint index ) const
{
    return this->operator[]( index );
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
static_assert( Json::booleanValue == JSON_VALUE_BOOL,    "5" );
static_assert( Json::arrayValue   == JSON_VALUE_ARRAY,   "6" );
static_assert( Json::objectValue  == JSON_VALUE_OBJECT,  "7" );


///////////////////////////////////////////////////////////////////////////////

} // namespace JsonCpp

} // namespace Macaron
