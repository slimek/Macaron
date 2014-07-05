// Macaron C++ Library Test - JsonCpp Test

#include "MacaronTestPch.h"

#include <Macaron/JsonCpp/JsonValue.h>


namespace Macaron
{

namespace JsonCpp
{

SUITE( JsonCppSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value Test
//

TEST( JsonCppTest )
{
    JsonValue jobj;
    CHECK( JSON_VALUE_NULL == jobj.Type() );
    CHECK( true == jobj.IsEmpty() );


    /// Load Empty Object ///

    JsonValue jtest1 = JsonValue::FromFile( "JsonCpp\\test1.json" );
    CHECK( JSON_VALUE_OBJECT == jtest1.Type() );
    CHECK( true == jtest1.IsEmpty() );


    /// Load Object with Simple Values ///

    JsonValue jtest2 = JsonValue::FromFile( "JsonCpp\\test2.json" );
    CHECK( false == jtest2.IsEmpty() );
    CHECK( 6 == jtest2.Size() );

    // Value existance
    CHECK( true == jtest2.HasValue( "Id" ));
    CHECK( false == jtest2.HasValue( "NotExists" ));

    // Regular accessors
    CHECK( 1 == jtest2.GetIntValue( "Id" ));
    CHECK( 1 == jtest2.GetUintValue( "Id" ));
    CHECK( -1 == jtest2.GetIntValue( "Alias" ));
    CHECK( 0xFFFFFFFF == jtest2.GetUintValue( "Limit" ));
    CHECK( "Alice" == jtest2.GetStringValue( "Name" ));
    CHECK( true == jtest2.GetBoolValue( "CanFly" ));
    CHECK( 40.5 == jtest2.GetFloatValue( "Weight" ));

    // Converting
    CHECK( 1 == jtest2.GetIntValue( "CanFly" ));         // Bool => Int
    CHECK( 40 == jtest2.GetIntValue( "Weight" ));        // Double => Int
    CHECK( "true" == jtest2.GetStringValue( "CanFly" )); // Bool => String
    CHECK( "1" == jtest2.GetStringValue( "Id" ));        // Int => String
    CHECK( "-1" == jtest2.GetStringValue( "Alias" ));    // Uint => String
    CHECK( "40.5" == jtest2.GetStringValue( "Weight" )); // Double => String

    // Invalid converting
    CHECK_THROW( jtest2.GetIntValue( "Name" ), Caramel::Exception );   // Not an Int
    CHECK_THROW( jtest2.GetUintValue( "Alias" ), Caramel::Exception ); // Negative int can't be Uint
    CHECK_THROW( jtest2.GetIntValue( "Limit" ), Caramel::Exception );  // Out of Int range.

    // Querying
    {
        Int dummy = 0;
        CHECK( false == jtest2.QueryIntValue( "NotExists", dummy ));

        Uint id = 0;
        CHECK( true == jtest2.QueryUintValue( "Id", id ));
        CHECK( 1 == id );

        Int alias = 0;
        CHECK( true == jtest2.QueryIntValue( "Alias", alias ));
        CHECK( -1 == alias );

        Bool canFly = false;
        CHECK( true == jtest2.QueryBoolValue( "CanFly", canFly ));
        CHECK( true == canFly );

        Float weight = 0;
        CHECK( true == jtest2.QueryFloatValue( "Weight", weight ));
        CHECK( 40.5 == weight );

        std::string name;
        CHECK( true == jtest2.QueryStringValue( "Name", name ));
        CHECK( "Alice" == name );
    }
    

    /// Sub-Value Operator and Converters ///

    CHECK( 1 == jtest2[ "Id" ].AsInt() );
    CHECK( 1 == jtest2[ "Id" ].AsUint() );
    CHECK( -1 == jtest2[ "Alias" ].AsInt() );
    CHECK( true == jtest2[ "CanFly" ].AsBool() );
    CHECK( 40.5 == jtest2[ "Weight" ].AsFloat() );
    CHECK( "Alice" == jtest2[ "Name" ].AsString() );


    /// Value types ///

    CHECK( JSON_VALUE_INT == jtest2[ "Id" ].Type() );
    CHECK( JSON_VALUE_INT == jtest2[ "Alias" ].Type() );
    CHECK( JSON_VALUE_BOOL == jtest2[ "CanFly" ].Type() );
    CHECK( JSON_VALUE_DOUBLE == jtest2[ "Weight" ].Type() );
    CHECK( JSON_VALUE_STRING == jtest2[ "Name" ].Type() );

    // A value greater than ( MAX_UINT / 10 ) would be treated as Double.
    CHECK( JSON_VALUE_DOUBLE == jtest2[ "Limit" ].Type() );


    /// Load Object with Sub-Object ///

    JsonValue jtest3 = JsonValue::FromFile( "JsonCpp\\test3.json" );

    CHECK( "Musou" == jtest3[ "Miko" ][ "Spell" ][ "Name" ].AsString() );
    CHECK( 100 == jtest3[ "Miko" ].GetValue( "Spell" )[ "Damage" ].AsInt() );

    JsonValue marisa = jtest3[ "Magician" ];
    CHECK( false == marisa[ "CanFly" ].AsBool() );
    CHECK( 50 == marisa.GetValue( "Weapon" ).GetIntValue( "Damage" ));
}


TEST( JsonCppArrayTest )
{
    JsonValue jtest4 = JsonValue::FromFile( "JsonCpp\\test4.json" );

    JsonValue guests = jtest4[ "Guests" ];
    CHECK( JSON_VALUE_ARRAY == guests.Type() );
    CHECK( true == guests.IsEmpty() );
    CHECK( 0 == guests.Size() );

    JsonValue users = jtest4[ "Users" ];
    CHECK( JSON_VALUE_ARRAY == users.Type() );
    CHECK( false == users.IsEmpty() );
    CHECK( 3 == users.Size() );

    CHECK( "Alice"  == users[0].AsString() );
    CHECK( "Marisa" == users[1].AsString() );
    CHECK( "Reimu"  == users[2].AsString() );

    // Invalid Operations to an Array
    CHECK( false == users.IsConvertibleTo( JSON_VALUE_STRING ));
    CHECK_THROW( users[100].AsString(), Caramel::Exception );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE JsonCppSuite

} // namespace JsonCpp

} // namespace Macaron