# `ict::utf8::robot` class

Provides single character processing between `std::string` (with *UTF8* encoding) and `std::wstring` strings.

## Interface

```c
//! 
//! @brief Adds a char character to the robot.
//! 
//! @param input Character to add.
//! 
ict::utf8::robot & operator ()(const char & input);
//! 
//! @brief Adds a wide char character to the robot.
//! 
//! @param input Character to add.
//! 
ict::utf8::robot & operator ()(const wchar_t & input);
//! 
//! @brief Gets the output wide char character.
//! 
//! @return The output wide char character.
//! 
const wchar_t & getChar() const;
//! 
//! @brief Gets the output char string.
//! 
//! @return The output char string.
//! 
const std::string & getString() const;
//! 
//! @brief Informs if robot is ready to generate the output (getChar() or getString())
//! 
//! @return true Gotowy do odczytu
//! @return false Jeszcze nie gotowy do odczytu.
//! 
bool isReady() const;
//! 
//! @brief Clears object.
//! 
void clear();
//!
//! @brief Checks whether the specified string has multibyte UTF8 characters.
//!
//! @param input String to check.
//! @return true The string has multibyte UTF8 characters.
//! @return false The string has not multibyte UTF8 characters.
//!
static bool hasUtf8(const std::string & input);
```

## Usage

From `std::string` to `std::wstring`:
```c
#inlude "libict-utf8/source/robot.hpp"

std::string input;
std::wstring output;
ict::utf8::robot r;
for (const char & c : input){//Read char by char
    if (r(c).isReady()){//When robot is ready (has enough data)
        output+=r.getChar();//Write output.
    }
}
```

From `std::wstring` to `std::string`:
```c
#inlude "libict-utf8/source/robot.hpp"

std::wstring input;
std::string output;
ict::utf8::robot r;
for (const wchar_t & c : input){//Read char by char
    if (r(c).isReady()){//When robot is ready (has enough data)
        output+=r.getString();//Write output.
    }
}
```
