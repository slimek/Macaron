// Macaron C++ Library - TinyXML2 - XML Element Private Header

#ifndef __MACARON_TINY_XML_2_XML_ELEMENT_IMPL_H
#define __MACARON_TINY_XML_2_XML_ELEMENT_IMPL_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Macaron/TinyXml2/XmlElement.h>
#include <tinyxml2/tinyxml2.h>


namespace Macaron
{

namespace TinyXml2
{

///////////////////////////////////////////////////////////////////////////////
//
// XML Element
//

class XmlElementImpl : public std::enable_shared_from_this< XmlElementImpl >
{
    friend XmlElement;

public:
    
    explicit XmlElementImpl( tinyxml2::XMLElement* element );


private:

    tinyxml2::XMLElement* m_element;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace TinyXml2

} // namespace Macaron

#endif // __MACARON_TINY_XML_2_XML_ELEMENT_IMPL_H
