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
    {
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

        // No more value
        CHECK_THROW( jb1.TakeBool(), Caramel::Exception );
    }

    /// Generic Fetchers ///
    {
        JsonBelt jb2( jarray );

        CHECK( "position" == jb2.Take< std::string >() );
        CHECK( 42 == jb2.Take< Int >() );
        CHECK( 51 == jb2.Take< Uint >() );
        CHECK( "scale" == jb2.Take< std::string >() );
        CHECK( 0.5f == jb2.Take< Float >() );
        CHECK( true == jb2.Take< Bool >() );
    }

    /// Tuple Fetchers - 1 Elements ///
    {
        JsonBelt jb3( jarray );

        std::string svalue;
        Int ivalue = 0;
        Uint uvalue = 0;

        std::tie( svalue ) = jb3.TakeTuple< std::string >();
        CHECK( "position" == svalue );

        std::tie( ivalue ) = jb3.TakeTuple< Int >();
        CHECK( 42 == ivalue );
    }

    /// Tuple Fetchers ///
    {
        JsonBelt jb4( jarray );

        std::string svalue;
        Int ivalue = 0;
        Uint uvalue = 0;

        std::tie( svalue, ivalue, uvalue ) = jb4.TakeTuple< std::string, Int, Uint >();

        CHECK( "position" == svalue );
        CHECK( 42 == ivalue );
        CHECK( 51 == uvalue );

        Float fvalue = 0.0f;
        Bool bvalue = false;

        std::tie( svalue, fvalue, bvalue ) = jb4.TakeTuple< std::string, Float, Bool >();

        CHECK( "scale" == svalue );
        CHECK( 0.5f == fvalue );
        CHECK( true == bvalue );
    }

    /// Conversion Fetchers ///
    {
        JsonBelt jb5( jarray );

        CHECK( "position" == (std::string)jb5 );
        CHECK( 42 == (Int)jb5 );
        CHECK( 51 == (Uint)jb5 );
        CHECK( "scale" == (std::string)jb5 );
        CHECK( 0.5f == (Float)jb5 );
        CHECK( true == (Bool)jb5 );
    }
}

} // SUITE RapidJsonBeltSuite

} // namespace RapidJson

} // namespace Macaron
