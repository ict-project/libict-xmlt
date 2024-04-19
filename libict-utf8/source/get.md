# `ict::utf8::get` interface

Provides conversion between `std::string` (with *UTF8* encoding) and `std::wstring` strings.

## Usage

### `ict::utf8::get(input)`

The `ict::utf8::get(input)` functions just returns a converted string (from a given input). 
The input string is not modified by these functions. 
Any incomplete sequence of UTF8 bytes in the input string are ignored.

An example of a getting an `std::wstring`:
```c
{
  std::string input("Pchnąć w tę łódź jeża lub ośm skrzyń fig.");
  std::wstring output=ict::utf8::get(input);
  // The result is:
  // input="Pchnąć w tę łódź jeża lub ośm skrzyń fig."
  // output="Pchnąć w tę łódź jeża lub ośm skrzyń fig."
}
```

An example of a getting an `std::string` (with *UTF8* encoding):
```c
{
  std::wstring input(L"Pójdźże, kiń tę chmurność w głąb flaszy!");
  std::string output=ict::utf8::get(input);
  // The result is:
  // input="Pójdźże, kiń tę chmurność w głąb flaszy!"
  // output="Pójdźże, kiń tę chmurność w głąb flaszy!"
}
```

### `ict::utf8::get(input,output)`

The `ict::utf8::get(input,output)` functions converts string from input to output. 
The input string is not modified by these functions.
Any incomplete sequence of UTF8 bytes in the input string are ignored.

An example of a getting an `std::wstring`:
```c
{
  std::string input("Pchnąć w tę łódź jeża lub ośm skrzyń fig.");
  std::wstring output;
  ict::utf8::get(input,output);
  // The result is:
  // input="Pchnąć w tę łódź jeża lub ośm skrzyń fig."
  // output="Pchnąć w tę łódź jeża lub ośm skrzyń fig."
}
```

An example of a getting an `std::string` (with *UTF8* encoding):
```c
{
  std::wstring input(L"Pójdźże, kiń tę chmurność w głąb flaszy!");
  std::string output
  ict::utf8::get(input,output);
  // The result is:
  // input="Pójdźże, kiń tę chmurność w głąb flaszy!"
  // output="Pójdźże, kiń tę chmurność w głąb flaszy!"
}
```
