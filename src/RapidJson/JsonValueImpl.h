// Macaron C++ Library - RapidJson - JSON Value Private Header

#ifndef __MACARON_RAPID_JSON_JSON_VALUE_IMPL_H
#define __MACARON_RAPID_JSON_JSON_VALUE_IMPL_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Macaron/RapidJson/JsonValue.h>
#include <rapidjson/document.h>


namespace Macaron
{

namespace RapidJson
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
//

class JsonValueImpl : public rapidjson::Value
{
public:

    JsonValueImpl();

private:

    
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_VALUE_IMPL_H
