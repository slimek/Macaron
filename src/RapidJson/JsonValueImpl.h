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

typedef rapidjson::Type ValueType;

class JsonValueImpl
{
    friend class JsonValue;

public:

    JsonValueImpl();    
    explicit JsonValueImpl( std::shared_ptr< rapidjson::Value >&& root );
    JsonValueImpl( std::shared_ptr< rapidjson::Value > root, rapidjson::Value& value );


    /// Properties ///

    rapidjson::Type GetType() const;


    /// Children Accessors ///

    Uint Size() const;

    Bool HasMember( const Char* name ) const;

    std::shared_ptr< JsonValueImpl > GetValue( const Char* name );

    const rapidjson::Value& At( const Char* name ) const;
    rapidjson::Value& At( const Char* name );


private:

    std::shared_ptr< rapidjson::Value > m_root;
    rapidjson::Value& m_value;

    // REMARKS: m_value depends on m_root.

    std::string m_tag;  // For debugging information,
                        // usually is the path of this value.
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_VALUE_IMPL_H
