#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <functional>
#include <sstream>
#include <chrono>

// Can be overridden by consumer
#ifndef LEETCODE_TEST_MAX_ITERATIONS
#define LEETCODE_TEST_MAX_ITERATIONS 100000
#endif

//! extract the return type of a standalone function
template<typename R, typename... A>
R ret(R(*)(A...));

//! extract the return type of a member function
template<typename C, typename R, typename... A>
R ret(R(C::*)(A...));

//! build parameter string from a tuple - N > 1 generalization
template<typename TupleType, size_t N>
struct TupleToParameterString {
    static std::string toString(const TupleType& t) {
        std::ostringstream converter;
        converter << std::get<N-1>(t);
        return TupleToParameterString<TupleType, N - 1>::toString(t) + ", " +
               std::to_string(N) + ": " + converter.str();
    }
};

//! build parameter string from a tuple - N == 1 specialization
template<typename TupleType>
struct TupleToParameterString<TupleType, 1> {
    static std::string toString(const TupleType& t) {
        std::ostringstream converter;
        converter << std::get<0>(t);
        return std::string("1: ") + converter.str();
    }
};

//! convert parameters tuple to string generalization
template<typename... Args, std::enable_if_t<sizeof...(Args) == 0, int> = 0>
std::string parametersToString(const std::tuple<Args...>& t)
{
    return "";
}
//! convert parameters tuple to string size == 0 specialization
template<typename... Args, std::enable_if_t<sizeof...(Args) != 0, int> = 0>
std::string parametersToString(const std::tuple<Args...>& t)
{
    return TupleToParameterString<decltype(t), sizeof...(Args)>::toString(t);
}

template <class SolutionType, class ArgumentsType, class ExpectedType>
int testSolution(SolutionType&& solutionFunc, const ArgumentsType& input, ExpectedType&& expected) {
    std::cout << "Starting test with input '" << parametersToString(input) << "'\n";
    auto result = std::apply(solutionFunc, input);
    if (result != expected) {
        std::cout << "Test FAILED\n";
        std::cout << "expected: '" << expected << "'\n";
        std::cout << "result: '" << result << "'\n";
        return 1;
    }
    std::cout << "    Test succeeded\n";
    std::cout << "        result: '" << result << "'\n";

    std::cout << "    Starting benchmark\n";
    uint64_t elapsed_ns = 0ULL;
    auto count = 0ULL;
    for (; count < LEETCODE_TEST_MAX_ITERATIONS; ++count) {
        auto start = std::chrono::steady_clock::now();
        auto tmp = std::apply(solutionFunc, input);
        auto end = std::chrono::steady_clock::now();
        if (tmp != expected) {
            std::cout << "Result mismatch during benchmark\n";
            std::cout << "    expected: '" << expected << "'\n";
            std::cout << "    result: '" << tmp << "'\n";
        }
        elapsed_ns +=
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                        end - start).count();
        if (elapsed_ns >= 1e8) {
            std::cout << "    Timeout exceeded after    ";
            std::cout << count + 1 << " runs.\n";
            std::cout << "    Stopping benchmark.\n";
            break;
        }
    }
    std::cout << "    Total testing time elapsed_ns: " << elapsed_ns << " ns\n";
    std::cout << "Test case finished successfully \n\n";
    return 0;
}

template<typename FunctionType, typename ArgumentsType, typename OutputType>
int testMain(const std::vector<std::tuple<FunctionType, ArgumentsType, OutputType>> &testParams){
    auto sum = 0;
    for (const auto& param : testParams) {
        std::cout << "Executing Test with params: " << parametersToString(std::get<1>(param)) << "\n";
        sum += testSolution(std::get<0>(param), std::get<1>(param),
                     std::get<2>(param));
    }
    return sum;
}