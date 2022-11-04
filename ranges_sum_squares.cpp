//
// Created by ji on 11/3/22.
//
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <vector>
#include <span>
#include <iostream>

void print(const std::vector<int>& v) {
    copy(begin(v), end(v),
         std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

int main() {
    auto const square = [](int i){ return i*i; };
    auto const vec = std::vector<int>{-1, 1, 0, 2, 4};
    const auto sum = ranges::accumulate(vec | ranges::views::transform(square), 0);

    std::cout << "Input\n";
    print(vec);
    std::cout << "Sum: " << sum << "\n";

    return 0;
}