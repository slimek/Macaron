// Macaron C++ Library - LibCurl - HTTP Response Private Header

#ifndef __MACARON_LIB_CURL_HTTP_RESPONSE_IMPL_H
#define __MACARON_LIB_CURL_HTTP_RESPONSE_IMPL_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Macaron/LibCurl/HttpResponse.h>
#include <sstream>


namespace Macaron
{

namespace LibCurl
{

///////////////////////////////////////////////////////////////////////////////
//
// HTTP Response
//

class HttpResponseImpl
{
    friend class HttpClientImpl;
    friend class HttpResponse;

public:


private:

    Int m_responseCode;
    
    std::stringstream m_stream;
    Uint m_writtenBytes;        

};


///////////////////////////////////////////////////////////////////////////////

} // namespace LibCurl

} // namespace Macaron

#endif // __MACARON_LIB_CURL_HTTP_RESPONSE_IMPL_H
