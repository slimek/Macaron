// Macaron C++ Library - LibCurl - HTTP Response Header

#ifndef __MACARON_LIB_CURL_HTTP_RESPONSE_H
#define __MACARON_LIB_CURL_HTTP_RESPONSE_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Caramel/Value/SharedArray.h>


namespace Macaron
{

namespace LibCurl
{

///////////////////////////////////////////////////////////////////////////////
//
// HTTP Response
//

typedef ConstSharedArray< Byte > ByteArray;

class HttpResponseImpl;

class HttpResponse
{
    friend class HttpClient;

public:

    HttpResponse();

    std::string ContentAsString()    const;
    ByteArray   ContentAsByteArray() const;

    // HTTP response code, e.g. 200 is Ok.
    Int ResponseCode() const;

private:

    std::shared_ptr< HttpResponseImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace LibCurl

} // namespace Macaron

#endif // __MACARON_LIB_CURL_HTTP_RESPONSE_H
