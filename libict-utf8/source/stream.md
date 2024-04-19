# `ict::utf8::s` stream modifier - since v1.1

Converts `std::string` (with *UTF8* encoding) and `std::wstring` strings so they could be used in `std::istream`, `std::wistream`, `std::ostream` and `std::wostream`.

## Usage

### `ict::utf8::s(input)`

Output example:
```c
std::cout<<ict::utf8::s("out1")<<ict::utf8::s(L",out2")<<std::endl;//Writes: "out1,out2"
std::wcout<<ict::utf8::s("out1")<<ict::utf8::s(L",out2")<<std::endl;//Writes: "out1,out2"
```

Input example:
```c
std::string input1;
std::wstring input2;
std::cin>>ict::utf8::s(input1)>>ict::utf8::s(input2);//Reads input1 and input2
std::wcin>>ict::utf8::s(input1)>>ict::utf8::s(input2);//Reads input1 and input2
```