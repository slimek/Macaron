// Macaron C++ Library - TinyXML2 - XML Element Header

#ifndef __MACARON_TINY_XML_2_XML_ELEMENT_H
#define __MACARON_TINY_XML_2_XML_ELEMENT_H
#pragma once

#include <Macaron/Setup/MacaronDefs.h>
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
