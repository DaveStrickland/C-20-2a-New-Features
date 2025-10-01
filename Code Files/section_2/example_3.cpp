#include "inc.hpp"

using std::string;
using std::cout;
using std::endl;

struct Person2
{
    int id;
    int ant;
};

int main()
{
    int num = 100;
    string s = "aa";
    Person2 p;
    printf("garbage 1: %f\n", num);
    printf("garbage 2: %s\n", p);
    printf("garbage 3: %s\n");
    //printf("garbage 4: %s\n", s);

    try
    {
        cout << std::vformat("{:f", std::make_format_args(num)) << endl;    // DKS: Use vformat, make_format_args
    }
    catch (const std::format_error& ex)
    {   
        std::string what = ex.what();   // DKS: ex.what() is an rvalue ref, but std::make_format_args only takes lvalue, so we cant ex.what() directly
        cout <<std::vformat("!!! Exception: {}\n", std::make_format_args(what));
    }
}
