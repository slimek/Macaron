// Macaron C++ Library Test - RapidJson Test

#include "MacaronTestPch.h"

#include <Macaron/RapidJson/JsonValue.h>
#include <Macaron/JsonCpp/JsonValue.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>


using namespace std;

namespace Macaron
{

namespace RapidJson
{

SUITE( RapidJsonSuite )
{

TEST( RapidJsonFromFileTest )
{
    auto emptyObject = JsonValue::FromFile( "RapidJson\\empty-object.json" );

    CHECK( true == emptyObject.IsObject() );

    auto normalObject = JsonValue::FromFile( "RapidJson\\normal-object.json" );

    CHECK( true == normalObject.IsObject() );
}


TEST( RapidJsonFromStringTest )
{
    auto jnull = JsonValue::FromString( "null" );

    CHECK( true  == jnull.IsNull() );
    CHECK( false == jnull.IsObject() );
    CHECK( false == jnull.IsArray() );

    auto jobj = JsonValue::FromString( "{}" );

    CHECK( false == jobj.IsNull() );
    CHECK( true  == jobj.IsObject() );
    CHECK( false == jobj.IsArray() );

    auto jary = JsonValue::FromString( "[]" );

    CHECK( false == jary.IsNull() );
    CHECK( false == jary.IsObject() );
    CHECK( true  == jary.IsArray() );
}


TEST( RapidJsonGetValueTest )
{
    auto obj = JsonValue::FromFile( "RapidJson\\normal-object.json" );

    auto id = obj[ "Id" ];

    CHECK( 1 == id.AsInt() );

    Int ivalue = 0;
    CHECK( true == obj.GetIntValue( "Id", ivalue ));
    CHECK( 1 == ivalue );

    Uint uvalue = 0;
    CHECK( true == obj.GetUintValue( "Id", uvalue ));
    CHECK( 1 == uvalue );
}


TEST( RapidJsonPerformanceTest )
{
    const std::string fileName = "RapidJson\\enemy-models.json";
    TickWatch watch;

    /// From File ///

    auto fromFile = JsonValue::FromFile( fileName );

    cout << "RapidJson FromFile : " << watch.Slice() << endl;


    /// From String ///

    InputFileStream file( fileName );
    TextStreamReader reader( file );
    const std::string jsonStr = reader.ReadAll();

    cout << "(Read String) : " << watch.Slice() << endl;

    auto fromString = JsonValue::FromString( jsonStr );

    cout << "RapidJson FromString : " << watch.Slice() << endl;


    /// Compare to JsonCpp ///

    auto compare = JsonCpp::JsonValue::FromFile( fileName );

    cout << "JsonCpp : " << watch.Slice() << endl;

}

} // SUITE RapidJsonSuite

} // namespace RapidJson

} // namespace Macaron
