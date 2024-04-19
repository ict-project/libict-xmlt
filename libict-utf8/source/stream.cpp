//! @file
//! @brief UTF8 stream module - Source file.
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
#include "stream.hpp"
//============================================
namespace ict { namespace utf8 {
//===========================================

//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
#include <sstream>
REGISTER_TEST(utf8_stream,tc1){
  std::wstring str(L",out2");
  std::cout<<ict::utf8::s(L"out1")<<ict::utf8::s(str)<<std::endl;
  return(0);
}
REGISTER_TEST(utf8_stream,tc2){
  std::string str(",out2");
  std::wcout<<ict::utf8::s("out1")<<ict::utf8::s(str)<<std::endl;
  return(0);
}
REGISTER_TEST(utf8_stream,tc3){
  std::wstring str(L"inout1");
  std::stringstream ios;
  ios<<ict::utf8::s(L"out1")<<ict::utf8::s(str)<<std::endl;
  ios>>ict::utf8::s(str);
  std::wcout<<str<<std::endl;
  if (str!=L"out1inout1") return(1);
  return(0);
}
REGISTER_TEST(utf8_stream,tc4){
  std::string str("inout1");
  std::wstringstream ios;
  ios<<ict::utf8::s("out1")<<ict::utf8::s(str)<<std::endl;
  ios>>ict::utf8::s(str);
  std::cout<<str<<std::endl;
  if (str!="out1inout1") return(1);
  return(0);
}
#endif
//===========================================