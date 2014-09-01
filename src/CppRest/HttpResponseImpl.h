// Macaron C++ Library - CppRest - HTTP Response Private Header

#ifndef __MACARON_CPP_REST_HTTP_RESPONSE_IMPL_H
#define __MACARON_CPP_REST_HTTP_RESPONSE_IMPL_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <cpprest/http_msg.h>


namespace Macaron
{

namespace CppRest
{

///////////////////////////////////////////////////////////////////////////////
//
// HTTP Response
//

class HttpResponseImpl : public web::http::http_response
{
public:
    
    HttpResponseImpl( web::http::http_response&& response );    
};


///////////////////////////////////////////////////////////////////////////////

} // namespace CppRest

} // namespace Macaron

#endif // __MACARON_CPP_REST_HTTP_RESPONSE_IMPL_H
