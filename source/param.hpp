//! @file
//! @brief Param name module - header file.
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
#ifndef _XMLT_PARAM_HEADER
#define _XMLT_PARAM_HEADER
//============================================
#include <string>
#include <vector> 
//============================================
namespace ict { namespace  xmlt { 
//===========================================
class Param{
public:
    //! Typ: Liczba kropek przed nazwą parametru.
    typedef unsigned int dots_t;
    //! Typ: Lista elementów, które składają się na nazwę parametru (rozdzielone kropkami).
    typedef std::vector<std::string> content_t;
private:
    static const char dot='.'; 
    //! Liczba kropek przed nazwą parametru.
    dots_t dots=0;
    //! Lista elementów, które składają się na nazwę parametru (rozdzielone kropkami).
    content_t content;
    //!
    //! @brief Parsuje nazwę parametru.
    //! 
    //! @param in Nazwa parametru.
    //!
    void parse(const std::string & in);
    //!
    //! @brief Porównuje dwa parametry.
    //! 
    //! @param p Parametr do porównania.
    //! @return int Zwraca:
    //!   @li -1 - gdy mniejszy;
    //!   @li 0  - gdy równa;
    //!   @li 1  - gdy większy.
    //!
    int compare(const Param & p) const;
 public:
    //!
    //! @brief Konstruktor: Tworzy parametr na podstawie jego nazwy.
    //! 
    //! @param in Wejściowy string z nazwą.
    //!
    Param(const std::string & in=""){
        parse(in);
    }
    //!
    //! @brief Konstruktor: Tworzy parametr na podstawie jego nazwy.
    //! 
    //! @param in Wejściowy string z nazwą.
    //!
    Param(const char * in){
        if (in) parse(in);
    }
    //!
    //! @brief Konstruktor: Tworzy parametr na podstawie innego parametru.
    //! 
    //! @param in Inny parametr.
    //!
    Param(const Param & in):dots(in.dots),content(in.content){
    }
    //!
    //! @brief Udostępnia liczbę kropek przed nazwą parametru.
    //! 
    //! @return const dots_t& Liczba kropek przed nazwą parametru.
    //!
    const dots_t & getDots() const {
        return dots;
    }
    //!
    //! @brief Udostępnia listę elementów, które składają się na nazwę parametru (rozdzielone kropkami).
    //! 
    //! @return const content_t& Lista elementów, które składają się na nazwę parametru (rozdzielone kropkami).
    //!
    const content_t & getContent() const {
        return content;
    }
    //!
    //! @brief Odtwarza oryginalną nazwę parametru.
    //! 
    //! @return std::string Oryginalna nazwa parametru.
    //!
    std::string getString() const;
    //!
    //! @brief Operator porównania.
    //! 
    //! @param p Parametr do porówniania.
    //!
    bool operator == (const Param & p) const{
        return 0==compare(p);
    }
    //!
    //! @brief Operator porównania.
    //! 
    //! @param p Parametr do porówniania.
    //!
    bool operator != (const Param & p) const{
        return 0!=compare(p);
    }
    //!
    //! @brief Operator porównania.
    //! 
    //! @param p Parametr do porówniania.
    //!
    bool operator < (const Param & p) const{
        return 0<compare(p);
    }
    //!
    //! @brief Operator porównania.
    //! 
    //! @param p Parametr do porówniania.
    //!
    bool operator <= (const Param & p) const{
        return 0<=compare(p);
    }
    //!
    //! @brief Operator porównania.
    //! 
    //! @param p Parametr do porówniania.
    //!
    bool operator > (const Param & p) const{
        return 0>compare(p);
    }
    //!
    //! @brief Operator porównania.
    //! 
    //! @param p Parametr do porówniania.
    //!
    bool operator >= (const Param & p) const{
        return 0>=compare(p);
    }
    //!
    //! @brief Operator dodawania do siebie nazw parametrów (są łączone kropką w nazwie) - kolejność ma znaczenie. 
    //! 
    //! @param p Nazwa parametru do dodania.
    //!
    Param & operator += (const Param & p);
    //!
    //! @brief Operator dodawania do siebie nazw parametrów (są łączone kropką w nazwie) - kolejność ma znaczenie. 
    //! 
    //! @param p Nazwa parametru do dodania.
    //!
    Param operator + (const Param & p) const;
};
//===========================================
} }
//============================================
#endif