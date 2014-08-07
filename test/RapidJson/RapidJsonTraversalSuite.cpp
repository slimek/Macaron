// Macaron C++ Library Test - RapidJson Traversal Suite

#include "MacaronTestPch.h"

#include <Macaron/RapidJson/JsonTraversal.h>
#include <iostream>


namespace Macaron
{

namespace RapidJson
{

SUITE( RapidJsonTraversalSuite )
{

TEST( JsonTraversalTest )
{
    JsonTraversal trave1( "{}" );

    CHECK( "" == trave1.GetPath() );

    //JsonTraversal trave2( R"( { "id" } )" );

    //CHECK( ".id" == trave2.GetPath() );

}

} // SUITE RapidJsonTraversalSuite

} // namespace RapidJson

} // namespace Macaron
