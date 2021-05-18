#include <string>
#include <iostream>


#include "leetcode_000_common.h"

// define variadic template struct to contain parameters
auto parameters = std::make_tuple(1, 2.0, std::string("j"));

class MockSolution {
public:
    static std::string to_string(int a, double b, const std::string &c){
        return (std::string("a: ") + std::to_string(a) +
                ", b: " + std::to_string(b) +
                ", c: ").append(c);
    }
};

int main() {
    std::cout << "Simple callWithTuple: " << MockSolution::to_string(1, 2.0, "j")
              << "\n";
    std::cout << "Print parameters: " << parametersToString(parameters) << "\n";
    std::cout << "Template callWithTuple: " << testSolution(
            MockSolution::to_string, parameters, "a: 1, b: 2, c: j")
              << "\n";
    return 0;
}