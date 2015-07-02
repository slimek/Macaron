// Macaron C++ Library Test - C++ REST HTTP Client Suite

#include "MacaronTestPch.h"

#include <Macaron/CppRest/HttpRequest.h>

#pragma comment( lib, "winhttp.lib" )


namespace Macaron
{

using namespace CppRest;

SUITE( CppRestHttpRequest )
{

TEST( HttpRequest )
{
    HttpRequest request;

    auto response = request.Get( "http://www.twitter.com" );

    cout << response.AsString() << endl;
}


} // SUITE CppRestHttpRequest

} // namespace Macaron
