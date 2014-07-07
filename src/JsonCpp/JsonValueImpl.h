// Macaron C++ Library - JsonCpp - JSON Value Private Header

#ifndef __MACARON_JSON_CPP_JSON_VALUE_IMPL_H
#define __MACARON_JSON_CPP_JSON_VALUE_IMPL_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
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


    /// Children Accessors ///

    const Json::Value& At( const std::string& name ) const;


    /// Array Accessors ///

    const Json::Value& At( Uint index ) const;

};

typedef std::shared_ptr< JsonValueImpl > JsonValuePtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace JsonCpp

} // namespace Macaron

#endif // __MACARON_JSON_CPP_JSON_VALUE_IMPL_H
