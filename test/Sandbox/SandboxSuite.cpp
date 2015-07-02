// Macaron C++ Library Test - Sandbox Suite

#include "MacaronTestPch.h"

//
// Test anything as you with :)
//


namespace Macaron
{

class Widget
{
public:
    explicit Widget( std::string&& name )
    {
        this->Init( std::move( name )); 
    }

private:
    //void Init( const std::string& name )
    //{
    //    cout << "Const L-Ref" << endl;
    //}

    void Init( std::string&& name )
    {
        cout << "R-Ref" << endl;
    }
};

SUITE( Sandbox )
{

TEST( Sandbox )
{
    Widget w( "hello" );
}


} // SUITE SandboxSuite

} // namespace Macaron
