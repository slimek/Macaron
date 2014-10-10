// Macaron C++ Library Test - RapidJson Belt Suite

#include "MacaronTestPch.h"

#include <Macaron/RapidJson/JsonBelt.h>


namespace Macaron
{

namespace RapidJson
{

SUITE( RapidJsonBeltSuite )
{

TEST( RapidJsonBeltTest )
{
    auto jarray = JsonArray::FromFile( "Data\\normal-array.json" );

    /// Single Fetchers ///

    JsonBelt jb1( jarray );

    CHECK( false == jb1.IsEmpty() );
    CHECK( jb1.Size() == jarray.Size() );

    CHECK( "position" == jb1.TakeString() );
    CHECK( 42 == jb1.TakeInt() );
    CHECK( 51 == jb1.TakeUint() );
    CHECK( "scale" == jb1.TakeString() );
    CHECK( 0.5f == jb1.TakeFloat() );
    CHECK( true == jb1.TakeBool() );

    CHECK( true == jb1.IsEmpty() );
    CHECK( 0    == jb1.Size() );

    CHECK_THROW( jb1.TakeBool(), Caramel::Exception );
}

} // SUITE RapidJsonBeltSuite

} // namespace RapidJson

} // namespace Macaron
