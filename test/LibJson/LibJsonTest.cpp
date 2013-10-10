// Macaron C++ Library Test - LibJson Test

#include "MacaronTestPch.h"

#include <Macaron/LibJson/JsonValue.h>


namespace Macaron
{

namespace LibJson
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value Test
//

TEST( JsonValueTest )
{
    JsonValue jobj;
    CHECK( JSON_VALUE_OBJECT == jobj.Type() );
    CHECK( true == jobj.IsEmpty() );


    /// Load Empty Object ///

    JsonValue jtest1 = JsonValue::FromFile( "LibJson\\test1.json" );
    CHECK( JSON_VALUE_OBJECT == jtest1.Type() );
    CHECK( true == jtest1.IsEmpty() );


    /// Load Object with Simple Values ///

    JsonValue jtest2 = JsonValue::FromFile( "LibJson\\test2.json" );
    CHECK( false == jtest2.IsEmpty() );

    CHECK( 1 == jtest2.GetIntValue( "Id" ));
    CHECK( "Alice" == jtest2.GetStringValue( "Name" ));
    CHECK( true == jtest2.GetBoolValue( "CanFly" ));
    CHECK( 40.5 == jtest2.GetFloatValue( "Weight" ));

    // All values should be able as string

    CHECK( "1" == jtest2.GetStringValue( "Id" ));
    CHECK( "true" == jtest2.GetStringValue( "CanFly" ));
    CHECK( "40.5" == jtest2.GetStringValue( "Weight" ));

    // Value existance

    CHECK( true  == jtest2.HasValue( "Id" ));
    CHECK( false == jtest2.HasValue( "Code" ));

    // Converters

    CHECK( 1 == jtest2[ "Id" ].AsInt() );
    CHECK( "Alice" == jtest2[ "Name" ].AsString() );
    CHECK( true == jtest2[ "CanFly" ].AsBool() );
    CHECK( 40.5 == jtest2[ "Weight" ].AsFloat() );

    // Value Types
    
    CHECK( JSON_VALUE_NUMBER == jtest2[ "Id" ].Type() );
    CHECK( JSON_VALUE_STRING == jtest2[ "Name" ].Type() );
    CHECK( JSON_VALUE_BOOLEAN == jtest2[ "CanFly" ].Type() );
}


TEST( JsonArrayTest )
{
    JsonValue jtest3 = JsonValue::FromFile( "LibJson\\test3.json" );

    JsonValue guests = jtest3[ "Guests" ];
    CHECK( JSON_VALUE_ARRAY == guests.Type() );
    CHECK( true == guests.IsEmpty() );
    CHECK( 0 == guests.Size() );

    JsonValue users = jtest3[ "Users" ];
    CHECK( JSON_VALUE_ARRAY == users.Type() );
    CHECK( false == users.IsEmpty() );
    CHECK( 3 == users.Size() );

    CHECK( "Alice"  == users[0].AsString() );
    CHECK( "Marisa" == users[1].AsString() );
    CHECK( "Reimu"  == users[2].AsString() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace LibJosn

} // namespace Macaron
