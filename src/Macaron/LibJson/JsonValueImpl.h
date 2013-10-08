// Macaron C++ Library - LibJson - JSON Value Private Header

#ifndef __MACARON_LIB_JSON_JSON_VALUE_IMPL_H
#define __MACARON_LIB_JSON_JSON_VALUE_IMPL_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Macaron/LibJson/JsonValue.h>
#include <libjson/libjson.h>


namespace Macaron
{

namespace LibJson
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
//

class JsonValueImpl
{
    friend class JsonValue;

public:

    JsonValueImpl();
    explicit JsonValueImpl( const JSONNode& node );

private:

    JSONNode m_node;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace LibJson

} // namespace Macaron

#endif // __MACARON_LIB_JSON_JSON_VALUE_IMPL_H
