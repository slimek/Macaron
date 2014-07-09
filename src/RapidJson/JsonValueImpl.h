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
public:

    JsonValueImpl();    
    explicit JsonValueImpl( std::shared_ptr< rapidjson::Document >&& doc );
    JsonValueImpl( std::shared_ptr< rapidjson::Document > doc, rapidjson::Value& value );


    /// Predicates ///

    Bool IsConvertibleToBool()   const;
    Bool IsConvertibleToFloat()  const;
    Bool IsConvertibleToString() const;


    /// Converters ///

    std::string GetString() const;


    /// Children Accessors ///

    Bool HasMember( const Char* name ) const;

    std::shared_ptr< JsonValueImpl > GetValue( const Char* name );

    const rapidjson::Value& At( const Char* name ) const;


private:

    std::shared_ptr< rapidjson::Document > m_document;
    rapidjson::Value& m_value;

    // REMARKS: m_value depends on m_document.
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_VALUE_IMPL_H
