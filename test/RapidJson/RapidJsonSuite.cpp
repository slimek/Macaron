// Macaron C++ Library Test - RapidJson Test

#include "MacaronTestPch.h"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>


using namespace std;

namespace Macaron
{

SUITE( RapidJsonSuite )
{

TEST( RapidJsonApiTest )
{
    using namespace rapidjson;

    Char buffer[1024] = { 0 };

    // Read JSON from file

    // Empty Object
    {
        Document d;
    
        FILE* file = fopen( "RapidJson\\empty-object.json", "rb" );
        FileReadStream emptyObject( file, buffer, 1024 );
        d.ParseStream( emptyObject );
        fclose( file );

        CHECK( true == d.IsObject() );
    }

    // Normal Object - with comments
    {
        Document d;

        FILE* file = fopen( "RapidJson\\normal-object.json", "rb" );
        FileReadStream normalObject( file, buffer, 1024 );
        d.ParseStream( normalObject );
        fclose( file );

        CHECK( true == d.IsObject() );
    }
}


} // SUITE RapidJsonSuite

} // namespace Macaron
