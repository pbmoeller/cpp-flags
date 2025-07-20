# cpp-flags

## Description

`cppflags` is a lightweight, modern, and header-only C++20 library that provides a type-safe and flexible bit flag utility for working with traditional `enum` and `enum class` types - including signed and unsigned integer types of 32 or 64 bits.

It supports clean and intuitive bitwise operations on enum values without any dependencies.

## Features

- [x] Type-safe wrapper for enum and enum class
- [x] Full support for int, uint, int64_t, and uint64_t underlying types
- [x] Header-only and dependency-free
- [x] Bitwise operators: |, &, ^, ~, and compound assignments
- [x] Works with std::initializer_list for flag combinations
- [x] testFlag, testFlags, and setFlag utility functions
- [x] Fully constexpr and C++20-compliant
