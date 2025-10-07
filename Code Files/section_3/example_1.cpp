#include "inc.hpp"

int main()
{
    std::vector<int> numbers = { 1, 2, 3 ,4, 5 };

    // DKS: STL algorithms often take two iterators, start and end...
    // Use case: initialize a container, call algorithms sequentially
    // on output from previous algorithm
    std::vector<int> evenNumbers;
    std::copy_if(numbers.begin(), numbers.end(),
       std::back_inserter(evenNumbers), [](int n){ return n % 2 == 0; });

    std::vector<int> results;
    std::transform(evenNumbers.begin(), evenNumbers.end(),
       std::back_inserter(results), [](int n){ return n * 2; });

    std::string results_str = join(results, ", ");   // DKS: Added to get around non const lval binding
    std::cout << std::vformat("\nc++98: {}\n", std::make_format_args( results_str ));

    // DKS: Note c++20 range does not have to_vector so we use the example from
    // stack overflow that I've added to inc.hpp
    /*
    auto result2 = numbers
        | std::ranges::views::filter([](int n){ return n % 2 == 0; })
        | std::ranges::views::transform([](int n){ return n * 2; })
        | std::ranges::to_vector;
    */
    auto result2 = to_vector<>( numbers
        | std::ranges::views::filter([](int n){ return n % 2 == 0; })
        | std::ranges::views::transform([](int n){ return n * 2; }) );
    // DKS: The purpose of this is to achieve in a single line what took multiple lines
    // before.

    std::string results2_str = join(result2, ", ");
    std::cout << std::vformat("\nc++20: {}\n", std::make_format_args(results2_str));
}

