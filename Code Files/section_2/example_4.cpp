#include "inc.hpp"

using std::cout;
using std::endl;

int main()
{
    // DKS: This example also suffers from non-const lval to rval issue.
    // See https://en.cppreference.com/w/cpp/utility/format/format_to.html
    // Equivalent to return std::vformat_to(std::move(out), fmt.str, std::make_format_args(args...));
    // or variants thereof

    // Example using container, which is really a lead-up to demonstrating
    // formatted_size and the c-style character buffer that is NULL terminated
    int num = 1042;
    std::vector<char> buf;

    std::format_to(std::back_inserter(buf), "{:#x}", num); // format to an iterator to container
    std::back_inserter(buf) = '\0';

    char* buf_ptr  = buf.data();    // DKS: added
    int   buf_size = buf.size();    // DKS: added
    std::cout << std::vformat("result 0: {} ({})\n", std::make_format_args(buf_ptr, buf_size));

    auto size = std::formatted_size("{:#x}", num) + 1;
    std::vector<char> buf2(size);
    auto result2 = std::format_to(buf2.data(), "{:#x}", num);   // format directly to pre-sized container
    *result2 = '\0';
    buf_ptr = buf2.data();    // DKS: added
    cout << std::vformat("result 1: {} ({})\n", std::make_format_args(buf_ptr, size));

    // DKS: https://en.cppreference.com/w/cpp/utility/format/format_to_n.html
    // Writes at most n characters, that end up in a structure with the output and size.
    // Not really sure why you would do this.
    char cbuf[10];
    auto result3 = std::format_to_n(cbuf, sizeof(cbuf), "{:#x}", num);
    *result3.out = '\0';
    int new_size = 1 + result3.size;    // DKS: added
    cout << std::vformat("result 2: {} ({})\n", std::make_format_args(cbuf, new_size));
}
