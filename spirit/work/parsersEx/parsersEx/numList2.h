/*
 * numList2.h
 *
 *  Created on: Jan 23, 2016
 *      Author: root
 */


#pragma once

// this sample demonstrates a parser from a comma separated list of numbers.
// the numbers are inserted in a vector using phoenix

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;


    // our number list compiler
    template <typename Iterator>
    bool parse_numbers2(Iterator first, Iterator last, std::vector<double>& v)
    {
    	using qi::double_;
    	using qi::phrase_parse;
    	using qi::_1;
    	using ascii::space;
    	using phoenix::push_back;

    	bool r = phrase_parse(first, last,
    	   // begin grammar
    		(
               double_[push_back(phoenix::ref(v), _1)]
                       >> *(',' >> double_[push_back(phoenix::ref(v),_1)])
    		)
    		,
    		// end grammar
    	    space);

    	if (first != last)  // fail if we did not get a full match
    		return false;
    	return r;
    }

    bool test_numList2();
}
