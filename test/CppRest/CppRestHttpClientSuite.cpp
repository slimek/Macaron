// Macaron C++ Library Test - C++ REST HTTP Client Suite

#include "MacaronTestPch.h"

#define _NO_ASYNCRTIMP
#include <cpprest/http_client.h>

#pragma comment( lib, "winhttp.lib" )


namespace Macaron
{

SUITE( CppRestHttpClientSuite )
{

TEST( HttpClientTest )
{
    web::http::client::http_client client( U( "http://www.google.com/" ));

    client.request( web::http::methods::GET, U( "" )).then(
    [=] ( web::http::http_response response )
    {
        cout << "HTTP status code: " << response.status_code() << endl;
    
    }).wait();

}


} // SUITe CppRestHttpClientSuite

} // namespace Macaron
