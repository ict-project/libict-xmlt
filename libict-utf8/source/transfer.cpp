//! @file
//! @brief UTF8 transfer module - Source file.
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
#include "transfer.hpp"
#include "robot.hpp"
//============================================
namespace ict { namespace utf8 {
//===========================================
void transfer(std::string & input,std::wstring & output,std::size_t max){
  ict::utf8::robot r;
  if (max==std::wstring::npos) max=output.max_size();
  while(input.size()){
    for(std::size_t k=0;k<input.size();k++){
      if (r(input.at(k)).isReady()){
        if (max<(output.size()+1)){
          return;
        } else {
          input.erase(0,k+1);
          output+=r.getChar();
        }
        break;
      }
    }
    if (!r.isReady()) return;
  }
}
void transfer(std::wstring & input,std::string & output,std::size_t max){
  ict::utf8::robot r;
  if (max==std::string::npos) max=output.max_size();
  while(input.size()){
    for(std::size_t k=0;k<input.size();k++){
      if (r(input.at(k)).isReady()){
        if (max<(output.size()+r.getString().size())){
          return;
        } else {
          input.erase(0,k+1);
          output+=r.getString();
        }
        break;
      }
    }
    if (!r.isReady()) return;
  }
}
//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
REGISTER_TEST(utf8_transfer,tc1){
  std::size_t k=0;
  std::cout<<" Test funkcji ict::utf8::transfer(string,wstring)"<<std::endl;
  for (const auto & s : ict::test::test_string){
    std::string input(s);
    std::wstring output(ict::test::test_wstring[k++]);
 
    std::wstring out;
    ict::utf8::transfer(input,out);

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
REGISTER_TEST(utf8_transfer,tc2){
  std::size_t k=0;
  std::cout<<" Test funkcji ict::utf8::transfer(wstring,string)"<<std::endl;
  for (const auto & s : ict::test::test_wstring){
    std::wstring input(s);
    std::string output(ict::test::test_string[k++]);
    
    std::string out;
    ict::utf8::transfer(input,out);
    
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
REGISTER_TEST(utf8_transfer,tc3){
  std::size_t k=0;
  std::cout<<" Test funkcji ict::utf8::transfer(string,wstring)"<<std::endl;
  for (const auto & s : ict::test::test_string){
    std::string input(s);
    std::wstring output(ict::test::test_wstring[k++]);

    std::string in;
    std::wstring out;    
    for(std::size_t k=0;k<input.size();k+=3){
      in+=input.substr(k,3);
      ict::utf8::transfer(in,out);
    }

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
REGISTER_TEST(utf8_transfer,tc4){
  std::size_t k=0;
  std::cout<<" Test funkcji ict::utf8::transfer(wstring,string)"<<std::endl;
  for (const auto & s : ict::test::test_wstring){
    std::wstring input(s);
    std::string output(ict::test::test_string[k++]);
    

    std::wstring in;
    std::string out;
    for(std::size_t k=0;k<input.size();k+=3){
      in+=input.substr(k,3);
      ict::utf8::transfer(in,out);
    }
    
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