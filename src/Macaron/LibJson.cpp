// Macaron C++ Library - LibJson Implementation

#include <Macaron/MacaronPch.h>

#include <Macaron/LibJson/JsonValueImpl.h>
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


JsonValue::JsonValue( JsonValueImpl* impl )
    : m_impl( impl )
{
}


JsonValue::~JsonValue()
{
}


JsonValue JsonValue::LoadFromFile( const std::string& fileName )
{
    return LoadFromFile( Utf8String( fileName ));
}


JsonValue JsonValue::LoadFromFile( const Utf8String& fileName )
{
    Path path( fileName );

    if ( ! path.HasExtension() )
    {
        path.AppendExtension( "json" );
    }

    InputFileStream file( path );
    TextStreamReader reader( file );

    return LoadFromString( reader.ReadAll() );
}


JsonValue JsonValue::LoadFromString( const std::string& text )
{
    const JSONNode node = libjson::parse( text );
    return JsonValue( new JsonValueImpl( node ));
}


//
// Accessors
//

Int JsonValue::AsInt() const
{
    return m_impl->m_node.as_int();
}


Float JsonValue::AsFloat() const
{
    // REMARKS: JSONNode::as_float() returns in double.
    return static_cast< Float >( m_impl->m_node.as_float() );
}


//
// Children Accessors
//

JsonValue JsonValue::operator[]( const std::string& name ) const
{
    return JsonValue( new JsonValueImpl( m_impl->m_node.at( name )));
}


//
// Implementation
//

JsonValueImpl::JsonValueImpl()
{
}


JsonValueImpl::JsonValueImpl( const JSONNode& node )
    : m_node( node )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace LibJson

} // namespace Macaron
