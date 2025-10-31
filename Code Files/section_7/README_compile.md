# Compiling Section 7 (Threading)

I've added this to document my attempts to get this working with
either G++ 14.3 or Apple Clang 17.0

## Using Original CMakeLists.txt

```bash
[ 83%] Linking CXX executable section_7_ex_1
ld: library 'tsan' not found
collect2: error: ld returned 1 exit status
make[2]: *** [section_7/section_7_ex_1] Error 1
make[1]: *** [section_7/CMakeFiles/section_7_ex_1.dir/all] Error 2
make: *** [all] Error 2

```