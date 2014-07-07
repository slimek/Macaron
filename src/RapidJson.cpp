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

    rapidjson::Document doc;
    doc.ParseStream( stream );

    auto value = std::make_shared< JsonValueImpl >();
    value->Swap( doc );

    return JsonValue( value );
}


JsonValue JsonValue::FromString( const std::string& text )
{
    rapidjson::StringStream stream( text.c_str() );

    rapidjson::Document doc;
    doc.ParseStream( stream );

    auto value = std::make_shared< JsonValueImpl >();
    value->Swap( doc );

    return JsonValue( value );
}


//
// Implementation
//

JsonValueImpl::JsonValueImpl()
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron
