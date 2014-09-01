// Macaron C++ Library Test - C++ REST HTTP Client Suite

#include "MacaronTestPch.h"

#include <Macaron/CppRest/HttpRequest.h>

#pragma comment( lib, "winhttp.lib" )


namespace Macaron
{

using namespace CppRest;

SUITE( CppRestHttpRequestSuite )
{

TEST( HttpRequestTest )
{
    HttpRequest request;

    auto response = request.Get( "http://www.twitter.com" );

    cout << response.AsString() << endl;
}


} // SUITe CppRestHttpClientSuite

} // namespace Macaron
