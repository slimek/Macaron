// Macaron C++ Library - RapidJson - JSON Error Locator Header

#ifndef __MACARON_RAPID_JSON_JSON_ERROR_LOCATOR_H
#define __MACARON_RAPID_JSON_JSON_ERROR_LOCATOR_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Caramel/Statechart/PromptStateMachine.h>
#include <rapidjson/reader.h>
#include <deque>


namespace Macaron
{

namespace RapidJson
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Error Locator
// - Stop when parse failed. We can get the read path at the moment.
//

class JsonErrorLocator
{
public:

    explicit JsonErrorLocator( const std::string& text );

    // Returns the path where the error occured.
    std::string GetPath() const;

    rapidjson::ParseErrorCode GetErrorCode() const { return m_errorCode; }


    /// Handlers ///

    typedef rapidjson::SizeType Size;

    // The third parameter is ignored.
    void String( const Char* chs, Size len, Caramel::Bool );

    void StartObject();
    void EndObject( Size );

    void StartArray();
    void EndArray( Size );

    // Scalar value handlers
    void Null() { this->ScalarValue(); }
    void Bool( bool ) { this->ScalarValue(); }
    void Int( int ) { this->ScalarValue(); }
    void Uint( unsigned ) { this->ScalarValue(); }
    void Int64( int64_t ) { this->ScalarValue(); }
    void Uint64( uint64_t ) { this->ScalarValue(); }
    void Double( double ) { this->ScalarValue(); }


private:

    rapidjson::ParseErrorCode m_errorCode { rapidjson::kParseErrorNone };

    /// State Machine ///

    void ScalarValue();
    void PopStack();
    
    PromptStateMachine m_machine;

    struct Node
    {
        Caramel::Bool isArrayNotObject { false };
        Caramel::Int arrayIndex { 0 };
        std::string name;
    };

    std::deque< Node > m_nodeStack;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_ERROR_LOCATOR_H
