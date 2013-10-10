// Macaron C++ Library Test - Run Test Main Entry

#include "MacaronTestPch.h"

#include <Caramel/Program/ConsoleApplication.h>
#include <UnitTest++/UnitTest++.h>
#include <iostream>


using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// Run Test
//

class RunTest : public ConsoleApplication
{
private:

    Int Main();
};


Int RunTest::Main()
{
    const Int result = UnitTest::RunAllTests();

    cin.get();

    return result;
}


///////////////////////////////////////////////////////////////////////////////
//
// Main Entry
//

int main()
{
    RunTest app;
    return app.Run();
}


///////////////////////////////////////////////////////////////////////////////
