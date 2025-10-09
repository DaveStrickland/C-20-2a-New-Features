#include <inc.hpp>
#include <compare>

template<typename T>
struct MyValue
{
    T v;
    constexpr MyValue(T v) : v{v} {}
    auto operator <=>(const MyValue&) const = default;
};

int main()
{
    MyValue iw1{1.0f};
    MyValue iw2{NAN};

    cout << "lhs lower: " <<(iw1 <=> iw2 < 0) << endl;  // DKS: use of 3way op, this is equivalent to iw1 < iw2
    cout << "lhs equal: " <<(iw1 <=> iw2 == 0) << endl; // DKS: equivalent of iw1 == iw2
    cout << "lhs higher: " <<(iw1 <=> iw2 > 0) << endl; // DKS: equivalent of iw1 > iw2 

    cout << typeName(iw2 <=> iw2) << endl;              // DKS: type of ordering supported
                                                        // strong one of the comparisons will return true
                                                        // partial none of the comparisons will return true
}
