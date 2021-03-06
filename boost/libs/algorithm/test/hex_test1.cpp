/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#include <boost/config.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/test/included/test_exec_monitor.hpp>

#include <string>
#include <iostream>


template<typename String>
void test_to_hex ( const typename String::value_type ** tests ) {
    for ( const typename String::value_type **p = tests; *p; p++ ) {
        String arg, argh, one, two, three, four;
        arg.assign ( *p );
        hexerboost::algorithm::hex ( *p, std::back_inserter ( one ));
        hexerboost::algorithm::hex ( arg, std::back_inserter ( two ));
        hexerboost::algorithm::hex ( arg.begin (), arg.end (), std::back_inserter ( three ));
        four = hexerboost::algorithm::hex ( arg );
        BOOST_CHECK ( one == two );
        BOOST_CHECK ( one == three );
        BOOST_CHECK ( one == four );
        argh = one;
        one.clear (); two.clear (); three.clear (); four.clear ();
        hexerboost::algorithm::unhex ( argh.c_str (), std::back_inserter ( one ));
        hexerboost::algorithm::unhex ( argh, std::back_inserter ( two ));
        hexerboost::algorithm::unhex ( argh.begin (), argh.end (), std::back_inserter ( three ));
        four = hexerboost::algorithm::unhex ( argh );
        BOOST_CHECK ( one == two );
        BOOST_CHECK ( one == three );
        BOOST_CHECK ( one == four );
        BOOST_CHECK ( one == arg );
        }
    }


template<typename String>
void test_from_hex_success ( const typename String::value_type ** tests ) {
    for ( const typename String::value_type **p = tests; *p; p++ ) {
        String arg, argh, one, two, three, four;
        arg.assign ( *p );
        hexerboost::algorithm::unhex ( *p, std::back_inserter ( one ));
        hexerboost::algorithm::unhex ( arg, std::back_inserter ( two ));
        hexerboost::algorithm::unhex ( arg.begin (), arg.end (), std::back_inserter ( three ));
        four = hexerboost::algorithm::unhex ( arg );
        BOOST_CHECK ( one == two );
        BOOST_CHECK ( one == three );
        BOOST_CHECK ( one == four );
        argh = one;
        one.clear (); two.clear (); three.clear (); four.clear ();
        hexerboost::algorithm::hex ( argh.c_str (), std::back_inserter ( one ));
        hexerboost::algorithm::hex ( argh, std::back_inserter ( two ));
        hexerboost::algorithm::hex ( argh.begin (), argh.end (), std::back_inserter ( three ));
        four = hexerboost::algorithm::hex ( argh );
        BOOST_CHECK ( one == two );
        BOOST_CHECK ( one == three );
        BOOST_CHECK ( one == four );
        BOOST_CHECK ( one == arg );
        }
    }

template<typename String>
void test_from_hex_failure ( const typename String::value_type ** tests ) {
    int num_catches;
    for ( const typename String::value_type **p = tests; *p; p++ ) {
        String arg, one;
        arg.assign ( *p );
        num_catches = 0;

        try { hexerboost::algorithm::unhex ( *p, std::back_inserter ( one )); }
        catch ( const hexerboost::algorithm::hex_decode_error & /*ex*/ ) { num_catches++; }
        try { hexerboost::algorithm::unhex ( arg, std::back_inserter ( one )); }
        catch ( const hexerboost::algorithm::hex_decode_error & /*ex*/ ) { num_catches++; }
        try { hexerboost::algorithm::unhex ( arg.begin (), arg.end (), std::back_inserter ( one )); }
        catch ( const hexerboost::algorithm::hex_decode_error & /*ex*/ ) { num_catches++; }
        BOOST_CHECK ( num_catches == 3 );
        }
    }



const char *tohex [] = {
    "",
    "a",
    "\001",
    "12",
    "asdfadsfsad",
    "01234567890ABCDEF",
    NULL        // End of the list
    };


const wchar_t *tohex_w [] = {
    L"",
    L"a",
    L"\001",
    L"12",
    L"asdfadsfsad",
    L"01234567890ABCDEF",
    NULL        // End of the list
    };


const char *fromhex [] = {
    "20",
    "2122234556FF",
    NULL        // End of the list
    };


const wchar_t *fromhex_w [] = {
    L"00101020",
    L"2122234556FF3456",
    NULL        // End of the list
    };


const char *fromhex_fail [] = {
    "2",
    "H",
    "234",
    "21222G4556FF",
    NULL        // End of the list
    };


const wchar_t *fromhex_fail_w [] = {
    L"2",
    L"12",
    L"H",
    L"234",
    L"21222G4556FF",
    NULL        // End of the list
    };


int test_main( int , char* [] )
{
  test_to_hex<std::string> ( tohex );
  test_from_hex_success<std::string> ( fromhex );
  test_from_hex_failure<std::string> ( fromhex_fail );

  test_to_hex<std::wstring> ( tohex_w );
  test_from_hex_success<std::wstring> ( fromhex_w );
  test_from_hex_failure<std::wstring> ( fromhex_fail_w );
  return 0;
}
