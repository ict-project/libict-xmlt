//! @file
//! @brief UTF8 get module - Source file.
//! @author Mariusz Ornowski (mariusz.ornowski@ict-project.pl)
//! @version 1.0
//! @date 2012-2021
//! @copyright ICT-Project Mariusz Ornowski (ict-project.pl)
/* **************************************************************
Copyright (c) 2012-2021, ICT-Project Mariusz Ornowski (ict-project.pl)
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
#include "get.hpp"
#include "robot.hpp"
//============================================
namespace ict { namespace utf8 {
//===========================================
void get(const std::string & input,std::wstring & output){
  ict::utf8::robot r;
  output.clear();
  for (const char & c : input){
    if (r(c).isReady()){
      output+=r.getChar();
    }
  }
}
void get(const std::wstring & input,std::string & output){
  ict::utf8::robot r;
  output.clear();
  for (const wchar_t & c : input){
    if (r(c).isReady()){
      output+=r.getString();
    }
  }
}
std::wstring get(const std::string & input){
  std::wstring output;
  get(input,output);
  return(output);
}
std::string get(const std::wstring & input){
  std::string output;
  get(input,output);
  return(output);
}
void get(const std::string & input,std::string & output){
    output=input;
}
void get(const std::wstring & input,std::wstring & output){
    output=input;
}
//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
REGISTER_TEST(utf8_get,tc1){
  std::size_t k=0;
  std::cout<<" Test funcji ict::utf8::get(string)"<<std::endl;
  for (const auto & s : ict::test::test_string){
    std::string input(s);
    std::wstring output(ict::test::test_wstring[k++]);
    std::wstring out=ict::utf8::get(input);
    if (output!=out){
      std::cout<<" Błąd!!!"<<std::endl;
      std::cout<<" input="<<input<<std::endl;
      std::wcout<<L" output(oczekiwany)="<<output<<std::endl;
      std::wcout<<L" output(otrzymany)="<<out<<std::endl;
      return(-1);
    }
  }
  return(0);
}
REGISTER_TEST(utf8_get,tc2){
  std::size_t k=0;
  std::cout<<" Test funcji ict::utf8::get(wstring)"<<std::endl;
  for (const auto & s : ict::test::test_wstring){
    std::wstring input(s);
    std::string output(ict::test::test_string[k++]);
    std::string out=ict::utf8::get(input);
    if (output!=out){
      std::cout<<" Błąd!!!"<<std::endl;
      std::wcout<<L" input="<<input<<std::endl;
      std::cout<<" output(oczekiwany)="<<output<<std::endl;
      std::cout<<" output(otrzymany)="<<out<<std::endl;
      return(-1);
    }
  }
  return(0);
}
#endif
//===========================================