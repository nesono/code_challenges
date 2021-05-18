#include <iostream>
#include <functional>
#include <tuple>

#include "leetcode_000_common.h"

using namespace std;

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

using TestParamType = vector<tuple<function<int(int)>, tuple<int>, int>>;

int main() {
    TestParamType testParams = {
            {Solution::reverse, {123}, 321},
            {Solution::reverse, {-123}, -321},
            {Solution::reverse, {0}, 0},
            {Solution::reverse, {1534236469}, 0},
            {Solution::reverse, {-2147483648}, 0}
    };
    return testMain(testParams);
}