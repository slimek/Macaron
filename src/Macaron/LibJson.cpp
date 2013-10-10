// Macaron C++ Library - LibJson Implementation

#include <Macaron/MacaronPch.h>

#include <Macaron/LibJson/JsonNode.h>
#include <Macaron/LibJson/JsonValue.h>
#include <Caramel/FileSystem/FileInfo.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>
#include <libjson/libjson.h>


namespace Macaron
{

namespace LibJson
{

//
// Contents
//
//   JsonNode
//   JsonValue
//

///////////////////////////////////////////////////////////////////////////////
//
// JSON Node
//

JsonNode::JsonNode()
{
}


JsonNode::JsonNode( const JSONNode& node )
    : JSONNode( node )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
//

JsonValue::JsonValue()
    : m_node( new JsonNode )
{
}


JsonValue::JsonValue( JsonNodePtr node )
    : m_node( node )
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
    const JSONNode node = libjson::parse( text );
    return JsonValue( std::make_shared< JsonNode >( node ));
}


//
// Properties
//

JsonValueType JsonValue::Type() const
{
    return static_cast< JsonValueType >( m_node->type() );
}


Bool JsonValue::IsEmpty() const
{
    return m_node->empty();
}


Uint JsonValue::Size() const
{
    return m_node->size();
}


//
// Converters
//

Bool JsonValue::AsBool() const
{
    return m_node->as_bool();
}


Int JsonValue::AsInt() const
{
    return m_node->as_int();
}


Float JsonValue::AsFloat() const
{
    return static_cast< Float >( m_node->as_float() );
}


std::string JsonValue::AsString() const
{
    return m_node->as_string();
}


//
// Children Accessors
//

Bool JsonValue::HasValue( const std::string& name ) const
{
    return m_node->find( name ) != m_node->end();
}


Bool JsonValue::GetBoolValue( const std::string& name ) const
{
    return m_node->at( name ).as_bool();
}


Int JsonValue::GetIntValue( const std::string& name ) const
{
    return m_node->at( name ).as_int();
}


Float JsonValue::GetFloatValue( const std::string& name ) const
{
    return static_cast< Float >( m_node->at( name ).as_float() );
}


std::string JsonValue::GetStringValue( const std::string& name ) const
{
    return m_node->at( name ).as_string();
}


JsonValue JsonValue::GetValue( const std::string& name ) const
{
    CARAMEL_ASSERT( JSON_VALUE_OBJECT == this->Type() );

    return JsonValue( std::make_shared< JsonNode >( m_node->at( name ) ));
}


JsonValue JsonValue::operator[]( const std::string& name ) const
{
    return this->GetValue( name );
}


JsonValue JsonValue::operator[]( const Char* name ) const
{
    return this->GetValue( name );
}


//
// Array Element Accessors
//

JsonValue JsonValue::GetValueAt( Uint index ) const
{
    CARAMEL_ASSERT( JSON_VALUE_ARRAY == this->Type() );

    return JsonValue( std::make_shared< JsonNode >( m_node->at( index )));
}


JsonValue JsonValue::operator[]( Uint index ) const
{
    return this->GetValueAt( index );
}


JsonValue JsonValue::operator[]( Int index ) const
{
    return this->GetValueAt( index );
}


///////////////////////////////////////////////////////////////////////////////
//
// Constants Validation
//

static_assert( JSON_NULL == JSON_VALUE_NULL, "0" );


///////////////////////////////////////////////////////////////////////////////

} // namespace LibJson

} // namespace Macaron
