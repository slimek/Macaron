// Macaron C++ Library - TinyXML2 - XML Document Private Header

#ifndef __MACARON_TINY_XML_2_XML_DOCUMENT_IMPL_H
#define __MACARON_TINY_XML_2_XML_DOCUMENT_IMPL_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
#include <Macaron/TinyXml2/XmlDocument.h>
#include <tinyxml2/tinyxml2.h>


namespace Macaron
{

namespace TinyXml2
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

} // namespace TinyXml2

} // namespace Macaron

#endif // __MACARON_TINY_XML_2_XML_DOCUMENT_IMPL_H
