// Macaron C++ Library - RapidJson - JSON Traversal Header

#ifndef __MACARON_RAPID_JSON_JSON_TRAVERSAL_H
#define __MACARON_RAPID_JSON_JSON_TRAVERSAL_H
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
// JSON Traversal
// - Stop when parse failed. We can get the read path at the moment.
//

class JsonTraversal : public rapidjson::BaseReaderHandler< rapidjson::UTF8<> >
{
public:

    explicit JsonTraversal( const std::string& text );

    std::string GetPath() const;


    /// Handlers ///

    typedef rapidjson::SizeType Size;

    // Process a value
    void Default();

    // The third parameter is ignored.
    void String( const Char* chs, Size len, Caramel::Bool );

    void StartObject();
    void EndObject( Size );

    void StartArray();
    void EndArray( Size );

private:

    rapidjson::Reader m_reader;

    /// State Machine ///

    void AddName();
    void PopStack();
    
    PromptStateMachine m_machine;

    Caramel::Int m_currentIndex { 0 };
    std::string m_currentName;

    struct Node
    {
        Caramel::Bool isArrayNotObject { false };
        Caramel::Int arrayIndex { -1 };
        std::string name;
    };

    std::deque< Node > m_nodeStack;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_TRAVERSAL_H
