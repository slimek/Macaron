// Macaron C++ Library Test - RapidJson Value Suite

#include "MacaronTestPch.h"

#include <Macaron/RapidJson/JsonValue.h>


namespace Macaron
{

namespace RapidJson
{

SUITE( RapidJsonValueSuite )
{

TEST( RapidJsonFromFileTest )
{
    auto emptyObject = JsonValue::FromFile( "Data\\empty-object.json" );

    CHECK( true == emptyObject.IsObject() );

    auto normalObject = JsonValue::FromFile( "RapidJson\\normal-object.json" );

    CHECK( true == normalObject.IsObject() );

    auto emptyArray = JsonValue::FromFile( "Data\\empty-array.json" );

    CHECK( true == emptyArray.IsArray() );
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

    CHECK( true == json.GetInt( "zero", ivalue ));
    CHECK( 0 == ivalue );
    CHECK( true == json.GetUint( "zero", uvalue ));
    CHECK( 0 == uvalue );
    CHECK( true == json.GetFloat( "zero", fvalue ));
    CHECK( 0.0f == fvalue );
    CHECK( true == json.GetDouble( "zero", dvalue ));
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

    CHECK( true == json.GetInt( "int32Max", ivalue ));
    CHECK( 2147483647 == ivalue );
    CHECK( true == json.GetUint( "int32Max", uvalue ));
    CHECK( 2147483647 == uvalue );
    CHECK( true == json.GetFloat( "int32Max", fvalue ));
    CHECK( 2147483647 == fvalue );
    CHECK( true == json.GetDouble( "int32Max", dvalue ));
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
    CHECK( true == obj.GetInt( "Id", ivalue ));
    CHECK( 1 == ivalue );

    Uint uvalue = 0;
    CHECK( true == obj.GetUint( "Id", uvalue ));
    CHECK( 1 == uvalue );

    JsonValue jvalue;
    CHECK( true == obj.GetValue( "Id", jvalue ));
    CHECK( jvalue.IsInt() );
    CHECK( 1 == jvalue.AsInt() );

    CHECK( true == obj.GetValue( "Name", jvalue ));
    CHECK( jvalue.IsString() );
    CHECK( "Alice" == jvalue.AsString() );
}


TEST( RapidJsonArrayTest )
{
    auto ary1 = JsonArray::FromString( "[ 0, 1, 2 ]" );

    CHECK( 3 == ary1.Size() );
    CHECK( 0 == ary1[0].AsInt() );
    CHECK( 1 == ary1[1].AsUint() );
    CHECK( 2 == ary1[2].AsDouble() );

    Int sum = 0;
    auto iter1 = ary1.Begin();
    for ( ; iter1 != ary1.End(); ++ iter1 )
    {
        sum += iter1->AsInt();
    }
    CHECK( 3 == sum );

    
    /// C++11 Ranged For ///

    sum = 0;
    for ( auto jvalue : ary1 )
    {
        sum += jvalue.AsInt();
    }
    CHECK( 3 == sum );


    auto ary2 = JsonArray::FromFile( "RapidJson\\normal-array.json" );
    auto iter2 = ary2.Begin();

    CHECK( "position" == iter2.TakeString() );
    CHECK( 42 == iter2.TakeInt() );
    CHECK( 51 == iter2.TakeUint() );
    CHECK( "scale" == iter2.TakeString() );
    CHECK( 0.5f == iter2.TakeFloat() );
}


} // SUITE RapidJsonValueSuite

} // namespace RapidJson

} // namespace Macaron
