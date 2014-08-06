// Macaron C++ Library - RapidJson - JSON Traversal Header

#ifndef __MACARON_RAPID_JSON_JSON_TRAVERSAL_H
#define __MACARON_RAPID_JSON_JSON_TRAVERSAL_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <rapidjson/reader.h>


namespace Macaron
{

namespace RapidJson
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Traversal
// - Stop when parse failed.
//

class JsonTraversal : public rapidjson::BaseReaderHandler< rapidjson::UTF8<> >
{
public:

    explicit JsonTraversal( const std::string& text );

private:

    typedef rapidjson::SizeType Size;

    void String( const Char* chs, Size len );

    void StartObject();
    void EndObject( Size );

    void StartArray();
    void EndArray( Size );

    rapidjson::Reader m_reader;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_TRAVERSAL_H
