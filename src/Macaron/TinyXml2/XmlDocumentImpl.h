// Macaron C++ Library - TinyXML2 - XML Document Private Header

#ifndef __MACARON_TINY_XML_2_XML_DOCUMENT_IMPL_H
#define __MACARON_TINY_XML_2_XML_DOCUMENT_IMPL_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Macaron/TinyXml2/XmlDocument.h>
#include <tinyxml2/tinyxml2.h>


namespace Macaron
{

///////////////////////////////////////////////////////////////////////////////
//
// XML Document
//

class XmlDocumentImpl
{
    friend XmlDocument;

public:

    tinyxml2::XMLDocument m_document;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Macaron

#endif // __MACARON_TINY_XML_2_XML_DOCUMENT_IMPL_H
