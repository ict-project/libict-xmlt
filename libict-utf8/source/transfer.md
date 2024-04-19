# `ict::utf8::transfer` interface

Provides conversion between `std::string` (with *UTF8* encoding) and `std::wstring` strings.

## Usage

### `ict::utf8::transfer(input,output)`

The `ict::utf8::transfer()` functions *transfer* characters from an input (first argument) 
 to an output (second argument) string. It means that the input string is modified by these
 functions. An advantage of this approach is that *transfer* may be done in steps, even
 if an incomplete sequence of UTF8 bytes was received in the input string. In that case
 the incomplete sequence is leaved in the input string so it could be completed in
 the next step. The output string isn't cleared by these functions - the new characters
 are added at the end of the string.

An example of a *transfer* from  `std::string` (with *UTF8* encoding) to `std::wstring`:

```c
{
  std::string input("Pchnąć w tę łódź jeża lub ośm skrzyń fig.");
  std::wstring output(L"Pójdźże, kiń tę chmurność w głąb flaszy!");
  ict::utf8::transfer(input,output)
  // The result is:
  // input=""
  // output="Pchnąć w tę łódź jeża lub ośm skrzyń fig.Pójdźże, kiń tę chmurność w głąb flaszy!"
}
```

An example of a *transfer* from  `std::wstring` to `std::string` (with *UTF8* encoding):

```c
{
  std::wstring input(L"Pójdźże, kiń tę chmurność w głąb flaszy!");
  std::string output("Pchnąć w tę łódź jeża lub ośm skrzyń fig.");
  ict::utf8::transfer(input,output)
  // The result is:
  // input=""
  // output="Pójdźże, kiń tę chmurność w głąb flaszy!Pchnąć w tę łódź jeża lub ośm skrzyń fig."
}
```
