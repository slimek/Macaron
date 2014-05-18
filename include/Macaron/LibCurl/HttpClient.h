// Macaron C++ Library - LibCurl - HTTP Client Header

#ifndef __MACARON_LIB_CURL_HTTP_CLIENT_H
#define __MACARON_LIB_CURL_HTTP_CLIENT_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Macaron/LibCurl/HttpResponse.h>


namespace Macaron
{

namespace LibCurl
{

///////////////////////////////////////////////////////////////////////////////
//
// HTTP Client
//

class HttpClientImpl;

class HttpClient
{
public:

    HttpClient( const std::string& baseUrl );
    ~HttpClient();


    // HTTP Requests

    HttpResponse Get( const std::string& pathQuery );


private:
    
    std::unique_ptr< HttpClientImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace LibCurl

} // namespace Macaron

#endif // __MACARON_LIB_CURL_HTTP_CLIENT_H
