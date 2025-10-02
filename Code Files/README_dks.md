# Modified Version for G++-14 and Apple Clang 17

These files have been modified to make use of more modern (2025 instead of 2020)
compiler support, so that the use of the independent implementations is not
needed (in fact they cuase problems with G++ version 14).

Dave Strickland 2025-10-01 <dave.strickland@gmail.com>

## Changes

[X] Disable FetchContent for fmt, cpp_coro, ranges libraries in CMakeLists.txt.
[X] Disable addition of those implementations include directories in the project.
[X] Modify `inc.hpp` in `common/`
[X] Get section 2 (format) working
[ ] Get section 3 (ranges) working