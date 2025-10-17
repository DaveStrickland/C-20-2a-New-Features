# Compiling from the command line with G++ or Clang

Added to record the compiling by hand parts of the course.

## G++

The module file is treated like any other C++ file on the command line.

```bash
g++-14 -std=c++20 -fmodules-ts M.cpp example_4.cpp -o example_4.exe
```

However, behind the scenes `g++` creates a gcm.cache directory containing a M.gcm file.

## Clang

```bash
# Slightly adatoped from course video, so not clang++9 and not -std=c++2a
# This is really Fortran90 module-like!
clang++ -std=c++20 -fmodules-ts --precompile -x c++-module M.cpp -o M.pcm
clang++ -std=c++20 -fmodules-ts -c M.pcm -o M.o
clang++ -std=c++20 -fmodules-ts -fprebuilt-module-path=. example_4.cpp M.o -o example_4_clang.exe
```

    None of this is working correctly

Of course it didn't work.... maybe Apple clang doesn't support it that way. After some messing about...
using https://releases.llvm.org/17.0.1/tools/clang/docs/StandardCPlusPlusModules.html (which is not
necessarily Apple Clang 17)...

```bash
clang++ -std=c++20 -fmodules M.cpp --precompile -o M.pcm
clang++ -std=c++20 -fmodules  M.pcm -o M.o
fatal error: file 'M.pcm' is not a valid precompiled AST file: file doesn't start with AST file magic
1 error generated.

#clang++ -std=c++20 -fmodules -fprebuilt-module-path=. example_4.cpp -o example_4_clang.exe
```

Try again
```bash
clang++ -std=c++20 M.cpp --precompile -o M.pcm
clang++ -std=c++20 example_4.cpp -fprebuilt-module-path=. M.pcm -o example_4_clang.exe
example_4.cpp:1:1: error: unknown type name 'import'
    1 | import M;
      | ^
example_4.cpp:7:20: error: use of undeclared identifier 'f'
    7 |     printf("%d\n", f(5));
      |                    ^
example_4.cpp:8:20: error: use of undeclared identifier 'g'
    8 |     printf("%f\n", g(0.0, 1));
      |                    ^
3 errors generated.
fatal error: file 'M.pcm' is not a valid precompiled AST file: file doesn't start with AST file magic
1 error generated.
```

However Clang documentation states:

    The file name of an importable module unit should end with .cppm (or .ccm, .cxxm, .c++m). The file name of a module implementation unit should end with .cpp (or .cc, .cxx, .c++).

    The file name of BMIs should end with .pcm. The file name of the BMI of a primary module interface unit should be module_name.pcm. The file name of BMIs of module partition unit should be module_name-partition_name.pcm.

    If the file names use different extensions, Clang may fail to build the module. For example, if the filename of an importable module unit ends with .cpp instead of .cppm, then we can’t generate a BMI for the importable module unit by --precompile option since --precompile option now would only run preprocessor, which is equal to -E now. If we want the filename of an importable module unit ends with other suffixes instead of .cppm, we could put -x c++-module in front of the file. For example,

```bash
clang++ -std=c++20 -x c++-module M.cpp --precompile -o M.pcm
M.cpp:1:8: error: expected template
    1 | export module M;
      |        ^
M.cpp:1:8: error: unknown type name 'module'
M.cpp:3:8: error: expected template
    3 | export int f(int x)
      |        ^
M.cpp:7:8: error: expected template
    7 | export double g(double y, int z)
      |        ^
4 errors generated.

clang++ -std=c++20 example_4.cpp -fprebuilt-module-path=. M.pcm -o example_4_clang.exe
clang++: error: no such file or directory: 'M.pcm'
```

I give up.