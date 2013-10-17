// Macaron C++ Library - LibJson - JSON Value Private Header

#ifndef __MACARON_JSON_CPP_JSON_VALUE_IMPL_H
#define __MACARON_JSON_CPP_JSON_VALUE_IMPL_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Macaron/JsonCpp/JsonValue.h>
#include <JsonCpp/json.h>


namespace Macaron
{

namespace JsonCpp
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
//

class JsonValueImpl : public Json::Value
{
public:

    JsonValueImpl() {}
    JsonValueImpl( const Json::Value& value );

};

typedef std::shared_ptr< JsonValueImpl > JsonValuePtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace JsonCpp

} // namespace Macaron

#endif // __MACARON_JSON_CPP_JSON_VALUE_IMPL_H
