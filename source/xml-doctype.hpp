//! @file
//! @brief XML doctype module - header file.
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
#ifndef _XMLT_DOCTYPE_HEADER
#define _XMLT_DOCTYPE_HEADER
//============================================
#include "xml-interface.hpp"
//============================================
namespace ict { namespace  xmlt { 
//===========================================

class XmlDoctypeStrings{
protected:
    static const std::string begin;
    static const std::string end;
};

template <class Bd> class XmlDoctype : public XmlInterface, private XmlDoctypeStrings {
    XmlInterface_friends
private:
    static const Literal tag;
    const Bd::XmlType body;
    XmlInterface_get_string_fun() {
        Literal::append(output,begin);
        body.getString(output,prefix);
        Literal::append(output,end);
    }
protected:
    XmlDoctype(const XmlData & data_in):XmlInterface(data_in),body(data_in){}
    bool isEmpty() const {return false;}
public:
    void getParams(Literal::param_set_t & output,const Param & prefix="") const {
        body.getParams(output,prefix);
    }
};

template <class Bd> struct Doctype : public XmlData, public XmlDoctype<Bd> {
    Doctype():XmlDoctype<Bd>((const XmlData &)*this){}
    Doctype(const XmlData & in):XmlData(in),XmlDoctype<Bd>((const XmlData &)*this){}
    typedef XmlDoctype<Bd> XmlType;
};

template <class Bd> using O = Doctype<Bd>;

//===========================================
} }
//============================================
#endif