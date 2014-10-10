// Macaron C++ Library - RapidJson - JSON Belt Header

#ifndef __MACARON_RAPID_JSON_JSON_BELT_H
#define __MACARON_RAPID_JSON_JSON_BELT_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Macaron/RapidJson/JsonValue.h>
#include <deque>
#include <tuple>


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


    /// Generic Fetchers ///

    template< typename T >
    T Take();

    template<> Bool  Take< Bool >()  { return this->TakeBool(); }
    template<> Int   Take< Int >()   { return this->TakeInt(); }
    template<> Uint  Take< Uint >()  { return this->TakeUint(); }
    template<> Float Take< Float >() { return this->TakeFloat(); }

    template<> std::string Take< std::string >() { return this->TakeString(); }


    /// Conversion Fetchers ///

    explicit operator Bool () { return this->TakeBool(); }
    explicit operator Int  () { return this->TakeInt(); }
    explicit operator Uint () { return this->TakeUint(); }
    explicit operator Float() { return this->TakeFloat(); }

    explicit operator std::string() { return this->TakeString(); }


    /// Tuple Fetchers ///

    template< typename T, typename... Args >
    std::tuple< T, Args... > TakeTuple();

private:
    
    template< typename T, typename... Args >
    struct TupleTaker
    {
        static std::tuple< T, Args... > Apply( JsonBelt& host );
    };

    template< typename T >
    struct TupleTaker< T >
    {
        static std::tuple< T > Apply( JsonBelt& host );
    };


    /// Members ///

    std::deque< JsonValue > m_values;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T, typename... Args >
inline std::tuple< T, Args... > JsonBelt::TakeTuple()
{
    return TupleTaker< T, Args... >::Apply( *this );
}


template< typename T, typename... Args >
inline std::tuple< T, Args... >
JsonBelt::TupleTaker< T, Args... >::Apply( JsonBelt& host )
{
    // NOTES: Make sure the first value is taken first.
    const T value = host.Take< T >();

    return std::tuple_cat(
        std::make_tuple( value ), JsonBelt::TupleTaker< Args... >::Apply( host ));
}


template< typename T >
inline std::tuple< T >
JsonBelt::TupleTaker< T >::Apply( JsonBelt& host )
{
    return std::make_tuple( host.Take< T >() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace RapidJson

} // namespace Macaron

#endif // __MACARON_RAPID_JSON_JSON_BELT_H
