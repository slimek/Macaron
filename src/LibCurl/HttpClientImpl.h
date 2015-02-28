// Macaron C++ Library - LibCurl - HTTP Client Private Header

#ifndef __MACARON_LIB_CURL_HTTP_CLIENT_IMPL_H
#define __MACARON_LIB_CURL_HTTP_CLIENT_IMPL_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include "LibCurl/HttpResponseImpl.h"
#include <Macaron/LibCurl/HttpClient.h>
#include <curl/curl.h>


namespace Macaron
{

namespace LibCurl
{

///////////////////////////////////////////////////////////////////////////////
//
// HTTP Client
//

class HttpClientImpl
{
public:

    explicit HttpClientImpl( const std::string& baseUrl );
    ~HttpClientImpl();


    /// HTTP Request ///

    void Get( const std::string& pathQuery, HttpResponseImpl* response );


private:

    void Perform( const std::string& pathQuery, HttpResponseImpl* response );

    static std::size_t WriteCallback(
        Void* data, std::size_t size, std::size_t count, Void* response );


    /// Helper Function ///

    template< typename T >
    void SetOption( CURLoption option, const T& data )
    {
        CURLcode code = curl_easy_setopt( m_curl, option, data );

        if ( CURLE_OK != code )
        {
            CARAMEL_THROW( "Set curl option {0} failed, code: {1}", option, code );
        }
    }


    /// Data Members ///

    std::string m_baseUrl;

    CURL* m_curl;

    std::vector< Char > m_errorBuffer;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace LibCurl

} // namespace Macaron

#endif // __MACARON_LIB_CURL_HTTP_CLIENT_IMPL_H
