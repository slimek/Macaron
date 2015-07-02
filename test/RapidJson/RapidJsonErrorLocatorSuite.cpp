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

SUITE( RapidJsonErrorLocator )
{

#define CHECK_JSON_EL( code, text, path ) \
    CHECK_JSON_EL_I( BOOST_PP_CAT( locator, __LINE__ ), code, text, path )

#define CHECK_JSON_EL_I( locator, code, text, path ) \
    JsonErrorLocator locator( text ); \
    CHECK( code == locator.GetErrorCode() ); \
    CHECK( path == locator.GetPath() )


TEST( JsonErrorLocatorSuccess )
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


TEST( JsonErrorLocatorDocumentEmpty )
{
    JsonErrorLocator locate( "" );
    CHECK( kParseErrorDocumentEmpty == locate.GetErrorCode() );
    CHECK( "" == locate.GetPath() );
}


TEST( JsonErrorLocatorValueInvalid )
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

    // Redundant Common in Array would cause "Value Invalid" error.
    CHECK_VALUE_INVALID(
        R"( [ "Alice", "Marisa", ] )",
        "[2]"
    );
}


TEST( JsonErrorLocatorObjectMissName )
{
    #define CHECK_OBJECT_MISS_NAME( text, path ) \
        CHECK_JSON_EL( kParseErrorObjectMissName, text, path )

    CHECK_OBJECT_MISS_NAME(
        R"( { 42 })",
        "."
    );

    CHECK_OBJECT_MISS_NAME(
        R"( { "id": 42, true )",
        ".id"
    );

    CHECK_OBJECT_MISS_NAME(
        R"( { "id": 42, { "name": "Marisa" }} )",
        ".id"
    );

    // Redundant Comma in Object would cause "Object Miss Name" error.
    CHECK_OBJECT_MISS_NAME(
        R"( { "id": 42, } )",
        ".id"
    );
}


TEST( JsonErrorLocatorObjectMissColon )
{
    #define CHECK_OBJECT_MISS_COLON( text, path ) \
        CHECK_JSON_EL( kParseErrorObjectMissColon, text, path )

    CHECK_OBJECT_MISS_COLON(
        R"( { "id" 42 } )",
        ".id"
    );

    CHECK_OBJECT_MISS_COLON(
        R"( { "id": 42, "player": { "name" "Marisa" }} )",
        ".player.name"
    );
}


TEST( JsonErrorLocatorObjectMissCommaOrBrace )
{
    #define CHECK_OBJECT_MISS_COMMA_OR_BRACE( text, path ) \
        CHECK_JSON_EL( kParseErrorObjectMissCommaOrCurlyBracket, text, path )

    CHECK_OBJECT_MISS_COMMA_OR_BRACE(
        R"( { "id": 42 )",
        ".id"
    );

    CHECK_OBJECT_MISS_COMMA_OR_BRACE(
        R"( { "id": 42 "name": "Marisa" } )",
        ".id"
    );
}


TEST( JsonErrorLocatorObjectMissCommaOrBracket )
{
    #define CHECK_ARRAY_MISS_COMMA_OR_BRACKET( text, path ) \
        CHECK_JSON_EL( kParseErrorArrayMissCommaOrSquareBracket, text, path )

    CHECK_ARRAY_MISS_COMMA_OR_BRACKET(
        R"( [ "Alice" )",
        "[1]"
    );

    CHECK_ARRAY_MISS_COMMA_OR_BRACKET(
        R"( [ "Alice" "Marisa" ] )",
        "[1]"
    );
}
    
} // SUITE RapidJsonErrorLocator

} // namespace RapidJson

} // namespace Macaron
