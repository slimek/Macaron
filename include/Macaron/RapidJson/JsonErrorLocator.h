// Macaron C++ Library - RapidJson - JSON Error Locator Header

#ifndef __MACARON_RAPID_JSON_JSON_ERROR_LOCATOR_H
#define __MACARON_RAPID_JSON_JSON_ERROR_LOCATOR_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
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
    bool Key( const Char* chs, Size len, Caramel::Bool );
    bool String( const Char* chs, Size len, Caramel::Bool );

    bool StartObject();
    bool EndObject( Size );

    bool StartArray();
    bool EndArray( Size );

    // Scalar value handlers
    bool Null() { this->ScalarValue(); return true;}
    bool Bool( bool ) { this->ScalarValue(); return true; }
    bool Int( int ) { this->ScalarValue(); return true; }
    bool Uint( unsigned ) { this->ScalarValue(); return true; }
    bool Int64( int64_t ) { this->ScalarValue(); return true; }
    bool Uint64( uint64_t ) { this->ScalarValue(); return true; }
    bool Double( double ) { this->ScalarValue(); return true; }


private:

    void ScalarValue();

    enum NodeState
    {
        NODE_OBJECT,
        NODE_VALUE,
        NODE_ARRAY,
    };    
    
    struct Node
    {
        NodeState state { NODE_OBJECT };
        Caramel::Int arrayIndex { 0 };
        std::string name;
    };

    std::deque< Node > m_nodeStack;

    rapidjson::ParseErrorCode m_errorCode { rapidjson::kParseErrorNone };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_ERROR_LOCATOR_H
