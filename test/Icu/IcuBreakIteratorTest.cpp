// Macaron C++ Library Test - ICU BreakIterator Test

#include "MacaronTestPch.h"

#include <unicode/brkiter.h>


SUITE( IcuBreakIteratorSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// ICU Break Iterator Test
//

TEST( IcuWordBreakTest )
{
    UErrorCode status = U_ZERO_ERROR;

    BreakIterator* bi = BreakIterator::createWordInstance( Locale::getUS(), status );

    delete bi;
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE IcuBreakIteratorSuite
