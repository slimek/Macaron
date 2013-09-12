// Macaron C++ Library - TinyXML2 - XML Element Header

#ifndef __MACARON_TINY_XML_2_XML_ELEMENT_H
#define __MACARON_TINY_XML_2_XML_ELEMENT_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Macaron
{

///////////////////////////////////////////////////////////////////////////////
//
// XML Element
//

class XmlElementImpl;

class XmlElement
{

private:

    std::shared_ptr< XmlElementImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Macaron

#endif // __MACARON_TINY_XML_2_XML_ELEMENT_H
