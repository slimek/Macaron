// Macaron C++ Library - TinyXML2 - XML Document Header

#ifndef __MACARON_TINY_XML_2_XML_DOCUMENT_H
#define __MACARON_TINY_XML_2_XML_DOCUMENT_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Macaron/TinyXml2/XmlElement.h>
#include <Caramel/String/Utf8String.h>
#include <vector>


namespace Macaron
{

namespace TinyXml2
{

///////////////////////////////////////////////////////////////////////////////
//
// XML Document
//

class XmlDocumentImpl;

class XmlDocument
{
public:

    XmlDocument();
    explicit XmlDocument( const std::string& fileName );
    explicit XmlDocument( const Utf8String&  fileName );

    void LoadFromFile( const std::string& fileName ); 
    void LoadFromFile( const Utf8String&  fileName );

    XmlElement GetRootElement() const;
    

private:

    std::shared_ptr< XmlDocumentImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace TinyXml2

} // namespace Macaron

#endif // __MACARON_TINY_XML_2_XML_DOCUMENT_H
