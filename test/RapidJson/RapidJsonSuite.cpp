// Macaron C++ Library Test - RapidJson Suite

#include "MacaronTestPch.h"

#include <Macaron/RapidJson/JsonValue.h>
#include <Macaron/JsonCpp/JsonValue.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>


namespace Macaron
{

namespace RapidJson
{

SUITE( RapidJsonSuite )
{

TEST( RapidJsonFromFileTest )
{
    auto emptyObject = JsonValue::FromFile( "Data\\empty-object.json" );

    CHECK( true == emptyObject.IsObject() );

    auto normalObject = JsonValue::FromFile( "RapidJson\\normal-object.json" );

    CHECK( true == normalObject.IsObject() );

    auto emptyArray = JsonValue::FromFile( "Data\\empty-array.json" );
}


TEST( RapidJsonFromStringTest )
{
    // The root of RapidJson must be an object or an array.

    auto jobj = JsonValue::FromString( "{}" );

    CHECK( false == jobj.IsNull() );
    CHECK( true  == jobj.IsObject() );
    CHECK( false == jobj.IsArray() );

    auto jary = JsonValue::FromString( "[]" );

    CHECK( false == jary.IsNull() );
    CHECK( false == jary.IsObject() );
    CHECK( true  == jary.IsArray() );
}


TEST( RapidJsonNumberTest )
{
    const auto json = JsonValue::FromFile( "Data\\numbers.json" );

    Int ivalue = 42;
    Uint uvalue = -51;
    Float fvalue = 6.25f;
    Double dvalue = 3.1416;


    /// Zero ///

    const auto zero = json[ "zero" ];

    CHECK( true  == zero.IsNumber() );
    CHECK( true  == zero.IsInt() );
    CHECK( true  == zero.IsUint() );
    CHECK( false == zero.IsString() );
    CHECK( 0 == zero.AsInt() );
    CHECK( 0 == zero.AsUint() );
    CHECK( 0 == zero.AsFloat() );
    CHECK( 0 == zero.AsDouble() );
    CHECK( "0" == zero.ToString() );

    CHECK( true == json.GetIntValue( "zero", ivalue ));
    CHECK( 0 == ivalue );
    CHECK( true == json.GetUintValue( "zero", uvalue ));
    CHECK( 0 == uvalue );
    CHECK( true == json.GetFloatValue( "zero", fvalue ));
    CHECK( 0.0f == fvalue );
    CHECK( true == json.GetDoubleValue( "zero", dvalue ));
    CHECK( 0.0 == dvalue );


    /// Int32 Max ///

    const auto int32Max = json[ "int32Max" ];

    CHECK( true  == int32Max.IsNumber() );
    CHECK( true  == int32Max.IsInt() );
    CHECK( true  == int32Max.IsUint() );
    CHECK( INT32_MAX == int32Max.AsInt() );
    CHECK( INT32_MAX == int32Max.AsUint() );
    CHECK( INT32_MAX == int32Max.AsFloat() );
    CHECK( INT32_MAX == int32Max.AsDouble() );
    CHECK( "2147483647" == int32Max.ToString() );

    CHECK( true == json.GetIntValue( "int32Max", ivalue ));
    CHECK( 2147483647 == ivalue );
    CHECK( true == json.GetUintValue( "int32Max", uvalue ));
    CHECK( 2147483647 == uvalue );
    CHECK( true == json.GetFloatValue( "int32Max", fvalue ));
    CHECK( 2147483647 == fvalue );
    CHECK( true == json.GetDoubleValue( "int32Max", dvalue ));
    CHECK( 2147483647 == dvalue );


    /// Int32 Min ///

    const auto int32Min = json[ "int32Min" ];

    CHECK( true  == int32Min.IsNumber() );
    CHECK( true  == int32Min.IsInt() );
    CHECK( false == int32Min.IsUint() );
    CHECK( INT32_MIN == int32Min.AsInt() );
    CHECK_THROW( int32Min.AsUint(), Caramel::Exception );
    CHECK( INT32_MIN == int32Min.AsFloat() );
    CHECK( INT32_MIN == int32Min.AsDouble() );
    CHECK( "-2147483648" == int32Min.ToString() );


    /// Uint32 Max ///

    const auto uint32Max = json[ "uint32Max" ];

    CHECK( true  == uint32Max.IsNumber() );
    CHECK( false == uint32Max.IsInt() );
    CHECK( true  == uint32Max.IsUint() );
    CHECK( UINT32_MAX == uint32Max.AsUint() );
    CHECK_THROW( uint32Max.AsInt(), Caramel::Exception );
    CHECK( UINT32_MAX == uint32Max.AsFloat() );
    CHECK( UINT32_MAX == uint32Max.AsDouble() );
    CHECK( "4294967295" == uint32Max.ToString() );


    /// Floating ///

    const auto half = json[ "half" ];

    CHECK( true  == half.IsNumber() );
    CHECK( false == half.IsInt() );
    CHECK( false == half.IsUint() );
    CHECK_THROW( half.AsInt(), Caramel::Exception );
    CHECK_THROW( half.AsUint(), Caramel::Exception );
    CHECK( 0.5f == half.AsFloat() );
    CHECK( 0.5  == half.AsDouble() );
    CHECK( "0.5" == half.ToString() );
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
