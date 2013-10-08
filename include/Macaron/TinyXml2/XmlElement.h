// Macaron C++ Library - TinyXML2 - XML Element Header

#ifndef __MACARON_TINY_XML_2_XML_ELEMENT_H
#define __MACARON_TINY_XML_2_XML_ELEMENT_H

#include <Macaron/Macaron.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <vector>


namespace Macaron
{

namespace TinyXml2
{

///////////////////////////////////////////////////////////////////////////////
//
// XML Element
//

class XmlElementImpl;

class XmlElement
{
    friend class XmlDocument;
    friend class XmlElementImpl;

public:

    XmlElement();

    /// Accessors ///

    std::string GetName() const;
    
    // Throws if the attribute not found.
    std::string GetAttribute( const std::string& name ) const;


    // Recursively search all descendants
    std::vector< XmlElement > FindAllElements( const std::string& name ) const;


private:

    explicit XmlElement( std::shared_ptr< XmlElementImpl > impl );

    std::shared_ptr< XmlElementImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace TinyXml2

} // namespace Macaron

#endif // __MACARON_TINY_XML_2_XML_ELEMENT_H
