//! @file
//! @brief Literal module - header file.
//! @author Mariusz Ornowski (mariusz.ornowski@ict-project.pl)
//! @date 2012-2024
//! @copyright ICT-Project Mariusz Ornowski (ict-project.pl)
/* **************************************************************
Copyright (c) 2012-2024, ICT-Project Mariusz Ornowski (ict-project.pl)
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
#ifndef _XMLT_LITERAL_HEADER
#define _XMLT_LITERAL_HEADER
//============================================
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <ostream>
#include "param.hpp"
//============================================
namespace ict { namespace  xmlt { 
//===========================================
class Literal{
public:
    //! Typ: Lista stringów, które składają się na literał.
    typedef std::vector<std::string> strings_t;
    //! Typ: Lista nazw parametrów, które składają się na literał.
    typedef std::vector<Param> params_t;
    //! Typ: Mapa wartości parametrów, która jest wykorzystywana do uzpełniania wartości parametrów w literale.
    typedef std::map<Param,std::string> param_map_t;
    //! Typ: Lista nazw parametrów, które występują w literale.
    typedef std::set<Param> param_set_t;
    //! Typ: Dostawca wartości parametrów, która jest wykorzystywana do uzpełniania wartości parametrów w literale.
    struct Data {
        Data(){}
        Data(const Data & in):params(in.params){}
        Data(const param_map_t & in):params(in){}
        virtual const std::string & get(const Param & p) const;
        param_map_t params;
    };
private:
    //! Lista stringów, które składają się na literał.
    strings_t strings;
    //! Lista nazw parametrów, które składają się na literał.
    params_t params;
    //! Informacja, czy w literale kodowane są XML entities.
    bool entities;
    //!
    //! @brief Wykonuje kodowanie XML entities (gdy entities_in=true) oraz parsowanie parametrów (gdy parameters_in=true) w wejściowym stringu - wersja std::string.
    //! 
    //! @param in Wejściowy string.
    //! @param strings Wynikowa lista stringów, które składają się na literał.
    //! @param params Wynikowa lista nazw parametrów, które składają się na literał.
    //! @param entities_in Informacja, czy należy wykonać kodowanie XML entities.
    //! @param parameters_in Informacja, czy należy wykonać parsowanie parametrów.
    //!
    static void prepare(const std::string & in,strings_t & strings,params_t & params,bool entities_in=true,bool parameters_in=true);
    //!
    //! @brief Wykonuje kodowanie XML entities (gdy entities_in=true) oraz parsowanie parametrów (gdy parameters_in=true) w wejściowym stringu - wersja std::wstring.
    //! 
    //! @param in Wejściowy string.
    //! @param strings Wynikowa lista stringów, które składają się na literał.
    //! @param params Wynikowa lista nazw parametrów, które składają się na literał.
    //! @param entities_in Informacja, czy należy wykonać kodowanie XML entities.
    //! @param parameters_in Informacja, czy należy wykonać parsowanie parametrów.
    //!
    static void prepare(const std::wstring & in,strings_t & strings,params_t & params,bool entities_in=true,bool parameters_in=true);
public:
    //!
    //! @brief Konstruktor: Obiekt, który tworzy literał na bazie wejściowego stringa oraz wartości parametrów - wersja std::string.
    //! 
    //! @param in Wejściowy string.
    //! @param entities_in Informacja, czy należy wykonać kodowanie XML entities.
    //!
    Literal(const std::string & in="",bool entities_in=true);
    //!
    //! @brief Konstruktor: Obiekt, który tworzy literał na bazie wejściowego stringa oraz wartości parametrów - wersja std::wstring.
    //! 
    //! @param in Wejściowy string.
    //! @param entities_in Informacja, czy należy wykonać kodowanie XML entities.
    //!
    Literal(const std::wstring & in,bool entities_in=true);
    //!
    //! @brief Udostępnia listę stringów, które składają się na literał.
    //! 
    //! @return const strings_t& Lista stringów, które składają się na literał.
    //!
    const strings_t & getStrings() const {
        return strings;
    }
    //!
    //! @brief Udostępnia listę nazw parametrów, które składają się na literał.
    //! 
    //! @return const params_t& Lista nazw parametrów, które składają się na literał.
    //!
    const params_t & getParams() const {
        return params;
    }
    //!
    //! @brief Tworzy literał na podstawie mapy wartości parametrów.
    //! 
    //! @param output Literał utworzony na podstawie mapy wartości parametrów.
    //! @param map Wejściowa mapa wartości parametrów.
    //! @param prefix Prefix nazw parametrów umieszczonych w mapie wartości.
    //!
    void getString(std::ostream & output,const Data & data={},const Param & prefix="") const;
    //!
    //! @brief Tworzy literał na podstawie mapy wartości parametrów.
    //! 
    //! @param output Literał utworzony na podstawie mapy wartości parametrów.
    //! @param map Wejściowa mapa wartości parametrów.
    //! @param prefix Prefix nazw parametrów umieszczonych w mapie wartości.
    //!
    void getString(std::string & output,const Data & data={},const Param & prefix="") const;
    //!
    //! @brief Tworzy literał na podstawie mapy wartości parametrów.
    //! 
    //! @param map Wejściowa mapa wartości parametrów.
    //! @param prefix Prefix nazw parametrów umieszczonych w mapie wartości.
    //! @return Literał utworzony na podstawie mapy wartości parametrów.
    //!
    std::string getString(const Data & data={},const Param & prefix="") const{
        std::string output;
        getString(output,data,prefix);
        return output;
    }
    //!
    //! @brief Zwraca listę nazw parametrów.
    //! 
    //! @param output Wyjściowa lista, do której dodawane są nazwy.
    //! @param prefix Prefix nazw parametrów dodawanych do listy.
    //!
    void getParams(param_set_t & output,const Param & prefix="") const;
    //!
    //! @brief Koduje XML entities - wersja std::string.
    //! 
    //! @param in Wejściowy string
    //! @return std::string Wyjściowy string.
    //!
    static std::string encodeEntities(const std::string & in);
    //!
    //! @brief Koduje XML entities - wersja std::wstring.
    //! 
    //! @param in Wejściowy string
    //! @return std::string Wyjściowy string.
    //!
    static std::wstring encodeEntities(const std::wstring & in);
    static void append(std::ostream & output,const std::string & input){output<<input;}
    static void append(std::string & output,const std::string & input){output+=input;}
};
//===========================================
} }
//============================================
#endif