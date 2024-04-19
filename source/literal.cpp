//! @file
//! @brief Literal module - Source file.
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
#include "literal.hpp"
#include "../libict-utf8/source/robot.hpp"
#include "../libict-utf8/source/get.hpp"
//============================================
namespace ict { namespace  xmlt { 
//============================================
static inline bool is_entity_name_char(const wchar_t & c){
    switch (c){
        case L'#':
        case L':':
        case L'_':
            return true;
        default:break;
    }
    return std::iswalnum(c);
}
static inline bool is_param_name_char(const wchar_t & c){
    switch (c){
        case L'.':
        case L'#':
        case L'[':
        case L']':
        case L'_':
            return true;
        default:break;
    }
    return std::iswalnum(c);
}
static void prepare_one_step(std::wstring & tmp,Literal::strings_t & strings,Literal::params_t & params,bool entities,bool parameters_in){
    static const std::string amp("&amp;");
    static const std::string lt("&lt;");
    static const std::string gt("&gt;");
    static const std::string apos("&apos;");
    static const std::string quot("&quot;");
    if (parameters_in&&(tmp.front()==L'$')){
        if (1<tmp.size()){
            if (tmp.back()==L'$') {// "$...$"
                if (tmp.size()==2){// "$$" dolar sign
                    strings.back()+='$';
                    tmp.clear();
                } else { // "$nnn$" = param name
                    params.push_back(ict::utf8::get(tmp.substr(1,tmp.size()-2)));
                    strings.push_back("");
                    tmp.erase(0,tmp.size()-1);
                    prepare_one_step(tmp,strings,params,entities,parameters_in);
                }
            } else if (tmp.back()==L';') {// "$...;"
                if (tmp.size()==2){// "$;" = empty name
                    strings.back()+=ict::utf8::get(tmp);
                } else { // "$nnn;" = param name
                    params.push_back(ict::utf8::get(tmp.substr(1,tmp.size()-2)));
                    strings.push_back("");
                }
                tmp.clear();
            } else if (!is_param_name_char(tmp.back())){// "$... "
                if (tmp.size()==2){// "$ " = empty name
                    strings.back()+='$';
                    tmp.erase(0,1);
                    prepare_one_step(tmp,strings,params,entities,parameters_in);
                } else { // "$nnn " = param name
                    params.push_back(ict::utf8::get(tmp.substr(1,tmp.size()-2)));
                    strings.push_back("");
                    tmp.erase(0,tmp.size()-1);
                    prepare_one_step(tmp,strings,params,entities,parameters_in);
                }
            } else if (1000<tmp.size()) { // too big
                strings.back()+=ict::utf8::get(tmp);
                tmp.clear();
            }
        }
    } else if (entities&&(tmp.front()==L'&')){
        if (1<tmp.size()){
            if (tmp.back()==L';') {// "&...;"
                if (tmp.size()==2){// "&;" = empty entity
                    strings.back()+=amp;
                    strings.back()+=';';
                } else {// "&nnn;" = entity
                    strings.back()+=ict::utf8::get(tmp);
                }
                tmp.clear();
            } else if (!is_entity_name_char(tmp.back())){// "&... " = not a entity
                strings.back()+=amp;
                strings.back()+=ict::utf8::get(tmp.substr(1,tmp.size()-2));
                tmp.erase(0,tmp.size()-1);
                prepare_one_step(tmp,strings,params,entities,parameters_in);
            } else if (1000<tmp.size()) { // too big
                strings.back()+=amp;
                strings.back()+=ict::utf8::get(tmp.substr(1,tmp.size()-1));
                tmp.clear();
            }
        }
    } else {
        if (entities){ 
            switch (tmp.front()){
                case L'<':{
                    strings.back()+=lt;
                } break;
                case L'>':{
                    strings.back()+=gt;
                } break;
                case L'\'':{
                    strings.back()+=apos;
                } break;
                case L'"':{
                    strings.back()+=quot;
                } break;
                default:if (tmp.front()){
                    std::wstring w;
                    w+=tmp.front();
                    strings.back()+=ict::utf8::get(w);
                } break;
            }
        } else if (tmp.front()) {
            std::wstring w;
            w+=tmp.front();
            strings.back()+=ict::utf8::get(w);
        }
        tmp.erase(0,1);
    }
}
Literal::Literal(const std::string & in,bool entities_in):entities(entities_in){
    prepare(in,strings,params,entities);
}
Literal::Literal(const std::wstring & in,bool entities_in):entities(entities_in){
    prepare(in,strings,params,entities);
}
template <class Type> static inline void local_get_string(Type & output,const Literal::Data & data,const Param & prefix,const Literal::strings_t & strings,const Literal::params_t & params,bool entities) {
    for (std::size_t k=0;k<strings.size();k++){
        Literal::append(output,strings.at(k));
        if (k<params.size()){
            Param tmp(prefix);
            tmp+=params.at(k);
             if (entities){
                Literal::append(output,Literal::encodeEntities(data.get(tmp)));
            } else {
                Literal::append(output,data.get(tmp));
            }
        }
    }
}
void Literal::getString(std::ostream & output,const Data & data,const Param & prefix) const {
    local_get_string(output,data,prefix,strings,params,entities);
}
void Literal::getString(std::string & output,const Data & data,const Param & prefix) const {
    local_get_string(output,data,prefix,strings,params,entities);
}
void Literal::getParams(param_set_t & output,const Param & prefix) const {
    for (const Param & p : params){
        Param tmp(prefix);
        tmp+=p;
        output.insert(tmp);
    }
}
void Literal::prepare(const std::string & in,strings_t & strings,params_t & params,bool entities,bool parameters){
    ict::utf8::robot r;
    std::wstring tmp;
    strings.push_back("");
    for (const char & c : in){//Read char by char
        if (r(c).isReady()){//When robot is ready (has enough data)
            tmp+=r.getChar();
            prepare_one_step(tmp,strings,params,entities,parameters);
        }
    }
    if (!tmp.empty()) {
        tmp+=L'\0';
        prepare_one_step(tmp,strings,params,entities,parameters);
    }
}
void Literal::prepare(const std::wstring & in,strings_t & strings,params_t & params,bool entities,bool parameters){
    std::wstring tmp;
    strings.push_back("");
    for (const wchar_t & c : in){//Read char by char
        tmp+=c;
        prepare_one_step(tmp,strings,params,entities,parameters);
    }
    if (!tmp.empty()) {
        tmp+=L'\0';
        prepare_one_step(tmp,strings,params,entities,parameters);
    }
}
std::string Literal::encodeEntities(const std::string & in){
    strings_t strings;
    params_t params;
    prepare(in,strings,params,true,false);
    return strings.front();
}
std::wstring Literal::encodeEntities(const std::wstring & in){
    strings_t strings;
    params_t params;
    prepare(in,strings,params,true,false);
    return ict::utf8::get(strings.front());
}
const std::string & Literal::Data::get(const Param & p) const {
    static const std::string empty;
    if (params.count(p)){
        return params.at(p);
    }
    return empty;
}
//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"

static bool test_compare(const ict::xmlt::Literal::strings_t & l,const ict::xmlt::Literal::strings_t & r){
    if (l.size()!=r.size()) {
        std::cerr<<l.size()<<"!="<<r.size()<<std::endl;
        return false;
    }
    for (std::size_t k=0;k<r.size();k++){
        if (l.at(k)!=r.at(k)) {
            std::cerr<<l.at(k)<<"!="<<r.at(k)<<std::endl;
            return false;
        }
    }
    return true;
}
static bool test_compare(const ict::xmlt::Literal::params_t & l,const ict::xmlt::Literal::params_t & r){
    if (l.size()!=r.size()) {
        std::cerr<<l.size()<<"!="<<r.size()<<std::endl;
        return false;
    }
    for (std::size_t k=0;k<r.size();k++){
        if (l.at(k)!=r.at(k)) {
            std::cerr<<l.at(k).getString()<<"!="<<r.at(k).getString()<<std::endl;
            return false;
        }
    }
    return true;
}
static int do_test1(const std::string & text_in, const ict::xmlt::Literal::strings_t & strings_out, const ict::xmlt::Literal::params_t & params_out,bool entities=true){
    ict::xmlt::Literal l(text_in,entities);
    if (!test_compare(strings_out,l.getStrings())) {
        return -1;
    }
    if (!test_compare(params_out,l.getParams())) {
        return -2;
    }
    return 0; 
}
static int do_test2(const std::string & text_in, const ict::xmlt::Literal::Data & data_in,const std::string & text_out,bool entities=true){
    ict::xmlt::Literal l(text_in,entities);
    std::string out=l.getString(data_in);
    if (text_out!=out) {
        std::cerr<<text_out<<"!="<<out<<std::endl;
        return -1;
    }
    return 0; 
}
REGISTER_TEST(literal,tc1){
    return do_test1(
        "ssdsdsd",
        {
            "ssdsdsd"
        },
        {

        },
        true
    );
}
REGISTER_TEST(literal,tc2){
    return do_test1(
        "<ala>ma 'kota' i \"psa\"</ala>&copy;&#174;&;&?",
        {
            "&lt;ala&gt;ma &apos;kota&apos; i &quot;psa&quot;&lt;/ala&gt;&copy;&#174;&amp;;&amp;?"
        },
        {

        },
        true
    );
}
REGISTER_TEST(literal,tc3){
    return do_test1(
        "<ala>ma 'kota' i \"psa\"</ala>&copy;&#174;&;&?",
        {
            "<ala>ma 'kota' i \"psa\"</ala>&copy;&#174;&;&?"
        },
        {

        },
        false
    );
}
REGISTER_TEST(literal,tc4){
    return do_test1(
        "<ala>ma '$kota' i \"$psa\"</ala>&copy;&#174;&;&?",
        {
            "&lt;ala&gt;ma &apos;",
            "&apos; i &quot;",
            "&quot;&lt;/ala&gt;&copy;&#174;&amp;;&amp;?"
        },
        {
            "kota",
            "psa"
        },
        true
    );
}
REGISTER_TEST(literal,tc5){
    return do_test1(
        "<ala>ma '$kota' i \"$psa\"</ala>&copy;&#174;&;&?",
        {
            "<ala>ma '",
            "' i \"",
            "\"</ala>&copy;&#174;&;&?"
        },
        {
            "kota",
            "psa"
        },
        false
    );
}
REGISTER_TEST(literal,tc6){
    return do_test1(
        "<ala>$ma 'kota' $i \"psa\"</ala>&copy;&#174;&;&?$$",
        {
            "&lt;ala&gt;",
            " &apos;kota&apos; ",
            " &quot;psa&quot;&lt;/ala&gt;&copy;&#174;&amp;;&amp;?$"
        },
        {
            "ma",
            "i"
        },
        true
    );
}
REGISTER_TEST(literal,tc7){
    return do_test1(
        "<ala>$ma 'kota' $i \"psa\"</ala>&copy;&#174;&;&?$$",
        {
            "<ala>",
            " 'kota' ",
            " \"psa\"</ala>&copy;&#174;&;&?$"
        },
        {
            "ma",
            "i"
        },
        false
    );
}
REGISTER_TEST(literal,tc8){
    return do_test1(
        "$ala$ma$kota",
        {
            "",
            "",
            "",
            "",
        },
        {
            "ala",
            "ma",
            "kota"
        },
        true
    );
}
REGISTER_TEST(literal,tc9){
    return do_test1(
        "&ala&ma&kota",
        {
            "&amp;ala&amp;ma&amp;kota"
        },
        {
        },
        true
    );
}
REGISTER_TEST(literal,tc10){
    return do_test2(
        "&$ala&$ma&$kota",
        ict::xmlt::Literal::param_map_t{
            {"ala","1"},
            {"ma","2"},
            {"kota","3"}
        },
        "&amp;1&amp;2&amp;3",
        true
    );
}
REGISTER_TEST(literal,tc11){
    return do_test2(
        "&$ala&$ma&$kota",
        ict::xmlt::Literal::param_map_t{
            {"ala","2"},
            {"ma","3"},
            {"kota","4"}
        },
        "&2&3&4",
        false
    );
}
#endif
//===========================================