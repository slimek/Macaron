// Macaron Tools - ASCII File Validator - Validator Entry

#include <Caramel/FileSystem/FileInfo.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Program/ConsoleApplication.h>
#include <Caramel/Program/ProgramOptions.h>
#include <Caramel/Trace/Trace.h>
#include <iostream>


using namespace std;
using namespace Caramel;

//
// Program Options
//

static const ProgramOptionString po_fileName( "filename,f" );

static const PositionalProgramOptionValues po_positional( po_fileName );

///////////////////////////////////////////////////////////////////////////////
//
// Validator
//

class Validator : public ConsoleApplication
{
private:

    Int Main() override;
};


Int Validator::Main()
{
    ProgramOptions::ParseCommandLine();

    if ( ! FileInfo( po_fileName ).Exists() )
    {
        CARAMEL_TRACE_ERROR( "File not found: %s", po_fileName );
        return EXIT_FAILURE;
    }

    CARAMEL_TRACE_INFO( "Input file : %s", po_fileName );

    InputFileStream file( po_fileName );

    Uint line = 1;
    Uint column = 0;
    Bool foundInvalid = false;

    while ( ! file.IsEof() )
    {
        // Read a byte from file
        Byte b = 0;
        file.Read( &b, 1 );
        ++ column;

        if ( 127 < b )
        {
            if ( ! foundInvalid )
            {
                foundInvalid = true;
                CARAMEL_TRACE_INFO( "< Invalid Bytes Found >" );
            }
            
            CARAMEL_TRACE_INFO( "  Line: %u, Column: %u", line, column );
        }

        if ( '\r' == b ) { continue; }

        if ( '\n' == b )
        {
            ++ line;
            column = 0;
            continue;
        }
    }

    if ( ! foundInvalid )
    {
        CARAMEL_TRACE_INFO( "< No Invalid Bytes Found >" );
    }

    CARAMEL_TRACE_INFO( "  Lines Read : %u", line );

    cin.get();

    return EXIT_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////
//
// Main Entry
//

int main()
{
    Validator app;
    return app.Run();
}


///////////////////////////////////////////////////////////////////////////////
