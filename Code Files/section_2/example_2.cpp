#include "inc.hpp"

using std::string;
using std::cout;
using std::endl;

struct Person
{
    int id;
    std::string name;
};

std::ostream &operator<<(std::ostream &os, const Person &p)
{
    os << "Person: " << p.name << " (" << p.id << ")";
    return os;
}

// DKS: Needed to add a template specialization of std::formatter, see e.g.
// https://stackoverflow.com/questions/77958416/customize-formatter-with-abstraction
// I'm not sure why the ostream did not work.

template <>
struct std::formatter<Person> : formatter<std::string>
{
    auto format(Person p, format_context &ctx) const
    {
        return formatter<std::string>::format("Person: " + p.name + " (" + std::to_string(p.id) + ")", ctx);
    }
};

int main()
{
    Person p = {1, "John"};

    printf("Person: %s (%d)\n", p.name.c_str(), p.id);
    cout << p << std::endl;
    cout << std::vformat("{}", std::make_format_args(p)) << std::endl;  // DKS: switch to vformat
}
