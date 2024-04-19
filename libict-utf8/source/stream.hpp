//! @file
//! @brief UTF8 stream module - Header file.
//! @author Mariusz Ornowski (mariusz.ornowski@ict-project.pl)
//! @version 1.0
//! @date 2012-2021
//! @copyright ICT-Project Mariusz Ornowski (ict-project.pl)
/* **************************************************************
Copyright (c) 2012-2021, ICT-Project Mariusz Ornowski (ict-project.pl)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. Neither the name of the ICT-Project Mariusz Ornowski nor the names
of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**************************************************************/
#ifndef _ICT_UTF8_STREAM_HEADER
#define _ICT_UTF8_STREAM_HEADER
//============================================
#include <string>
#include <iostream>
#include <stdexcept>
#include "get.hpp"
//============================================
namespace ict { namespace utf8 {
//===========================================
//! Struktura, która przechuwuje argumenty
template<class String> struct arg_template {
    String & arg;
    const String & carg;
    static String empty;
};
template <class String> String arg_template<String>::empty;
//! 
//! @brief Zwraca strukturę z parametrami.
//! 
//! @param a Referencja do string.
//! @return Struktura z parametrami.
//! 
template<class String> inline arg_template<String> s(String & a) {
    return {a,a};
}
//! 
//! @brief Zwraca strukturę z parametrami.
//! 
//! @param a Referencja do string.
//! @return Struktura z parametrami.
//! 
template<class String> inline arg_template<String> s(const String & a) {
    return {arg_template<String>::empty,a};
}
//! 
//! @brief Operator zapisu do strumienia
//! 
//! @param os Strumień do zapisu.
//! @param s Struktura z parametrami.
//! @return Strumień do zapisu.
//! 
template<typename Char,typename Traits,class String> 
std::basic_ostream<Char,Traits> & operator<<(std::basic_ostream<Char,Traits> & os,arg_template<String> s){
    std::basic_string<Char> tmp;
    ict::utf8::get(s.carg,tmp);
    os<<tmp;
    return(os);
}
//! 
//! @brief Operator odczytu ze strumienia
//! 
//! @param os Strumień do odczytu.
//! @param s Struktura z parametrami.
//! @return Strumień do odczytu.
//! 
template<typename Char,typename Traits,class String> 
std::basic_istream<Char,Traits> & operator>>(std::basic_istream<Char,Traits> & is,arg_template<String> s){
    std::basic_string<Char> tmp;
    is>>tmp;
    ict::utf8::get(tmp,s.arg);
    if (!arg_template<String>::empty.empty()) {
        arg_template<String>::empty.clear();
        std::invalid_argument("You can't write to a const variable!");
    }
    return(is);
}
//===========================================
} }
//============================================
#endif