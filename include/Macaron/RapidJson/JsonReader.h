// Macaron C++ Library - RapidJson - JSON Reader Header

#ifndef __MACARON_RAPID_JSON_JSON_READER_H
#define __MACARON_RAPID_JSON_JSON_READER_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Macaron/RapidJson/JsonValue.h>


namespace Macaron
{

namespace RapidJson
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Reader
//

class JsonReader
{
public:

    Bool Parse( const std::string& text, JsonValue& value );
    Bool ParseFromFile( const std::string& text, JsonValue& value );


    // If you are sure it is an array
    Bool Parse( const std::string& text, JsonArray& value );

    std::string GetErrorMessage() const { return m_errorMessage; }

private:

    std::string m_errorMessage;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_READER_H
