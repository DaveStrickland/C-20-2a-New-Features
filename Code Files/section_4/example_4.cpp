#include <inc.hpp>
#include <compare>

struct InternalT
{
    int v;
    constexpr InternalT(int v) : v{v} {}

    // DKS: You might define your own operators in cases of types where some
    // optimization is possible, e.g strings you can check string length
    // before doing character by character comparison, etc.
    auto operator <=>(const InternalT& rhs) const   // DKS: User-defined <=> operator instead of compiler...
    {
        cout << "called <=> with: " << v << ", " << rhs.v << endl;
        return v <=> rhs.v;
    }
    auto operator==(const InternalT& rhs) const     // DKS: ...so user MUST also define an equality operator
    {
        cout << "called == with: " << v << ", " << rhs.v << endl;
        return v == rhs.v;
    }
};

struct MyValue
{
    InternalT v;
    constexpr MyValue(int v) : v{v} {}
    auto operator <=>(const MyValue&) const = default;
};

int main()
{
    MyValue iw1{3};
    MyValue iw2{3};

    bool twc = (iw1 <=> iw2 == 0);
    bool eqc = (iw1 == iw2);

    cout << "three way equality: " << twc << endl;
    cout << "two way equality: " << eqc << endl;
}
