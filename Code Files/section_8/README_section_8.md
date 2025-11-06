# Section 8 (Coroutines)

As originally written circa 2019-2020, the code in `section_8`
assumed that the coroutines are in the `std::experimental` namespace and
the header in `<experimental/coroutine>`. Other than example 1, they
depend on `ccpcoro` which similarly assumes coroutines are still
experimental.

This is no longer the case in 2025, and in g++ the include path and
namespace no longer include experimental, in fact it causes compile
errors.

I can get example 1 from section_8 to work by changing the include
statements, and removing `experimental::` from the namespace in
the example1.cpp and generator.hpp files.

I can not get the later examples to work because the third-party
`cppcoro` library remains hardwired for `experimental`.
