// Macaron C++ Library - CppRest - HTTP Response Header

#ifndef __MACARON_CPP_REST_HTTP_RESPONSE_H
#define __MACARON_CPP_REST_HTTP_RESPONSE_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Caramel/Value/SharedArray.h>


namespace Macaron
{

namespace CppRest
{

///////////////////////////////////////////////////////////////////////////////
//
// HTTP Response
//

class HttpResponseImpl;

class HttpResponse
{
public:

    explicit HttpResponse( std::shared_ptr< HttpResponseImpl > impl );

    std::string AsString() const;

private:

    std::shared_ptr< HttpResponseImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace CppRest

} // namespace Macaron

#endif // __MACARON_CPP_REST_HTTP_RESPONSE_H
