// Macaron C++ Library - RapidJson Implementation

#include "MacaronPch.h"

#include "RapidJson/JsonTraversal.h"
#include "RapidJson/JsonValueImpl.h"
#include <Macaron/RapidJson/JsonReader.h>
#include <Caramel/FileSystem/FileInfo.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/String/Format.h>
#include <Caramel/String/ToString.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


namespace Macaron
{

namespace RapidJson
{

//
// Contents
//
//   JsonValue
//   JsonReader
//   JsonTraversal
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

    if ( doc->HasParseError() )
    {
        const auto error = doc->GetParseError();
        CARAMEL_THROW( "Parse JSON file %s failed: %d", fileName, error );
    }

    return JsonValue( std::make_shared< JsonValueImpl >( std::move( doc )));
}


JsonValue JsonValue::FromString( const std::string& text )
{
    rapidjson::StringStream stream( text.c_str() );

    auto doc = std::make_shared< rapidjson::Document >();
    doc->ParseStream( stream );

    if ( doc->HasParseError() )
    {
        const auto error = doc->GetParseError();
        CARAMEL_THROW( "Parse JSON string failed: %d", error );
    }

    return JsonValue( std::make_shared< JsonValueImpl >( std::move( doc )));
}


//
// Properties
//

Bool JsonValue::IsNull() const
{
    return m_impl->m_value.IsNull();
}

Bool JsonValue::IsBool() const
{
    return m_impl->m_value.IsBool();
}

Bool JsonValue::IsNumber() const
{
    return m_impl->m_value.IsNumber();
}

Bool JsonValue::IsString() const
{
    return m_impl->m_value.IsString();
}

Bool JsonValue::IsObject() const
{
    return m_impl->m_value.IsObject();
}

Bool JsonValue::IsArray() const
{
    return m_impl->m_value.IsArray();
}

Bool JsonValue::IsInt() const
{
    return m_impl->m_value.IsInt();
}

Bool JsonValue::IsUint() const
{
    return m_impl->m_value.IsUint();
}


//
// Converters
//

Int JsonValue::AsInt() const
{
    CARAMEL_CHECK_MSG( this->IsInt(),
        "JsonValue %s can't convert to Int", m_impl->m_tag );

    return m_impl->m_value.GetInt();
}

Uint JsonValue::AsUint() const
{
    CARAMEL_CHECK_MSG( this->IsUint(),
        "JsonValue %s can't convert to Uint", m_impl->m_tag );

    return m_impl->m_value.GetUint();
}

Float JsonValue::AsFloat() const
{
    CARAMEL_CHECK_MSG( this->IsNumber(),
        "JsonValue %s can't convert to Float", m_impl->m_tag );
    
    return static_cast< Float >( this->AsDouble() );
}

Double JsonValue::AsDouble() const
{
    CARAMEL_CHECK_MSG( this->IsNumber(),
        "JsonValue %s can't convert to Double", m_impl->m_tag );
    
    return m_impl->m_value.GetDouble();
}

std::string JsonValue::AsString() const
{
    CARAMEL_CHECK_MSG( this->IsString(),
        "JsonValue %s can't convert to String", m_impl->m_tag );

    return m_impl->m_value.GetString();
}


//
// Serialization
//

std::string JsonValue::ToString() const
{
    using namespace rapidjson;

    const rapidjson::Value& jvalue = m_impl->m_value;

    switch ( jvalue.GetType() )
    {
    case kStringType: return jvalue.GetString();
    case kNumberType:
    {
        if ( jvalue.IsInt() )
        {
            return Caramel::ToString( jvalue.GetInt() );
        }
        else if ( jvalue.IsUint() )
        {
            return Caramel::ToString( jvalue.GetUint() );
        }
        else
        {
            return Caramel::ToString( jvalue.GetDouble() );
        }
    }

    case kNullType:  return "null";
    case kFalseType: return "false";
    case kTrueType:  return "true";

    case kObjectType:
    case kArrayType:
    {
        StringBuffer sbuf;
        Writer< rapidjson::StringBuffer > writer( sbuf );
        jvalue.Accept( writer );
        return sbuf.GetString();
    }

    default:
        CARAMEL_NOT_REACHED();
    }
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


Bool JsonValue::GetIntValue( const std::string& name, Int& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = jvalue.GetInt();
    return true;
}


Bool JsonValue::GetUintValue( const std::string& name, Uint& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = jvalue.GetUint();
    return true;
}


Bool JsonValue::GetFloatValue( const std::string& name, Float& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = static_cast< Float >( jvalue.GetDouble() );
    return true;
}


Bool JsonValue::GetDoubleValue( const std::string& name, Double& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = jvalue.GetDouble();
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
// JSON Value Implementation
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
//
// JSON Reader
//

static std::string TranslateParseErrorCode( rapidjson::ParseErrorCode code );

Bool JsonReader::Parse( const std::string& text, JsonValue& value )
{
    rapidjson::StringStream stream( text.c_str() );

    rapidjson::Document doc;
    doc.ParseStream( stream );

    if ( doc.HasParseError() )
    {
        auto errorCode = doc.GetParseError();
        m_errorMessage = TranslateParseErrorCode( errorCode );
        return false;
    }

    return true;
}


std::string TranslateParseErrorCode( rapidjson::ParseErrorCode code )
{
    using namespace rapidjson;

    switch ( code )
    {
    case kParseErrorNone: return "";

    case kParseErrorDocumentEmpty:
        return "document empty";

    case kParseErrorDocumentRootNotObjectOrArray:
        return "document root not object or array";

    case kParseErrorDocumentRootNotSingular:
        return "document root not singular";

    case kParseErrorValueInvalid:
        return "value invalid";

    case kParseErrorObjectMissName:
        return "object miss name";

    case kParseErrorObjectMissColon:
        return "object miss colon";

    case kParseErrorObjectMissCommaOrCurlyBracket:
        return "object miss comma or curly bracket";

    case kParseErrorArrayMissCommaOrSquareBracket:
        return "array miss comma or square bracket";

    default: return Format( "error code: {0}", code );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// JSON Traversal
//

JsonTraversal::JsonTraversal( const std::string& text )
{
    rapidjson::StringStream stream( text.c_str() );
    
    // 0 : use default flags.
    const Caramel::Bool ok = m_reader.Parse( stream, *this );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron
