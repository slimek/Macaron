// Macaron C++ Library - RapidJson - JSON Belt Header

#ifndef __MACARON_RAPID_JSON_JSON_BELT_H
#define __MACARON_RAPID_JSON_JSON_BELT_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Macaron/RapidJson/JsonValue.h>
#include <deque>


namespace Macaron
{

namespace RapidJson
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Belt
// - A list of JsonValue. You may fetch them one by one.
//

class JsonBelt
{
public:
    
    explicit JsonBelt( const JsonArray& jarray );

    /// Properties ///

    Bool IsEmpty() const { return m_values.empty(); }
    Uint Size()    const { return static_cast< Uint >( m_values.size() ); }


    //
    // Single Fetchers
    // - Throws if
    //   1. The next value can't convert to the required type.
    //   2. No more value available.
    //

    Bool  TakeBool();
    Int   TakeInt();
    Uint  TakeUint();
    Float TakeFloat();

    std::string TakeString();


private:

    std::deque< JsonValue > m_values;
};


///////////////////////////////////////////////////////////////////////////////


} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_BELT_H
