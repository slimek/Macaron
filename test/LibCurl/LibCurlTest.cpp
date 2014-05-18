// Macaron C++ Library Test - LibCurl Test

#include "MacaronTestPch.h"

#include <Macaron/LibCurl/HttpClient.h>
#include <iostream>


namespace Macaron
{

using namespace std;
using namespace LibCurl;

SUITE( LibCurlSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// libcurl Direct Test
//

TEST( LibCurlEasyTest )
{
    HttpClient client( "http://www.google.com" );

    HttpResponse response = client.Get( "" );

    cout << response.ContentAsString() << endl;
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE LibCurlSuite

} // namespace Macaron
