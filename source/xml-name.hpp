//! @file
//! @brief XML name module - header file.
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
#ifndef _XMLT_NAME_HEADER
#define _XMLT_NAME_HEADER
//============================================
#include "xml-interface.hpp"
//============================================
namespace ict { namespace  xmlt { 
//===========================================

template <StringLiteral Nm, class Bd> class XmlName : public XmlInterface {
    XmlInterface_friends
private:
    static const Param name;
    const Bd::XmlType body;
    XmlInterface_get_string_fun() {
        Param p(prefix);
        p+=name;
        body.getString(output,p);
    }
protected:
    XmlName(const XmlData & data_in):XmlInterface(data_in),body(data_in){}
    bool isEmpty() const {
        return body.isEmpty();
    }
public:
    void getParams(Literal::param_set_t & output,const Param & prefix="") const {
        Param p(prefix);
        p+=name;
        body.getParams(output,p);
    }
};
template <StringLiteral Nm, class Bd> const Param XmlName<Nm,Bd>::name(Nm.value);

template <StringLiteral Nm, class Bd> struct Name : public XmlData, public XmlName<Nm,Bd> {
    Name():XmlName<Nm,Bd>((const XmlData &)*this){}
    Name(const XmlData & in):XmlData(in),XmlName<Nm,Bd>((const XmlData &)*this){}
    typedef XmlName<Nm,Bd> XmlType;
};

template <StringLiteral Nm, class Bd> using N = Name<Nm,Bd>;

//===========================================
} }
//============================================
#endif