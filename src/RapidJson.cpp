// Macaron C++ Library - RapidJson Implementation

#include "MacaronPch.h"

#include "RapidJson/JsonValueImpl.h"
#include <Macaron/RapidJson/JsonBelt.h>
#include <Macaron/RapidJson/JsonReader.h>
#include <Macaron/RapidJson/JsonErrorLocator.h>
#include <Caramel/FileSystem/FileInfo.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Memory/UniquePtrUtils.h>
#include <Caramel/String/Algorithm.h>
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
//   JsonArray
//   JsonArrayConstIterator
//   JsonBelt
//   JsonReader
//   JsonErrorLocator
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
    JsonReader reader;
    JsonValue value;

    if ( ! reader.ParseFromFile( fileName, value ))
    {
        CARAMEL_THROW( "Parse JSON file \"{0}\" failed: {1}", fileName, reader.GetErrorMessage() );
    }

    value.SetTag( fileName );
    return value;
}


JsonValue JsonValue::FromString( const std::string& text )
{
    JsonReader reader;
    JsonValue value;

    if ( ! reader.Parse( text, value ))
    {
        CARAMEL_THROW( "Parse JSON string failed: {0}", reader.GetErrorMessage() );
    }

    return value;
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

Bool JsonValue::AsBool() const
{
    CARAMEL_CHECK_MSG( this->IsBool(),
        "JsonValue \"{0}\" can't convert to Bool", m_impl->m_tag );

    return m_impl->m_value.GetBool();
}

Int JsonValue::AsInt() const
{
    CARAMEL_CHECK_MSG( this->IsInt(),
        "JsonValue \"{0}\" can't convert to Int", m_impl->m_tag );

    return m_impl->m_value.GetInt();
}

Uint JsonValue::AsUint() const
{
    CARAMEL_CHECK_MSG( this->IsUint(),
        "JsonValue \"{0}\" can't convert to Uint", m_impl->m_tag );

    return m_impl->m_value.GetUint();
}

Float JsonValue::AsFloat() const
{
    CARAMEL_CHECK_MSG( this->IsNumber(),
        "JsonValue \"{0}\" can't convert to Float", m_impl->m_tag );
    
    return static_cast< Float >( this->AsDouble() );
}

Double JsonValue::AsDouble() const
{
    CARAMEL_CHECK_MSG( this->IsNumber(),
        "JsonValue \"{0}\" can't convert to Double", m_impl->m_tag );
    
    return m_impl->m_value.GetDouble();
}

std::string JsonValue::AsString() const
{
    CARAMEL_CHECK_MSG( this->IsString(),
        "JsonValue \"{0}\" can't convert to String", m_impl->m_tag );

    return m_impl->m_value.GetString();
}

JsonArray JsonValue::AsArray() const
{
    CARAMEL_CHECK_MSG( this->IsArray(),
        "JsonValue \"{0}\" can't convert to Array", m_impl->m_tag );

    return JsonArray( m_impl );
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


JsonValue JsonValue::operator[]( const Char* name ) const
{
    return JsonValue( m_impl->GetValue( name ));
}


Bool JsonValue::GetBool( const std::string& name, Bool& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = jvalue.GetBool();
    return true;
}


Bool JsonValue::GetInt( const std::string& name, Int& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = jvalue.GetInt();
    return true;
}


Bool JsonValue::GetUint( const std::string& name, Uint& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = jvalue.GetUint();
    return true;
}


Bool JsonValue::GetFloat( const std::string& name, Float& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = static_cast< Float >( jvalue.GetDouble() );
    return true;
}


Bool JsonValue::GetDouble( const std::string& name, Double& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = jvalue.GetDouble();
    return true;
}


Bool JsonValue::GetString( const std::string& name, std::string& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    const auto& jvalue = m_impl->At( name.c_str() );

    value = jvalue.GetString();
    return true;
}


Bool JsonValue::GetValue( const std::string& name, JsonValue& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    value = JsonValue( m_impl->GetValue( name.c_str() ));
    return true;
}


Bool JsonValue::GetArray( const std::string& name, JsonArray& value ) const
{
    if ( ! m_impl->HasMember( name.c_str() )) { return false; }

    auto& jvalue = m_impl->At( name.c_str() );

    value = JsonArray( std::make_shared< JsonValueImpl >( m_impl->m_root, jvalue ));
    return true;
}


boost::optional< std::string > JsonValue::GetString( const std::string& name ) const
{
    std::string value;
    if ( this->GetString( name, value ))
    {
        return boost::optional< std::string >( value );
    }
    else
    {
        return boost::optional< std::string >();
    }
}


//
// Tag Management
//

void JsonValue::SetTag( const std::string& tag )
{
    m_impl->m_tag = tag;
}


std::string JsonValue::GetTag() const
{
    return m_impl->m_tag;
}


//
// JSON Value Implementation
//

JsonValueImpl::JsonValueImpl()
    : m_root( std::make_shared< rapidjson::Value >() )
    , m_value( *m_root )
{
}


JsonValueImpl::JsonValueImpl( std::shared_ptr< rapidjson::Value >&& root )
    : m_root( std::move( root ))
    , m_value( *m_root )
{
}


JsonValueImpl::JsonValueImpl( std::shared_ptr< rapidjson::Value > root, rapidjson::Value& value )
    : m_root( root )
    , m_value( value )
{
}


//
// Children Accessors
//

Uint JsonValueImpl::Size() const
{
    return static_cast< Uint >( m_value.Size() );
}


Bool JsonValueImpl::HasMember( const Char* name ) const
{
    return m_value.HasMember( name );
}


std::shared_ptr< JsonValueImpl > JsonValueImpl::GetValue( const Char* name ) const
{
    CARAMEL_ASSERT( m_value.IsObject() );
    return std::make_shared< JsonValueImpl >( m_root, m_value[ name ] );
}


const rapidjson::Value& JsonValueImpl::At( const Char* name ) const
{
    CARAMEL_ASSERT( name != nullptr );
    CARAMEL_ASSERT( m_value.IsObject() );
    return m_value[ name ];
}


rapidjson::Value& JsonValueImpl::At( const Char* name )
{
    CARAMEL_ASSERT( name != nullptr );
    CARAMEL_ASSERT( m_value.IsObject() );
    return m_value[ name ];
}


std::shared_ptr< JsonValueImpl > JsonValueImpl::GetValueByIndex( Uint index ) const
{
    CARAMEL_ASSERT( m_value.IsArray() );
    return std::make_shared< JsonValueImpl >( m_root, m_value[ index ] );
}


rapidjson::Value::ValueIterator JsonValueImpl::Begin() const
{
    return m_value.Begin();
}


rapidjson::Value::ValueIterator JsonValueImpl::End() const
{
    return m_value.End();
}


///////////////////////////////////////////////////////////////////////////////
//
// JSON Array
//

JsonArray::JsonArray()
{
}


JsonArray::JsonArray( std::shared_ptr< JsonValueImpl > impl )
    : JsonValue( impl )
{
    CARAMEL_ASSERT( this->IsArray() );
}


JsonArray JsonArray::FromFile( const std::string& filePath )
{
    auto value = JsonValue::FromFile( filePath );
    if ( ! value.IsArray() )
    {
        CARAMEL_THROW( "The file \"{0}\" is not a JSON array", filePath );
    }
    return value.AsArray();
}


JsonArray JsonArray::FromString( const std::string& text )
{
    auto value = JsonValue::FromString( text );
    if ( ! value.IsArray() )
    {
        CARAMEL_THROW( "The text is not a JSON array" );
    }
    return value.AsArray();
}


//
// Array Element Accessors
//

Uint JsonArray::Size() const
{
    return m_impl->Size();
}


JsonValue JsonArray::operator[]( Uint index ) const
{
    CARAMEL_ASSERT( m_impl->Size() > index );
    return JsonValue( m_impl->GetValueByIndex( index ));
}


//
// Iterator Accessors
//

JsonArrayConstIterator JsonArray::Begin() const
{
    return JsonArrayConstIterator(
        std::make_shared< JsonArrayConstIterator::Impl >( m_impl, 0 ));
}


JsonArrayConstIterator JsonArray::End() const
{
    return JsonArrayConstIterator(
        std::make_shared< JsonArrayConstIterator::Impl >( m_impl, m_impl->Size() ));
}


JsonArrayConstIterator JsonArray::begin() const { return this->Begin(); }
JsonArrayConstIterator JsonArray::end()   const { return this->End(); }


///////////////////////////////////////////////////////////////////////////////
//
// JSON Array Const Iterator
//

JsonArrayConstIterator::JsonArrayConstIterator( std::shared_ptr< Impl > impl )
    : m_impl( impl )
{
}


//
// Operators
//

JsonArrayConstIterator& JsonArrayConstIterator::operator++()
{
    ++ m_impl->m_index;
    return *this;
}


Bool JsonArrayConstIterator::operator==( const JsonArrayConstIterator& other ) const
{
    return m_impl->m_index == other.m_impl->m_index;
}


std::unique_ptr< const JsonValue > JsonArrayConstIterator::operator->() const
{
    auto value = m_impl->m_value;
    auto index = m_impl->m_index;

    CARAMEL_ASSERT( value->Size() > index );

    return MakeUnique< JsonValue >( value->GetValueByIndex( index ));
}


JsonValue JsonArrayConstIterator::operator*() const
{
    auto value = m_impl->m_value;
    auto index = m_impl->m_index;

    CARAMEL_ASSERT( value->Size() > index );

    return JsonValue( value->GetValueByIndex( index ));
}


//
// Implementation
//

JsonArrayConstIterator::Impl::Impl( std::shared_ptr< JsonValueImpl > value, Usize index )
    : m_value( value )
    , m_index( index )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// JSON Belt
//

JsonBelt::JsonBelt( const JsonArray& jarray )
    //: m_values( jarray.Begin(), jarray.End() )
{
    for ( Usize i = 0; i < jarray.Size(); ++ i )
    {
        m_values.push_back( jarray[i] );
    }
}


//
// Single Fetchers
//

Bool JsonBelt::TakeBool()
{
    CARAMEL_CHECK( ! m_values.empty() );

    const Bool value = m_values.front().AsBool();
    m_values.pop_front();
    return value;
}


Int JsonBelt::TakeInt()
{
    CARAMEL_CHECK( ! m_values.empty() );

    const Int value = m_values.front().AsInt();
    m_values.pop_front();
    return value;
}


Uint JsonBelt::TakeUint()
{
    CARAMEL_CHECK( ! m_values.empty() );

    const Uint value = m_values.front().AsUint();
    m_values.pop_front();
    return value;
}


Float JsonBelt::TakeFloat()
{
    CARAMEL_CHECK( ! m_values.empty() );

    const Float value = m_values.front().AsFloat();
    m_values.pop_front();
    return value;
}


std::string JsonBelt::TakeString()
{
    CARAMEL_CHECK( ! m_values.empty() );

    const std::string value = m_values.front().AsString();
    m_values.pop_front();
    return value;
}


///////////////////////////////////////////////////////////////////////////////
//
// JSON Reader
//

static std::string TranslateParseErrorCode( rapidjson::ParseErrorCode code );

Bool JsonReader::Parse( const std::string& text, JsonValue& value )
{
    rapidjson::StringStream stream( text.c_str() );

    auto doc = std::make_shared< rapidjson::Document >();
    doc->ParseStream( stream );

    if ( doc->HasParseError() )
    {
        auto errorCode = doc->GetParseError();
        m_errorMessage = TranslateParseErrorCode( errorCode );
        return false;
    }

    value.m_impl.reset( new JsonValueImpl( std::move( doc )));
    return true;
}


Bool JsonReader::ParseFromFile( const std::string& fileName, JsonValue& value )
{
    if ( ! FileInfo( fileName ).Exists() )
    {
        CARAMEL_THROW( "File not found: \"{0}\"", fileName );
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
        CARAMEL_THROW( "Parse JSON file \"{0}\" failed: {1}", fileName, error );
    }

    value.m_impl.reset( new JsonValueImpl( std::move( doc )));
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
// JSON Error Locator
//

JsonErrorLocator::JsonErrorLocator( const std::string& text )
{
    rapidjson::StringStream stream( text.c_str() );
    rapidjson::Reader reader;

    // This function will return when it meets an error.    
    reader.Parse( stream, *this );

    m_errorCode = reader.GetParseErrorCode();
}


bool JsonErrorLocator::Key( const Char* chs, Size len, Caramel::Bool )
{
    auto& node = m_nodeStack.back();

    CARAMEL_ASSERT( node.state == NODE_OBJECT );

    node.name = std::string( chs, len );
    node.state = NODE_VALUE;

    return true;
}


bool JsonErrorLocator::String( const Char* chs, Size len, Caramel::Bool )
{
    auto& node = m_nodeStack.back();

    switch ( node.state )
    {
    case NODE_VALUE:
        node.state = NODE_OBJECT;
        break;

    case NODE_ARRAY:
        node.arrayIndex ++;
        break;

    default:
        CARAMEL_NOT_REACHED();
    }

    return true;
}


bool JsonErrorLocator::StartObject()
{
    Node node;
    node.state = NODE_OBJECT;
    m_nodeStack.push_back( node );
    return true;
}


bool JsonErrorLocator::EndObject( Size )
{
    m_nodeStack.pop_back();
    return true;
}


bool JsonErrorLocator::StartArray()
{
    Node node;
    node.state = NODE_ARRAY;
    m_nodeStack.push_back( node );
    return true;
}


bool JsonErrorLocator::EndArray( Size )
{
    m_nodeStack.pop_back();
    return true;
}


void JsonErrorLocator::ScalarValue()
{
    // Non-string scalar value.

    auto& node = m_nodeStack.back();

    switch ( node.state )
    {
    case NODE_VALUE:
        node.state = NODE_OBJECT;
        break;

    case NODE_ARRAY:
        node.arrayIndex ++;
        break;

    default:
        CARAMEL_NOT_REACHED();
    }
}


std::string JsonErrorLocator::GetPath() const
{
    std::string path;

    for ( const Node& node : m_nodeStack )
    {
        if ( node.state == NODE_ARRAY )
        {
            path += Format( "[{0}]", node.arrayIndex );
        }
        else
        {
            if ( Contains( node.name, ' ' ))
            {
                path += Format( ".\"{0}\"", node.name );
            }
            else
            {
                path += "." + node.name;
            }
        }
    }

    return path;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron
