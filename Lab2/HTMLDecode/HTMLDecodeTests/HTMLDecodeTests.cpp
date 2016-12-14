// HTMLDecodeTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../HTMLDecode/HTMLDecode.h"

BOOST_AUTO_TEST_SUITE(DecodeStringElementsToHtmlEntities)

BOOST_AUTO_TEST_CASE(DecodeNotEmptyString)
{
	boost::string_ref testString = "&quot;Where's my horse battle?&quot; &ap&amp;os &&apos; &gt; &amp; &lt; &lT &amp;&amp;&amp; &quot;Where sonorous horns singing?&quot;&&quot;Done rattle fierce thunderstorms.&quot;&&quot;Vanished days gone by in the darkness at sunset.&quot;";
	BOOST_CHECK_EQUAL(HTMLDecode(testString), "\"Where's my horse battle?\" &ap&os &' > & < &lT &&& \"Where sonorous horns singing?\"&\"Done rattle fierce thunderstorms.\"&\"Vanished days gone by in the darkness at sunset.\"");
};

BOOST_AUTO_TEST_CASE(DecodeEmptyString)
{
	boost::string_ref testString = "";
	BOOST_CHECK_EQUAL(HTMLDecode(testString), "");
};

BOOST_AUTO_TEST_SUITE_END()