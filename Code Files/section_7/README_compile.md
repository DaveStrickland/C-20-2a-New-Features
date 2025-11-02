# Compiling Section 7 (Threading)

I've added this to document my attempts to get this working with
either G++ 14.3 or Apple Clang 17.0 on MacOS Sequoia 15.7.1 (M1 Max).

## On Fedora Linux 42 It Compiles And Run Fine

The only slight changes needed were to (a) install libtsan, and `#include <latch>` 
and `#include <barrier>`. Otherwise works out of the box, because its Linux.

## Using Original CMakeLists.txt on MacOS

With G++-14 as the compiker we get:

```bash
[ 83%] Linking CXX executable section_7_ex_1
ld: library 'tsan' not found
collect2: error: ld returned 1 exit status
make[2]: *** [section_7/section_7_ex_1] Error 1
make[1]: *** [section_7/CMakeFiles/section_7_ex_1.dir/all] Error 2
make: *** [all] Error 2
```

Switching off the other sections and resetting everything to use Apple Clang 17.0
(and `make VERBOSE=1`) we get:

```bash
cmake ../ -DCMAKE_CXX_COMPILER=$(which c++)
-- Configuring done (0.2s)
You have changed variables that require your cache to be deleted.
Configure will be re-run and you may have to reset some variables.
The following variables have changed:
CMAKE_CXX_COMPILER= /usr/bin/c++

-- The C compiler identification is AppleClang 17.0.0.17000319
-- The CXX compiler identification is AppleClang 17.0.0.17000319
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done (1.3s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/dstrickland/git/C-20-2a-New-Features/Code Files/build
proteus/Darwin ~/git/C-20-2a-New-Features/Code Files/build (master *) 10:01:01> make VERBOSE=1
/opt/homebrew/bin/cmake -S"/Users/dstrickland/git/C-20-2a-New-Features/Code Files" -B"/Users/dstrickland/git/C-20-2a-New-Features/Code Files/build" --check-build-system CMakeFiles/Makefile.cmake 0
/opt/homebrew/bin/cmake -E cmake_progress_start "/Users/dstrickland/git/C-20-2a-New-Features/Code Files/build/CMakeFiles" "/Users/dstrickland/git/C-20-2a-New-Features/Code Files/build//CMakeFiles/progress.marks"
/Applications/Xcode.app/Contents/Developer/usr/bin/make  -f CMakeFiles/Makefile2 all
/Applications/Xcode.app/Contents/Developer/usr/bin/make  -f section_7/CMakeFiles/section_7_ex_1.dir/build.make section_7/CMakeFiles/section_7_ex_1.dir/depend
cd "/Users/dstrickland/git/C-20-2a-New-Features/Code Files/build" && /opt/homebrew/bin/cmake -E cmake_depends "Unix Makefiles" "/Users/dstrickland/git/C-20-2a-New-Features/Code Files" "/Users/dstrickland/git/C-20-2a-New-Features/Code Files/section_7" "/Users/dstrickland/git/C-20-2a-New-Features/Code Files/build" "/Users/dstrickland/git/C-20-2a-New-Features/Code Files/build/section_7" "/Users/dstrickland/git/C-20-2a-New-Features/Code Files/build/section_7/CMakeFiles/section_7_ex_1.dir/DependInfo.cmake" "--color="
Dependencies file "section_7/CMakeFiles/section_7_ex_1.dir/example_1.cpp.o.d" is newer than depends file "/Users/dstrickland/git/C-20-2a-New-Features/Code Files/build/section_7/CMakeFiles/section_7_ex_1.dir/compiler_depend.internal".
Consolidate compiler generated dependencies of target section_7_ex_1
/Applications/Xcode.app/Contents/Developer/usr/bin/make  -f section_7/CMakeFiles/section_7_ex_1.dir/build.make section_7/CMakeFiles/section_7_ex_1.dir/build
[ 10%] Building CXX object section_7/CMakeFiles/section_7_ex_1.dir/example_1.cpp.o
cd "/Users/dstrickland/git/C-20-2a-New-Features/Code Files/build/section_7" && /usr/bin/c++  -I"/Users/dstrickland/git/C-20-2a-New-Features/Code Files/common" -std=c++20 -arch arm64 -fsanitize=thread -MD -MT section_7/CMakeFiles/section_7_ex_1.dir/example_1.cpp.o -MF CMakeFiles/section_7_ex_1.dir/example_1.cpp.o.d -o CMakeFiles/section_7_ex_1.dir/example_1.cpp.o -c "/Users/dstrickland/git/C-20-2a-New-Features/Code Files/section_7/example_1.cpp"
In file included from /Users/dstrickland/git/C-20-2a-New-Features/Code Files/section_7/example_1.cpp:1:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/memory:985:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/atomic:605:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/aliases.h:12:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/atomic.h:12:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/atomic_sync.h:12:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/contention_t.h:12:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/support.h:109:
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/support/c11.h:38:37: error: _Atomic cannot be applied to type 'std::shared_ptr<int>' which is not trivially copyable
   38 |   _LIBCPP_DISABLE_EXTENSION_WARNING _Atomic(_Tp) __a_value;
      |                                     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/support.h:115:35: note: in instantiation of template class 'std::__cxx_atomic_base_impl<std::shared_ptr<int>>' requested here
  115 | struct __cxx_atomic_impl : public _Base {
      |                                   ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/atomic.h:41:34: note: in instantiation of template class 'std::__cxx_atomic_impl<std::shared_ptr<int>>' requested here
   41 |   mutable __cxx_atomic_impl<_Tp> __a_;
      |                                  ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/atomic.h:230:24: note: in instantiation of template class 'std::__atomic_base<std::shared_ptr<int>>' requested here
  230 | struct atomic : public __atomic_base<_Tp> {
      |                        ^
/Users/dstrickland/git/C-20-2a-New-Features/Code Files/section_7/example_1.cpp:8:39: note: in instantiation of template class 'std::atomic<std::shared_ptr<int>>' requested here
    8 |     std::atomic<std::shared_ptr<int>> ptr = std::make_shared<int>(4);
      |                                       ^
In file included from /Users/dstrickland/git/C-20-2a-New-Features/Code Files/section_7/example_1.cpp:1:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/memory:985:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/atomic:605:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/aliases.h:12:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/atomic.h:12:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/atomic_sync.h:12:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/contention_t.h:12:
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/support.h:116:17: error: static assertion failed due to requirement 'is_trivially_copyable<std::shared_ptr<int>>::value': std::atomic<T> requires that 'T' be a trivially copyable type
  116 |   static_assert(is_trivially_copyable<_Tp>::value, "std::atomic<T> requires that 'T' be a trivially copyable type");
      |                 ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/atomic.h:41:34: note: in instantiation of template class 'std::__cxx_atomic_impl<std::shared_ptr<int>>' requested here
   41 |   mutable __cxx_atomic_impl<_Tp> __a_;
      |                                  ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__atomic/atomic.h:230:24: note: in instantiation of template class 'std::__atomic_base<std::shared_ptr<int>>' requested here
  230 | struct atomic : public __atomic_base<_Tp> {
      |                        ^
/Users/dstrickland/git/C-20-2a-New-Features/Code Files/section_7/example_1.cpp:8:39: note: in instantiation of template class 'std::atomic<std::shared_ptr<int>>' requested here
    8 |     std::atomic<std::shared_ptr<int>> ptr = std::make_shared<int>(4);
      |                                       ^
2 errors generated.
make[2]: *** [section_7/CMakeFiles/section_7_ex_1.dir/example_1.cpp.o] Error 1
make[1]: *** [section_7/CMakeFiles/section_7_ex_1.dir/all] Error 2
make: *** [all] Error 2

```

Looning at the [C++20 support page](https://en.cppreference.com/w/cpp/compiler_support/20.html)
it is clear that neither clang or apple clang support Atomic std::shared_ptr, so we dead on that front.