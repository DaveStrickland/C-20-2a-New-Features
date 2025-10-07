#include "inc.hpp"

int main()
{
    int n = 10;
    auto square_fn = [](int x){ return x * x;};

    std::vector<int> input(static_cast<size_t>(n));
    std::iota(input.begin(), input.end(), 0);
    std::vector<int> results;
    std::transform(input.begin(),input.end(),
        std::back_inserter(results), square_fn);

    std::string results_str = join(results, ", ");
    std::cout << std::vformat("\nc++98: {}\n", std::make_format_args(results_str));

    // auto result2 = std::ranges::views::iota(0, n)
    //     | std::ranges::views::transform(square_fn);

    // DKS: std::range::views::iota creates an iota_view, not a vector
    auto result2 =  std::ranges::views::iota(0, n)
        | std::ranges::views::transform(square_fn);
       
    // DKS: we don't have to use the | chaining, we could just use normal
    // function nesting.
    // auto result2 =
    //     std::ranges::views::transform(std::ranges::views::iota(0, n), square_fn);

    // In C++20 we can't use the C++23 std::range::to method, so we have to do this
    std::vector<int> result2_vec(std::begin(result2), std::end(result2));
    std::string result2_str = join(result2_vec, ", ");   // Standard lvalue fix
    std::cout << std::vformat("\nc++20: {}\n", std::make_format_args(result2_str));
}
