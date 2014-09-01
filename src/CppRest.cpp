// Macaron C++ Library - CppRest Implementation

#include "MacaronPch.h"

#define _NO_ASYNCRTIMP  // C++ REST SDK would be a static library.

#include "CppRest/HttpResponseImpl.h"
#include "CppRest/Utility.h"
#include <Macaron/CppRest/HttpRequest.h>
#include <Macaron/CppRest/HttpResponse.h>

#include <cpprest/uri.h>
#include <cpprest/http_client.h>


namespace Macaron
{

namespace CppRest
{

//
// Contents
// 
//   HttpRequest
//   HttpResponse
//

///////////////////////////////////////////////////////////////////////////////
//
// HTTP Request
//

HttpResponse HttpRequest::Get( const std::string& url )
{
    web::http::client::http_client client( ToUstr( url ));

    auto task = client.request( web::http::methods::GET, U( "" ));
    
    try
    {
        task.wait();
    }
    catch ( ... )
    {
        CARAMEL_THROW( "client.request() failed, url: %s", url );
    }

    return HttpResponse( std::make_shared< HttpResponseImpl >( task.get() ));
}


///////////////////////////////////////////////////////////////////////////////
//
// HTTP Response
//

HttpResponse::HttpResponse( std::shared_ptr< HttpResponseImpl > impl )
    : m_impl( impl )
{
}


std::string HttpResponse::AsString() const
{
    return FromUstr( m_impl->extract_string().get() );
}


//
// Implementation
//

HttpResponseImpl::HttpResponseImpl( web::http::http_response&& response )
    : web::http::http_response( std::move( response ))
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace CppRest

} // namespace Macaron
