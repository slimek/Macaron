// Macaron C++ Library - TinyXML-2 Implementation

#include "MacaronPch.h"

#include "TinyXml2/XmlDocumentImpl.h"
#include "TinyXml2/XmlElementImpl.h"
#include <Caramel/Io/InputFileStream.h>
#include <tinyxml2/tinyxml2.h>
#include <stack>


namespace Macaron
{

namespace TinyXml2
{

//
// Contents
//
//   XmlDocument
//   XmlElement
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
    InputFileStream inputFile( fileName );

    m_impl->m_document.LoadFile( inputFile.GetFilePointer() );
}


XmlElement XmlDocument::GetRootElement() const
{
    return XmlElement( std::make_shared< XmlElementImpl >( m_impl->m_document.RootElement() ));
}


///////////////////////////////////////////////////////////////////////////////
//
// XML Element
//

XmlElement::XmlElement()
    : m_impl( nullptr )
{
}


XmlElement::XmlElement( std::shared_ptr< XmlElementImpl > impl )
    : m_impl( impl )
{
}


std::string XmlElement::GetName() const
{
    CARAMEL_ASSERT( m_impl );

    return std::string( m_impl->m_element->Name() );
}


std::string XmlElement::GetAttribute( const std::string& name ) const
{
    CARAMEL_ASSERT( m_impl );

    const Char* value = m_impl->m_element->Attribute( name.c_str() );
    if ( ! value )
    {
        CARAMEL_THROW( "Node \"{0}\" attribute \"{1}\" not found : ", this->GetName(), name );
    }

    return std::string( value );
}


std::vector< XmlElement > XmlElement::FindAllElements( const std::string& name ) const
{
    CARAMEL_ASSERT( m_impl );

    std::vector< XmlElement > result;
    std::stack< tinyxml2::XMLElement* > elemStack;

    tinyxml2::XMLElement* elem = m_impl->m_element;
    elemStack.push( elem );

    while ( ! elemStack.empty() )
    {
        elem = elemStack.top();
        elemStack.pop();

        if ( elem->Name() == name )
        {
            result.push_back( XmlElement( std::make_shared< XmlElementImpl >( elem )));
        }

        tinyxml2::XMLElement* child = elem->FirstChildElement();
        while ( child )
        {
            elemStack.push( child );
            child = child->NextSiblingElement();
        }
    }

    return result;
}


//
// Implementation
//

XmlElementImpl::XmlElementImpl( tinyxml2::XMLElement* element )
    : m_element( element )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace TinyXml2

} // namespace Macaron
