# Simple UTF8 encoder/decoder implementation [![Build Status](https://travis-ci.org/ict-project/libict-utf8.svg?branch=main)](https://travis-ci.org/ict-project/libict-utf8)

This code implements a simple UTF8 encoder/decoder.

See:
* [robot](source/robot.md) for more details about single character processing;
* [get](source/get.md) for more details about string encoding/decoding get interface;
* [transfer](source/transfer.md) for more details about string encoding/decoding transfer interface;
* [stream](source/stream.md) for more details about UTF8 stream modifier (since v1.1).

Releases:
* Branch release-v1 [![Build Status](https://travis-ci.org/ict-project/libict-utf8.svg?branch=release-v1)](https://travis-ci.org/ict-project/libict-utf8)

## Building instructions

```sh
make # Build library
make test # Execute all tests
make package # Create library package
make package_source  # Create source package
```