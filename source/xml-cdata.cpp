//! @file
//! @brief XML cdata module - Source file.
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
//============================================
#include "xml-cdata.hpp"
//============================================
namespace ict { namespace  xmlt { 
//============================================
const std::string XmlCDataStrings::begin("<![CDATA[");
const std::string XmlCDataStrings::end("]]>");
//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
#include "xml-all.hpp"

REGISTER_TEST(xml_cdata,tc1){
    ict::xmlt::Literal::param_set_t p;
    ict::xmlt::D<"to jest testowy tekst&"> d;
    if (d.getString("")!="<![CDATA[to jest testowy tekst&]]>") return -1;
    d.getParams(p);
    if (p.size()!=0) return -3;
    return 0;
}
REGISTER_TEST(xml_cdata,tc2){
    ict::xmlt::Literal::param_set_t p;
    ict::xmlt::D<"to $jest $testowy; tekst"> d;
    if (d.getString("")!="<![CDATA[to   tekst]]>") return -1;
    d.getParams(p);
    if (p.size()!=2) return -3;
    return 0;
}
REGISTER_TEST(xml_cdata,tc3){
    ict::xmlt::Literal::param_set_t p;
    ict::xmlt::D<"to $jest $testowy; tekst"> d;
    d.params["jest"]="1";
    d.params["testowy"]="2";
    if (d.getString("")!="<![CDATA[to 1 2 tekst]]>") return -1;
    d.getParams(p);
    if (p.size()!=2) return -3;
    return 0;
}
REGISTER_TEST(xml_cdata,tc4){
    ict::xmlt::Literal::param_set_t p;
    ict::xmlt::D<"to $jest $testowy; tekst"> d;
    d.getParams(p);
    d.loadMockData(p);
    if (d.getString("")!="<![CDATA[to $jest; $testowy; tekst]]>") return -1;
    if (p.size()!=2) return -3;
    return 0;
}
#endif
//===========================================