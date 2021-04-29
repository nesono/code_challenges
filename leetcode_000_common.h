#pragma once
#include <iostream>
#include <chrono>

// Can be overridden by consumer
#ifndef LEETCODE_TEST_MAX_ITERATIONS
#define LEETCODE_TEST_MAX_ITERATIONS 100000
#endif

template <class SolutionType, class InputType, class ResultType>
int testSolution(SolutionType&& solutionFunc, InputType&& input, ResultType&& expected) {
    std::cout << "Starting test with input '" << input << "'\n";
    auto result = solutionFunc(input);
    if (result != expected) {
        std::cout << "Test FAILED\n";
        std::cout << "expected: '" << expected << "'\n";
        std::cout << "result: '" << result << "'\n";
        return -1;
    }
    std::cout << "    Test succeeded\n";
    std::cout << "        result: '" << result << "'\n";

    std::cout << "    Starting benchmark\n";
    uint64_t elapsed_ms = 0ULL;
    for (auto count = 0U; count < LEETCODE_TEST_MAX_ITERATIONS; ++count) {
        auto start = std::chrono::steady_clock::now();
        auto tmp = solutionFunc(input);
        auto current = std::chrono::steady_clock::now();
        if (tmp != expected) {
            std::cout << "Result mismatch during benchmark\n";
            std::cout << "    expected: '" << expected << "'\n";
            std::cout << "    result: '" << tmp << "'\n";
        }
        elapsed_ms +=
                std::chrono::duration_cast<std::chrono::milliseconds>(
                        current - start).count();
        if (elapsed_ms >= 100) {
            std::cout << "    Timeout exceeded after    ";
            std::cout << count + 1 << " runs.\n";
            std::cout << "    Stopping benchmark.\n";
            break;
        }
    }
    std::cout << "    Total testing time elapsed_ms: " << elapsed_ms << " ms\n";
    std::cout << "Test case finished successfully \n\n";
}