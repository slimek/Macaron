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

}


///////////////////////////////////////////////////////////////////////////////

} // SUITE JsonCppSuite

} // namespace JsonCpp

} // namespace Macaron