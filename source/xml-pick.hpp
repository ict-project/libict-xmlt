//! @file
//! @brief XML pick module - header file.
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
#ifndef _XMLT_PICK_HEADER
#define _XMLT_PICK_HEADER
//============================================
#include "xml-interface.hpp"
#include "xml-nil.hpp"
//============================================
namespace ict { namespace  xmlt { 
//===========================================

class XmlPickStrings{
protected:
    static const std::string delimiter;
};

template<StringLiteral Nm,std::size_t N,class El=Nil,class... Nxt> class XMLPick;

template<StringLiteral Nm,std::size_t N> class XMLPick<Nm,N> : public XmlInterface, private XmlPickStrings {
    XmlInterface_friends
private:
    XmlInterface_get_string_fun() {}
protected:
    XMLPick(const XmlData & data_in):XmlInterface(data_in){}
    bool isEmpty() const {return true;}
public:
    void getParams(Literal::param_set_t & output,const Param & prefix="") const {
        Param p(prefix);
        Param n(Nm.value);
        p+=n;
        output.insert(p);
    }
};

template <StringLiteral Nm,std::size_t N,class El,class... Nxt> class XMLPick : public XmlInterface, private XmlPickStrings {
    XmlInterface_friends
private:
    static const Param name;
    const El::XmlType element;
    const XMLPick<Nm,N+1,Nxt...> next;
    XmlInterface_get_string_fun() {
        Param p(prefix);
        p+=name;
        std::size_t k=0;
        try {
            k=std::stoll(data.get(p));
        } catch (...) {}
        if (k==N) {
            element.getString(output,p.getString()+delimiter+std::to_string(k));
        } else {
            next.getString(output,prefix);
        }
    }
protected:
    XMLPick(const XmlData & data_in):XmlInterface(data_in),element(data_in),next(data_in){}
    bool isEmpty() const {
        if (element.isEmpty()){
            return next.isEmpty();
        }
        return false;
    }
public:
    void getParams(Literal::param_set_t & output,const Param & prefix="") const {
        Param p(prefix);
        p+=name;
        element.getParams(output,p.getString()+delimiter+std::to_string(N));
        next.getParams(output,prefix);
    }
};
template <StringLiteral Nm,std::size_t N,class El,class... Nxt> const Param XMLPick<Nm,N,El,Nxt...>::name(Nm.value);

template <StringLiteral Nm,class... Els> struct Pick : public XmlData, public XMLPick<Nm,0,Els...> {
    Pick():XMLPick<Nm,0,Els...>((const XmlData &)*this){}
    Pick(const XmlData & in):XmlData(in),XMLPick<Nm,0,Els...>((const XmlData &)*this){}
    typedef XMLPick<Nm,0,Els...> XmlType;
};

template <StringLiteral Nm,class... Els> using P = Pick<Nm,Els...>;

//===========================================
} }
//============================================
#endif