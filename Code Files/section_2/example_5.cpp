#include "inc.hpp"

using std::cout;
using std::endl;

int main()
{
    // DKS: Note that forat works here because this is a constexpr. It does not change.
    cout << std::format("The number is {} and {}",  20, 6) << endl;
    cout << std::format("Die Zahl ist {1} und {0}", 20, 6) << endl;

    // DKS: The orginal case, naively reformatted from format to vformat, as shown below,
    // will result in the following g++-14 compiker error
    //      example_5.cpp:8:79: error: cannot bind non-const lvalue reference of type 'int&' to an rvalue of type 'int'
    //      8 |     cout << std::vformat("The number is {} and {}",     std::make_format_args(20, 6)) << endl;
    /*
    cout << std::vformat("The number is {} and {}",     std::make_format_args(20, 6)) << endl;
    cout << std::vformat("Die Zahl ist {1} und {0}",    std::make_format_args(20, 6)) << endl;
    */
}
