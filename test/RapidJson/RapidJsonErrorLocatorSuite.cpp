// Macaron C++ Library Test - RapidJson Error Locator Suite

#include "MacaronTestPch.h"

#include <Macaron/RapidJson/JsonErrorLocator.h>
#include <iostream>
#include <boost/preprocessor/cat.hpp>


namespace Macaron
{

namespace RapidJson
{

using namespace rapidjson;

SUITE( RapidJsonErrorLocatorSuite )
{

#define CHECK_JSON_EL( code, text, path ) \
    CHECK_JSON_EL_I( BOOST_PP_CAT( locator, __LINE__ ), code, text, path )

#define CHECK_JSON_EL_I( locator, code, text, path ) \
    JsonErrorLocator locator( text ); \
    CHECK( code == locator.GetErrorCode() ); \
    CHECK( path == locator.GetPath() )


TEST( JsonErrorLocatorSuccessTest )
{
    #define CHECK_NONE( text ) \
        CHECK_JSON_EL( kParseErrorNone, text, "" )

    CHECK_NONE(
        "{}"
    );

    CHECK_NONE(
        "[]"
    );

    CHECK_NONE(
        R"( { "id": 1, "name": "Alice" } )"
    );

    CHECK_NONE(
        R"( [ "Alice", "Reimu", "Marisa" ] )"
    );

    CHECK_NONE(
        R"( { "name": "Marisa", "spells": [ "Master Spark", "Stardust Reverie" ]} )"
    );

    CHECK_NONE(
        R"( { "name": "Alice", "weapon": { "name": "grimoire", "type": "book" }} )"
    );
}


TEST( JsonErrorLocatorDocumentEmptyTest )
{
    JsonErrorLocator locate( "" );
    CHECK( kParseErrorDocumentEmpty == locate.GetErrorCode() );
    CHECK( "" == locate.GetPath() );
}


TEST( JsonErrorLocatorValueInvalidTest )
{
    #define CHECK_VALUE_INVALID( text, path ) \
        CHECK_JSON_EL( kParseErrorValueInvalid, text, path )

    CHECK_VALUE_INVALID(
         R"( { "id": not-valid-value )",
         ".id"
    );

    CHECK_VALUE_INVALID(
         R"( { "id": 42, "name": not-valid-value } )",
         ".name"
    );

    CHECK_VALUE_INVALID(
         R"( { "user": { "id": not-valid-value }} )",
         ".user.id"
    );

    CHECK_VALUE_INVALID(
         R"( { "user": { "id": 42, "name": not-valid-value }} )",
         ".user.name"
    );

    CHECK_VALUE_INVALID(
        R"( { "stage": 5, "bosses": [ "reimu", not-valid-value ] } )",
        ".bosses[1]"
    );

    CHECK_VALUE_INVALID(
        R"( [ not-valid-value ] )",
        "[0]"
    );

    CHECK_VALUE_INVALID(
        R"( [ "Alice", "Marisa", not-valid-value ] )",
        "[2]"
    );

    CHECK_VALUE_INVALID(
        R"( [ "Cirno", { "type": not-valid-value } ] )",
        "[1].type"
    );
}


} // SUITE RapidJsonErrorLocatorSuite

} // namespace RapidJson

} // namespace Macaron
