// Macaron C++ Library - TinyXML-2 Implementation

#include <Macaron/TinyXml2/XmlDocumentImpl.h>
#include <tinyxml2/tinyxml2.h>


namespace Macaron
{

//
// Contents
//
//   XmlDocument
//

///////////////////////////////////////////////////////////////////////////////
//
// XML Document
//

XmlDocument::XmlDocument()
    : m_impl( new XmlDocumentImpl )
{
}


XmlDocument::XmlDocument( const std::string& fileName )
    : m_impl( new XmlDocumentImpl )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8FileName, fileName );

    this->LoadFromFile( u8FileName );
}


XmlDocument::XmlDocument( const Utf8String& fileName )
    : m_impl( new XmlDocumentImpl )
{
    this->LoadFromFile( fileName );
}


void XmlDocument::LoadFromFile( const std::string& fileName )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8FileName, fileName );

    this->LoadFromFile( u8FileName );
}


void XmlDocument::LoadFromFile( const Utf8String& fileName )
{
    m_impl->m_document.LoadFile( fileName.ToCstr() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Macaron
