// Macaron C++ Library Test - RapidJson Test

#include "MacaronTestPch.h"

#include <Macaron/RapidJson/JsonValue.h>
#include <Caramel/Chrono/TickClock.h>


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


} // SUITE RapidJsonSuite

} // namespace RapidJson

} // namespace Macaron
