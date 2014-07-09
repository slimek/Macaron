// Macaron C++ Library - RapidJson Implementation

#include "MacaronPch.h"

#include "RapidJson/JsonValueImpl.h"
#include <Caramel/FileSystem/FileInfo.h>
#include <Caramel/Io/InputFileStream.h>
#include <rapidjson/filereadstream.h>


namespace Macaron
{

namespace RapidJson
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


JsonValue::JsonValue( std::shared_ptr< JsonValueImpl > impl )
    : m_impl( impl )
{
}


//
// Creating
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

    const Uint BUFFER_SIZE = 1024;
    Char buffer[ BUFFER_SIZE ] = { 0 };

    InputFileStream file( fileName );
    rapidjson::FileReadStream stream( file.GetFilePointer(), &buffer[0], BUFFER_SIZE );

    auto doc = std::make_shared< rapidjson::Document >();
    doc->ParseStream( stream );

    return JsonValue( std::make_shared< JsonValueImpl >( std::move( doc )));
}


JsonValue JsonValue::FromString( const std::string& text )
{
    rapidjson::StringStream stream( text.c_str() );

    auto doc = std::make_shared< rapidjson::Document >();
    doc->ParseStream( stream );

    return JsonValue( std::make_shared< JsonValueImpl >( std::move( doc )));
}


//
// Converters
//

std::string JsonValue::AsString() const
{
    CARAMEL_CHECK_MSG(
        m_impl->IsConvertibleToString(), "Can't convert this value to string" );

    return m_impl->GetString();
}


//
// Children Accessors
//

Bool JsonValue::HasValue( const std::string& name ) const
{
    return m_impl->HasMember( name.c_str() );
}


Bool JsonValue::HasValue( const Char* name ) const
{
    return m_impl->HasMember( name );
}


JsonValue JsonValue::operator[]( const std::string& name ) const
{
    return JsonValue( m_impl->GetValue( name.c_str() ));
}


Bool JsonValue::GetBoolValue( const std::string& name, Bool& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = jvalue.GetBool();
    return true;
}


Bool JsonValue::GetFloatValue( const std::string& name, Float& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = static_cast< Float >( jvalue.GetDouble() );
    return true;
}


Bool JsonValue::GetStringValue( const std::string& name, std::string& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = jvalue.GetString();
    return true;
}


//
// Implementation
//

JsonValueImpl::JsonValueImpl()
    : m_document( std::make_shared< rapidjson::Document >() )
    , m_value( *m_document )
{
}


JsonValueImpl::JsonValueImpl( std::shared_ptr< rapidjson::Document >&& doc )
    : m_document( std::move( doc ))
    , m_value( *m_document )
{
}


JsonValueImpl::JsonValueImpl( std::shared_ptr< rapidjson::Document > doc, rapidjson::Value& value )
    : m_document( doc )
    , m_value( value )
{
}


//
// Predicates
//

Bool JsonValueImpl::IsConvertibleToString() const
{
    return m_value.IsString();
}


//
// Converters
//

std::string JsonValueImpl::GetString() const
{
    return m_value.GetString();
}


//
// Children Accessors
//

Bool JsonValueImpl::HasMember( const Char* name ) const
{
    return m_value.HasMember( name );
}


std::shared_ptr< JsonValueImpl > JsonValueImpl::GetValue( const Char* name )
{
    return std::make_shared< JsonValueImpl >( m_document, m_value[ name ] );
}


const rapidjson::Value& JsonValueImpl::At( const Char* name ) const
{
    return m_value[ name ];
}


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron
