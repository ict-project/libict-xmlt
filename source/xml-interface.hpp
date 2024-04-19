//! @file
//! @brief XML interface module - header file.
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
#ifndef _XMLT_INTERFACE_HEADER
#define _XMLT_INTERFACE_HEADER
//============================================
#include <string>
#include <sstream>
#include <algorithm>
#include <ostream>
#include "literal.hpp"
#include "xml-data.hpp"
//============================================
namespace ict { namespace  xmlt { 
//===========================================

template<size_t N> struct StringLiteral {
    //Source: https://ctrpeach.io/posts/cpp20-string-literal-template-parameters/
    constexpr StringLiteral(const char (&str)[N]) {
        std::copy_n(str,N,value);
    }
    char value[N];
};

class XmlInterface {
private:
    const XmlData & data;
protected:
    #define XmlInterface_get_string_fun() \
        void get_string(std::ostream & output,const XmlData & data,const Param & prefix="") const {local_get_string(output,data,prefix);} \
        void get_string(std::string & output,const XmlData & data,const Param & prefix="") const {local_get_string(output,data,prefix);} \
        template <class Type> void local_get_string(Type & output,const XmlData & data,const Param & prefix="") const 
    virtual void get_string(std::ostream & output,const XmlData & data,const Param & prefix="") const =0;
    virtual void get_string(std::string & output,const XmlData & data,const Param & prefix="") const =0;
    XmlInterface(const XmlData & data_in):data(data_in){}
    virtual bool isEmpty() const =0;
public:
    virtual void getParams(Literal::param_set_t & output,const Param & prefix="") const =0;
    void getString(std::ostream & output,const Param & prefix="") const {
        get_string(output,data,prefix);
    }
    friend std::ostream & operator << (std::ostream & stream,const XmlInterface & object) {
        object.getString(stream);
        return stream;
    }
    void getString(std::string & output,const Param & prefix="") const {
        get_string(output,data,prefix);
    }
    std::string getString(const Param & prefix="") const {
        std::string output;
        getString(output,prefix);
        return output;
    }
};

#define XmlInterface_friends \
    template <StringLiteral P1> friend class XmlText; \
    template <StringLiteral P1> friend class XmlCData; \
    template <StringLiteral P1> friend class XmlComment; \
    template <StringLiteral P1,StringLiteral P2> friend class XmlAttribute; \
    template <StringLiteral P1, class P2, class P3> friend class XmlElement; \
    template <StringLiteral P1, class P2> friend class XmlInstruction; \
    template <class P1> friend class XmlDoctype; \
    template <class P1 ,class... P2>  friend class XmlSet; \
    template <StringLiteral P1, class P2> friend class XmlArray; \
    template <StringLiteral P1,std::size_t P2,class P3,class... P4> friend class XMLPick; \
    template <StringLiteral P1, class P2> friend class XmlName;

//===========================================
} }
//============================================
#endif