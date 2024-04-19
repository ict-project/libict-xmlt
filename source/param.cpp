//! @file
//! @brief Param module - Source file.
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
#include <regex>
#include "param.hpp"
//============================================
namespace ict { namespace  xmlt { 
//============================================
void Param::parse(const std::string & in){
    bool d=true;
    content.push_back("");
    for (const char & c : in){
        if (d){
            if (c==dot){
                dots++;
            } else {
                d=false;
            }
        } 
        if (!d) {
            if (c==dot){
                content.push_back("");
            } else {
                content.back()+=c;
            }
        }
    }
    if (!content.empty()) 
        if (content.back().empty())
            content.erase(content.end()-1);
    for (std::size_t k=0;k<content.size();k++){
        static const std::regex r1(R"regex((.+)\[(.+)\].*)regex");
        static const std::regex r2(R"regex((.+)#([0-9]+).*)regex");
        std::smatch m;
        if (std::regex_match(content.at(k),m,r1)){
            if (3<=m.size()){
                std::string i;
                try{
                    i=std::to_string(std::stol(m[2].str()));
                } catch (...){
                    i="0";
                }
                content[k]=m[1].str()+'['+i+']';
            }
        }
        if (std::regex_match(content.at(k),m,r2)){
            if (3<=m.size()){
                std::string i;
                try{
                    i=std::to_string(std::stol(m[2].str()));
                } catch (...){
                    i="0";
                }
                content[k]=m[1].str()+'#'+i;
            }
        }
    }
}
std::string Param::getString() const {
    bool first=true;
    std::string out;
    for (dots_t d=0;d<dots;d++) out+=dot;
    for (const std::string & s:content) {
        if (first){
            first=false;
        } else {
            out+=dot;    
        }
        out+=s;
    }
    return out;
}
int Param::compare(const Param & p) const{
    if (content.size()<p.content.size()) return 1;
    if (content.size()>p.content.size()) return -1;
    for (std::size_t k=0;k<content.size();k++) {
        if (content.at(k)<p.content.at(k)) return 1;
        if (content.at(k)>p.content.at(k)) return -1;
    }
    if (dots<p.dots) return 1;
    if (dots>p.dots) return -1;
    return 0;
}
Param & Param::operator += (const Param & p) {
    for (dots_t d=0;(d<p.dots)&&(!content.empty());d++) {
        content.erase(content.end()-1);
    }
    for (const std::string & s : p.content){
        content.push_back(s);
    }
    return *this;
}
Param Param::operator + (const Param & p) const {
    Param out(*this);
    out+=p;
    return out;
}
//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
static bool param_test1(const std::string & s){
    const ict::xmlt::Param p(s);
    if (s!=p.getString()){
        std::cerr<<s<<std::endl;
        return false;
    }
    return true;
}
static bool param_test2(const std::string & s1,const std::string & comp,const std::string & s2){
    const ict::xmlt::Param p1(s1);
    const ict::xmlt::Param p2(s2);
    if (comp=="=="){
        if (p1==p2) return true;
    } else if (comp=="!="){
        if (p1!=p2) return true;
    } else if (comp=="<"){
        if (p1<p2) return true;
    } else  if (comp=="<="){
        if (p1<=p2) return true;
    } else if (comp==">"){
        if (p1>p2) return true;
    } else  if (comp==">="){
        if (p1>=p2) return true;
    }
    return false;
}
static bool param_test3(const std::string & s1,const std::string & s2,const std::string & res){
    const ict::xmlt::Param p1(s1);
    const ict::xmlt::Param p2(s2);
    const ict::xmlt::Param r(res);
    if (p1+p2!=r){
        std::cerr<<s1<<"+"<<s2<<"!="<<res<<std::endl;
        return false;
    }
    return true;
}
REGISTER_TEST(param,tc1){
    return(param_test1("")?0:-1);
}
REGISTER_TEST(param,tc2){
    return(param_test1(".")?0:-1);
}
REGISTER_TEST(param,tc3){
    return(param_test1("..")?0:-1);
}
REGISTER_TEST(param,tc4){
    return(param_test1("..")?0:-1);
}
REGISTER_TEST(param,tc5){
    return(param_test1("test1.test2.test3")?0:-1);
}
REGISTER_TEST(param,tc6){
    return(param_test1("test")?0:-1);
}
REGISTER_TEST(param,tc7){
    return(param_test1(".test1.test2.test3")?0:-1);
}
REGISTER_TEST(param,tc8){
    return(param_test1(".test")?0:-1);
}
REGISTER_TEST(param,tc9){
    return(param_test1("...test1.test2.test3")?0:-1);
}
REGISTER_TEST(param,tc10){
    return(param_test1("...test")?0:-1);
}
REGISTER_TEST(param,tc11){
    return(param_test2("test[020]","==","test[20]")?0:-1);
}
REGISTER_TEST(param,tc12){
    return(param_test2(".test","==",".test")?0:-1);
}
REGISTER_TEST(param,tc13){
    return(param_test2("...test","==","...test")?0:-1);
}
REGISTER_TEST(param,tc14){
    return(param_test2("test1.test2.test3","==","test1.test2.test3")?0:-1);
}
REGISTER_TEST(param,tc15){
    return(param_test2(".test1.test2.test3","==",".test1.test2.test3")?0:-1);
}
REGISTER_TEST(param,tc16){
    return(param_test2("...test1.test2.test3","==","...test1.test2.test3")?0:-1);
}
REGISTER_TEST(param,tc17){
    return(param_test2("test1.test2.test3","<","test2.test3.test4")?0:-1);
}
REGISTER_TEST(param,tc18){
    return(param_test2(".test1.test2.test3","<",".test2.test3.test4")?0:-1);
}
REGISTER_TEST(param,tc19){
    return(param_test2("...test1.test2.test3","<","...test2.test3.test4")?0:-1);
}
REGISTER_TEST(param,tc20){
    return(param_test3("test1","test2","test1.test2")?0:-1);
}
REGISTER_TEST(param,tc21){
    return(param_test3("test1.test2.test3",".test2.test3.test4","test1.test2.test2.test3.test4")?0:-1);
}
REGISTER_TEST(param,tc22){
    return(param_test3("test1.test2.test3","..test2.test3.test4","test1.test2.test3.test4")?0:-1);
}
REGISTER_TEST(param,tc23){
    return(param_test3(".test1.test2.test3",".test2.test3.test4",".test1.test2.test2.test3.test4")?0:-1);
}
REGISTER_TEST(param,tc24){
    return(param_test3("..test1.test2.test3","..test2.test3.test4","..test1.test2.test3.test4")?0:-1);
}
#endif
//===========================================