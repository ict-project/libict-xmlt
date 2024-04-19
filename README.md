# Handy XML template library based on C++20 templates


## Basic example

Code:
```c
#include "xml-all.hpp"
using namespace ict::xmlt;
S<
    I<"xml",S<
        A<"version","1.0">,
        A<"encoding","UTF-8">
    >>,
    E<"html",A<"lang","en">,S<
        N<"head",E<"head",Nil,
            E<"title",Nil,T<"Hello World and $name!">>
        >>,
        N<"body",E<"body",Nil,S<
            E<"h1",Nil,T<"Hello World and $.head.name;!">>,
            E<"p",Nil,T<"Witaj $name!">>
        >>>
    >>
> html;
html.params["head.name"]="Universe";
html.params["body.name"]="Kolego";
std::cout<<html;
```
Output:
```
<?xml version="1.0" encoding="UTF-8"?><html lang="en"><head><title>Hello World and Universe!</title></head><body><h1>Hello World and Universe!</h1><p>Witaj Kolego!</p></body></html>
```
## Basic templates

* `ict::xmlt::Text<"example text">` or `ict::xmlt::T<"example text">` - Creates text string with XML encoding.
* `ict::xmlt::Comment<"example comment">` or `ict::xmlt::C<"example comment">` - Creates XML comment.
* `ict::xmlt::CData<"example content">` or `ict::xmlt::D<"example content">` - Creates XML CDATA section.
* `ict::xmlt::Attribute<"example_name","example_value">` or `ict::xmlt::A<"example_name","example_value">` - Creates XML attribute with given name and value (value is optional).
* `ict::xmlt::Element<"example_tag",attribute,child>` or `ict::xmlt::E<"example_tag",attribute,child>` - Creates XML element with given tag name, attributes and child element (*attribute* and *child* is optional).
* `ict::xmlt::Instruction<"example_tag",body>` or `ict::xmlt::I<"example_tag",body>` - Creates XML processing instruction element with given tag name and body (*body* is optional).
* `ict::xmlt::Doctype<body>` or `ict::xmlt::O<body>` - Creates XML document type element with given body.
* `ict::xmlt::Set<elements ...>` or `ict::xmlt::S<elements ...>` - Contains set of provided elements.
* `ict::xmlt::Array<"example_name",child>` or `ict::xmlt::Y<elements ...>` - Repeats provided child basing on value provided in *example_name* parameter.
* `ict::xmlt::Pick<"example_name",child0,child1 ...>` or `ict::xmlt::P<"example_name",child0,child1 ...>` - Creates element that is choosen from provided childs by value in *example_name* parameter ('0'- picks *child0*, '1' - picks *child1* and so on).
* `ict::xmlt::Name<"example_name",body>` or `ict::xmlt::N<"example_name",body>` - creates name space for parameters used in provided *body*.
* `ict::xmlt::Nil` or `ict::xmlt::L` - empty element (if needed by other).

## Parameters

In any content of XML document the template parameters may be used. The name of the parameter is provided directly in the text and starts with '$' (dollar sign) and ends with ';' (semicolon - that is optional if next character is not alphanumeric, nor is one of following characters: '.', '[', ']', '#', '_').

Example (parameter *name*):
```c
T<"Hello World and $name!">
```

If `ict::xmlt::Name<>` is used then names of parameters are prefixed with given name space.

Example (parameter *space.name*):
```c
N<"space",T<"Hello World and $name!">>
```

If `ict::xmlt::Array<>` is used then names of parameters are prefixed with given name space and occurance ID (in square brakets).

Example (parameter *array[0].name*):
```c
Y<"array",T<"Hello World and $name!">>
```

If `ict::xmlt::Pick<>` is used then names of parameters are prefixed with given name space and number of element (after hash).

Example (parameter *pick#0.name*):
```c
P<"pick",T<"Hello World and $name!">>
```

The name of the parameter can contain leading dots, that means that parameter should be placed in higier level of name space (more dots, more levels).

Example (parameter *name*):
```c
N<"space",T<"Hello World and $.name!">>
```

## Usage

Generaly XML template is defined by a C++ type - example:
```c
#include "xml-all.hpp"
using namespace ict::xmlt;

template <class Header=Nil, class Body=Nil> using Html = S<
    I<"xml",S<
        A<"version","1.0">,
        A<"encoding","UTF-8">
    >>,
    O<A<"html">>,
    E<"html",A<"lang","en">,S<
        N<"head",E<"head",Nil,Header>>,
        N<"body",E<"body",Nil,Body>>
    >>
>;
```
This type can be used to declare a variable - example:
```c
Html<Nil,T<"Hello World and $name;!">> html;
```
The variable is filled with data - example:
```c
html.params["body.name"]="Kolego";
```
Finaly the variable can be serialized into XML - examle:
```c
std::cout<<html;
```
Output:
```
<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE html><html lang="en"><head/><body>Hello World and Kolego!</body></html>
```

## Building instructions

```sh
make # Build library
make test # Execute all tests
make package # Create library package
make package_source  # Create source package
```