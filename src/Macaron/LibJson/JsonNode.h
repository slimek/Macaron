// Macaron C++ Library - LibJson - JSON Node Header

#ifndef __MACARON_LIB_JSON_JSON_NODE_H
#define __MACARON_LIB_JSON_JSON_NODE_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <libjson/libjson.h>


namespace Macaron
{

namespace LibJson
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Node
//

class JsonNode : public JSONNode
{
public:

    JsonNode();
    explicit JsonNode( const JSONNode& node );
};

typedef std::shared_ptr< JsonNode > JsonNodePtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace LibJson

} // namespace Macaron

#endif // __MACARON_LIB_JSON_JSON_NODE_H
