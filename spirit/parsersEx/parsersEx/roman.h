#pragma once

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <string>

namespace client
{
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;

	// parse roman hundreds (100..900) numerals using the symbol table
	// data associated with each slot is the parser's attribute
	// (which is passed to attached semantic actions).
	//
	struct hundreds_ : qi::symbols<char, unsigned>
	{
		hundreds_()
		{
			add
				("C", 100)
				("CC", 200)
				("CCC", 300)
				("CD", 400)
				("D", 500)
				("DC", 600)
				("DCC", 700)
				("DCCC", 800)
				("CM", 900)
				;
		}
	} hundreds;

	// parse roman tens (10..90) numerals using symbol table
	struct tens_ : qi::symbols<char, unsigned>
	{
		tens_()
		{
			add
				("X", 10)
				("XX", 20)
				("XXX", 30)
				("XL", 40)
				("L", 50)
				("LX", 60)
				("LXX", 70)
				("LXXX", 80)
				("XC", 90)
				;
		}
	} tens;

	// parse roman ones (1..9) using symbol table
	struct ones_ : qi::symbols<char, unsigned>
	{
		ones_()
		{
			add
				("I", 1)
				("II", 2)
				("III", 3)
				("IV", 4)
				("V", 5)
				("VI", 6)
				("VII", 7)
				("VIII", 8)
				("IX", 9)
				;
		}
	} ones;

	// roman (numerals) grammar
	template <typename Iterator>
	struct roman : qi::grammar<Iterator, unsigned()>
	{
		roman() : roman::base_type(start)
		{
			using qi::eps;
			using qi::lit;
			using qi::_val;
			using qi::_1;
			using ascii::char_;

			start = eps			[_val = 0] >>
				(
					+lit('M')	[_val += 1000]
					|| hundreds	[_val += _1]
					|| tens		[_val += _1]
					|| ones		[_val += _1]
				)
			;
		}

		qi::rule<Iterator, unsigned()> start;

	};

	bool test_roman();
}