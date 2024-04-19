//! @file
//! @brief XML array module - header file.
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
#ifndef _XMLT_ARRAY_HEADER
#define _XMLT_ARRAY_HEADER
//============================================
#include "xml-interface.hpp"
//============================================
namespace ict { namespace  xmlt { 
//===========================================

class XmlArrayStrings{
protected:
    static const std::string open;
    static const std::string close;
    static const std::string both;
};

template <StringLiteral Nm, class Bd> class XmlArray : public XmlInterface , private XmlArrayStrings {
    XmlInterface_friends
private:
    static const Param name;
    const Bd::XmlType body;
    XmlInterface_get_string_fun() {
        Param p(prefix);
        p+=name;
        try {
            std::size_t s=std::stoll(data.get(p));
            for (std::size_t k=0;k<s;k++) {
                body.getString(output,p.getString()+open+std::to_string(k)+close);
            }
        } catch (...) {}
    }
protected:
    XmlArray(const XmlData & data_in):XmlInterface(data_in),body(data_in){}
    bool isEmpty() const {
        return body.isEmpty();
    }
public:
    void getParams(Literal::param_set_t & output,const Param & prefix="") const {
        Param p(prefix);
        p+=name;
        body.getParams(output,p.getString()+both);
        output.insert(p);
    }
};
template <StringLiteral Nm, class Bd> const Param XmlArray<Nm,Bd>::name(Nm.value);

template <StringLiteral Nm, class Bd> struct Array : public XmlData, public XmlArray<Nm,Bd> {
    Array():XmlArray<Nm,Bd>((const XmlData &)*this){}
    Array(const XmlData & in):XmlData(in),XmlArray<Nm,Bd>((const XmlData &)*this){}
    typedef XmlArray<Nm,Bd> XmlType;
};

template <StringLiteral Nm, class Bd> using Y = Array<Nm,Bd>;

//===========================================
} }
//============================================
#endif