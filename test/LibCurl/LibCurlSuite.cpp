// Macaron C++ Library Test - LibCurl Test

#include "MacaronTestPch.h"

#include <Macaron/LibCurl/HttpClient.h>
#include <iostream>


namespace Macaron
{

using namespace std;
using namespace LibCurl;

SUITE( LibCurl )
{

///////////////////////////////////////////////////////////////////////////////
//
// libcurl Direct Test
//

TEST( LibCurlEasy )
{
    HttpClient client( "http://www.google.com" );

    HttpResponse response = client.Get( "" );

    cout << response.ContentAsString() << endl;
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE LibCurl

} // namespace Macaron
