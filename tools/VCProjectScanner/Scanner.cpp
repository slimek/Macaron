// Macaron Tools - Visual C++ Project Scanner - Scanner Main Entry

#include <Macaron/TinyXml2/XmlDocument.h>
#include <Caramel/FileSystem/DirectoryInfo.h>
#include <Caramel/FileSystem/FileInfo.h>
#include <Caramel/Program/ConsoleApplication.h>
#include <Caramel/Program/ProgramOptions.h>
#include <Caramel/Trace/Trace.h>
#include <iostream>


using namespace std;
using namespace Caramel;
using namespace Macaron;

//
// Program Options
// - The filename should be a Visual C++ Project Filters file (*.vcxproj.filters)
//

static const ProgramOptionString po_fileName( "filename,f" );
static const ProgramOptionBool   po_verbose( "verbose,v" );

static const PositionalProgramOptionValues po_positional( po_fileName );

///////////////////////////////////////////////////////////////////////////////
//
// Scanner
//

class Scanner : public ConsoleApplication
{

private:

    Int Main();
};


Int Scanner::Main()
{
    ProgramOptions::ParseCommandLine();

    if ( ! po_fileName.Exists() )
    {
        CARAMEL_TRACE_INFO( "Usage : VCProjectSCanner <filename>" );

        return EXIT_FAILURE;
    }

    Path fileName = po_fileName;

    if ( ! fileName.HasExtension() )
    {
        fileName.AppendExtension( "vcxproj.filters" );
    }

    if ( ! FileInfo( fileName ).Exists() )
    {
        CARAMEL_TRACE_INFO( "File not found : %s", po_fileName );

        return EXIT_FAILURE;
    }
    
    cout << "Project File : " << fileName << endl;

    const Path projectDir = fileName.IsAbsolute()
                          ? fileName.Directory()
                          : DirectoryInfo::Current().GetPath() / fileName.Directory();

    XmlDocument xmlDoc;
    xmlDoc.LoadFromFile( fileName );

    XmlElement root = xmlDoc.GetRootElement();

    std::vector< XmlElement > sources = root.FindAllElements( "ClCompile" );

    for ( Uint i = 0; i < sources.size(); ++ i )
    {
        const Path path = sources[i].GetAttribute( "Include" );

        if ( po_verbose )
        {
            cout << "Source : " << path << endl;
        }

        if ( ! FileInfo( projectDir / path ).Exists() )
        {
            cout << "Source not found : " << path << endl;
        }
    }

    std::vector< XmlElement > headers = root.FindAllElements( "ClInclude" );

    for ( Uint i = 0; i < headers.size(); ++ i )
    {
        const Path path = headers[i].GetAttribute( "Include" );

        if ( po_verbose )
        {
            cout << "Header : " << path << endl;
        }

        if ( ! FileInfo( projectDir / path ).Exists() )
        {
            cout << "Header not found : " << path << endl;
        }
    }


    cout << "Program Complete, Press Any Key to Exit" << endl
         << endl;

    cin.get();

    return EXIT_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////
//
// Main Entry
//

int main()
{
    Scanner app;
    return app.Run();
}


///////////////////////////////////////////////////////////////////////////////
