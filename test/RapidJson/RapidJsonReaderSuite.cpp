// Macaron C++ Library Test - RapidJson Reader Suite

#include "MacaronTestPch.h"

#include <Macaron/RapidJson/JsonReader.h>


namespace Macaron
{

namespace RapidJson
{

SUITE( RapidJsonReaderSuite )
{

TEST( ReaderTest )
{
    JsonReader reader;
    JsonValue value;

    /// Parse Error List ///

    CHECK( false == reader.Parse( "", value ));
    CHECK( "document empty" == reader.GetErrorMessage() );

    CHECK( false == reader.Parse( "true", value ));
    CHECK( "document root not object or array" == reader.GetErrorMessage() );

    CHECK( false == reader.Parse( "{}{}", value ));
    CHECK( "document root not singular" );

    CHECK( false == reader.Parse( R"({ "name": value })", value ));
    CHECK( "value invalid" );

    CHECK( false == reader.Parse( "{ value }", value ));
    CHECK( "object miss name" );

    CHECK( false == reader.Parse( R"({ "name" value })", value ));
    CHECK( "object miss colon" );

    CHECK( false == reader.Parse( R"({ "name": value "tag": id })", value ));
    CHECK( "object miss comma or curly bracket" );

    CHECK( false == reader.Parse( R"([ "item1" "item2" ])", value ));
    CHECK( "array miss comma or square bracket" );


    /// Common Errors ///

    // A comma at the end of the last value.
    
    CHECK( false == reader.Parse( R"({ "name": value, })", value ));
    CHECK( "value invalid" );
}

} // SUITE RapidJsonReaderSuite

} // namespace RapidJson

} // namespace Macaron
