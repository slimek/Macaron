// Macaron C++ Library - CppRest - HTTP Request Header

#ifndef __MACARON_CPP_REST_HTTP_REQUEST_H
#define __MACARON_CPP_REST_HTTP_REQUEST_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Macaron/CppRest/HttpResponse.h>


namespace Macaron
{

namespace CppRest
{

///////////////////////////////////////////////////////////////////////////////
//
// HTTP Request
//

class HttpRequest
{
public:

    HttpResponse Get( const std::string& url );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace CppRest

} // namespace Macaron

#endif // __MACARON_CPP_REST_HTTP_REQUEST_H
