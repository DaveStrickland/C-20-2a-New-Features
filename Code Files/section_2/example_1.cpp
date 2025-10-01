#include "inc.hpp"

using namespace std;

int main()
{
    // 100 -> 0x00000064
    int n = 100;
    int pad = 10;

    printf("%#0*x\n", pad, n);
    cout << "0x" << setfill('0') << setw(pad-2) << hex << n << endl;

    // cout << format("{:0=#{}x}\n", n, pad);

    /*
        DKS: The original example will not compile. See
        https://en.cppreference.com/w/cpp/utility/format/format.html which says
        It is an error if the format string is not a constant expression unless 
        it is initialized from the result of std::runtime_format(since C++26). 
        std::vformat does not have this requirement. 

        Also had to modify the format string.
     */
    cout << std::vformat("{:0{}x}\n", std::make_format_args(n, pad));
}
