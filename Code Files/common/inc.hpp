#pragma once

#include <format>   // was #include <fmt/format.h>
// not needed? #include <fmt/ostream.h>
#include <ranges>   // was #include <range/v3/all.hpp>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cxxabi.h>
#include <typeinfo>
#include <cmath>
#include <utility>

// not needed?  using namespace fmt;
using std::cout;
using std::endl;
using namespace std::string_literals;

template<typename T>
struct ShowType;

inline std::string demangle(const std::string& name)
{
    int status;
    auto ptr = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);
    std::string str(ptr);
    free(ptr);
    return str;
}

template<typename T>
inline std::string typeName()
{
    return demangle(typeid(T).name());
}

template<typename T>
inline std::string typeName(T&& obj)
{
    return demangle(typeid(obj).name());
}

// DKS: C++20 std::format does not provide an equivalent to fmt::join
// The following is a quick hack based on the C++ Cookbook by Stevens, Diggins, Turkanis & Cogswell
// https://learning.oreilly.com/library/view/c-cookbook/0596007612/ch04s09.html#cplusplusckbk-CHP-4-SECT-8.2

inline std::string join(const std::vector<int>& vec, const std::string &sep)
{
    std::string ostr;

    for (std::vector<int>::const_iterator p = vec.cbegin(); p != vec.cend(); ++p)
    {
        ostr += std::to_string( *p );
        if (p != vec.cend() - 1)
        {
            ostr += sep;
        }
    }
    return ostr;
}

// DKS: C++20 std::ranges does not have the proposed ranges to_vector. C++23 has to<> template.
// In the mean time try this from stack overflow: https://stackoverflow.com/a/63116423
//
// Example usage:
//    auto result2 = to_vector<>( numbers
//        | std::ranges::views::filter([](int n){ return n % 2 == 0; })
//        | std::ranges::views::transform([](int n){ return n * 2; }) );
//
template <std::ranges::range R>
auto to_vector(R&& r) {
    std::vector<std::ranges::range_value_t<R>> v;

    // if we can get a size, reserve that much
    if constexpr (requires { std::ranges::size(r); }) {
        v.reserve(std::ranges::size(r));
    }

    // push all the elements
    for (auto&& e : r) {
        v.push_back(static_cast<decltype(e)&&>(e));
    }

    return v;
}

