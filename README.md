# C# to C++
This project is an adaptation of the .NET library to C++.

It is aimed to rewrite certain Classes and Methods in .NET in C++ and allow developers to access the classes and methods in the .NET library without .NET dependency.
## Example
```cpp
#include "System.h"
#include "System.IO.h"

using namespace System;
using namespace SystemIO;

int main()
{
    Console::WriteLine("Hello Wolrld!");
    if (!Directory::Exists(L"C:\\Path"))
    {
        Directory::Create(L"C:\\Path");
    }
    else
    {
        Console::WriteLine("Directory already exists!");
    }
    Environment::Exit(0);
}
```
