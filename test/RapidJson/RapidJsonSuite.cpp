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

    //CHECK( true == emptyObject.IsObject() );

    auto normalObject = JsonValue::FromFile( "RapidJson\\normal-object.json" );

    //CHECK( true == normalObject.IsObject() );
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
