#include <iostream>

#include "leetcode_000_common.h"

class Solution {
public:
    static int reverse(int x) {
        if (x == std::numeric_limits<int>::min()) {
            return 0;
        }
        if (x < 0 ) {
            return -reverse(-x);
        }

        int result = 0;
        while (x > 0) {
            int64_t tmp = static_cast<int64_t>(result) * 10LL + x % 10;
            if (tmp > std::numeric_limits<int>::max()) {
                return 0;
            }
            result = static_cast<int>(tmp);
            x = x / 10;
        }
        return result;
    }
};

int main() {
    testSolution(Solution::reverse, 123, 321);
    testSolution(Solution::reverse, -123, -321);
    testSolution(Solution::reverse, 0, 0);
    testSolution(Solution::reverse,
                 1534236469, 0);
    testSolution(Solution::reverse, -2147483648, 0);
}