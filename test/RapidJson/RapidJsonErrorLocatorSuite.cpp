// Macaron C++ Library Test - RapidJson Error Locator Suite

#include "MacaronTestPch.h"

#include <Macaron/RapidJson/JsonErrorLocator.h>
#include <iostream>


namespace Macaron
{

namespace RapidJson
{

SUITE( RapidJsonErrorLocatorSuite )
{

TEST( JsonErrorLocatorTest )
{
    JsonErrorLocator locate1( "{}" );

    CHECK( "" == locate1.GetPath() );

    //JsonTraversal trave2( R"( { "id" } )" );

    //CHECK( ".id" == trave2.GetPath() );

}

} // SUITE RapidJsonErrorLocatorSuite

} // namespace RapidJson

} // namespace Macaron
