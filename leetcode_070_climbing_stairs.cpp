#include <iostream>
#include <cassert>

class Solution1 {
public:
    int climbStairs(int n) {
        assert (n > 0);
        if (n <= 3) {
            return n;
        }

        int prev = 3;
        int prev2 = 2;
        int result = 0;

        for (auto i = 3; i < n; ++i) {
            result = prev + prev2;
            prev2 = prev;
            prev = result;
        }
        return result;
    }
};

int main() {
    Solution1 solution;
    std::cout << solution.climbStairs(6) << std::endl;
}