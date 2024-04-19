//! @file
//! @brief XML element module - header file.
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
#ifndef _XMLT_ELEMENT_HEADER
#define _XMLT_ELEMENT_HEADER
//============================================
#include "xml-interface.hpp"
#include "xml-nil.hpp"
//============================================
namespace ict { namespace  xmlt { 
//===========================================

class XmlElementStrings{
protected:
    static const std::string begin1,begin2;
    static const std::string end1,end2;
};

template <StringLiteral Tg, class Att = Nil, class Bd = Nil> class XmlElement : public XmlInterface, private XmlElementStrings {
    XmlInterface_friends
private:
    static const Literal tag;
    const Att::XmlType attributes;
    const Bd::XmlType body;
    XmlInterface_get_string_fun() {
        if (body.isEmpty()){
            Literal::append(output,begin1);
            tag.getString(output,data,prefix);
            attributes.getString(output,prefix);
            Literal::append(output,end2);
        } else {
            Literal::append(output,begin1);
            tag.getString(output,data,prefix);
            attributes.getString(output,prefix);
            Literal::append(output,end1);
            body.getString(output,prefix);
            Literal::append(output,begin2);
            tag.getString(output,data,prefix);
            Literal::append(output,end1);
        }
    }
protected:
    XmlElement(const XmlData & data_in):XmlInterface(data_in),attributes(data_in),body(data_in){}
    bool isEmpty() const {return false;}
public:
    void getParams(Literal::param_set_t & output,const Param & prefix="") const {
        tag.getParams(output,prefix);
        attributes.getParams(output,prefix);
        body.getParams(output,prefix);
    }
};
template <StringLiteral Tg, class Att, class Bd> const Literal XmlElement<Tg,Att,Bd>::tag(Tg.value);

template <StringLiteral Tg, class Att, class Bd> struct Element : public XmlData, public XmlElement<Tg,Att,Bd> {
    Element():XmlElement<Tg,Att,Bd>((const XmlData &)*this){}
    Element(const XmlData & in):XmlData(in),XmlElement<Tg,Att,Bd>((const XmlData &)*this){}
    typedef XmlElement<Tg,Att,Bd> XmlType;
};

template <StringLiteral Tg, class Att = Nil, class Bd = Nil> using E = Element<Tg,Att,Bd>;

//===========================================
} }
//============================================
#endif