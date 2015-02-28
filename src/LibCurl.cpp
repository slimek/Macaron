// Macaron C++ Library - LibCurl Implementation

#include "MacaronPch.h"
#include "LibCurl/HttpClientImpl.h"
#include "LibCurl/HttpResponseImpl.h"
#include <Caramel/String/Algorithm.h>


namespace Macaron
{

namespace LibCurl
{

//
// Contents
//
//   HttpClient
//   HttpResponse
//

///////////////////////////////////////////////////////////////////////////////
//
// HTTP Client
//

HttpClient::HttpClient( const std::string& baseUrl )
    : m_impl( new HttpClientImpl( baseUrl ))
{
}


HttpClient::~HttpClient()
{
}


HttpResponse HttpClient::Get( const std::string& pathQuery )
{
    HttpResponse response;
    m_impl->Get( pathQuery, response.m_impl.get() );
    return response;
}


//
// Implementation
//

HttpClientImpl::HttpClientImpl( const std::string& baseUrl )
    : m_baseUrl( baseUrl )
    , m_curl( curl_easy_init() )
{
    if ( ! m_curl )
    {
        CARAMEL_THROW( "Init curl failed" );
    }

    m_errorBuffer.resize( CURL_ERROR_SIZE, 0 );
    

    /// Configure Curl ///

    this->SetOption( CURLOPT_ERRORBUFFER, &m_errorBuffer[0] );
    this->SetOption( CURLOPT_TIMEOUT, 10 );
    this->SetOption( CURLOPT_CONNECTTIMEOUT, 10 );
    this->SetOption( CURLOPT_WRITEFUNCTION, &HttpClientImpl::WriteCallback );
    
    // Prevent network thread to raise a signal
    this->SetOption( CURLOPT_NOSIGNAL, 1 );

    // SSL Settings
    this->SetOption( CURLOPT_SSL_VERIFYPEER, 0 );
    this->SetOption( CURLOPT_SSL_VERIFYHOST, 0 );
}


HttpClientImpl::~HttpClientImpl()
{
    curl_easy_cleanup( m_curl );
}


void HttpClientImpl::Get( const std::string& pathQuery, HttpResponseImpl* response )
{
    this->SetOption( CURLOPT_FOLLOWLOCATION, 1 );
    this->SetOption( CURLOPT_POST, 0 );

    this->Perform( pathQuery, response );
}


void HttpClientImpl::Perform( const std::string& pathQuery, HttpResponseImpl* response )
{
    const std::string url = EndsWith( m_baseUrl, '/' )
                          ? m_baseUrl + pathQuery
                          : m_baseUrl + "/" + pathQuery;

    this->SetOption( CURLOPT_URL, url.c_str() );
    this->SetOption( CURLOPT_WRITEDATA, reinterpret_cast< Void* >( response ));

    const CURLcode code = curl_easy_perform( m_curl );

    if ( CURLE_OK != code )
    {
        CARAMEL_THROW( "Curl perform failed, code: {0}, url: \"{1}\"", code, url );
    }

    CARAMEL_VERIFY( CURLE_OK == curl_easy_getinfo(
        m_curl, CURLINFO_RESPONSE_CODE, &response->m_responseCode ));
}


std::size_t HttpClientImpl::WriteCallback(
    Void* rawData, std::size_t size, std::size_t count, Void* responsePtr )
{
    // NOTES: WriteCallback may be called multiple time in a Perform().

    const Uint totalSize = size * count;
    auto response = reinterpret_cast< HttpResponseImpl* >( responsePtr );

    const Char* data = static_cast< Char* >( rawData );

    response->m_stream.write( data, totalSize );
    response->m_writtenBytes += totalSize;

    return totalSize;
}


///////////////////////////////////////////////////////////////////////////////
//
// HTTP Response
//

HttpResponse::HttpResponse()
    : m_impl( new HttpResponseImpl )
{
}


std::string HttpResponse::ContentAsString() const
{
    return m_impl->m_stream.str();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace LibCurl

} // namespace Macaron
