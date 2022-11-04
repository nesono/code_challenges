#include <iostream>
#include <vector>
#include <numeric>

#include <range/v3/numeric/algorithm.hpp>
#include <range/v3/view/transform.hpp>

using namespace std;

class Solution1 {
public:
    // implementation using Kadane's algorithm
    static int maxSubArray(vector<int>& nums) {
        int maxSum = nums[0];

        for (auto idx = 1U; idx < nums.size(); ++idx) {
            if (nums[idx-1] > 0) {
                nums[idx] += nums[idx-1];
            }
            maxSum = std::max(maxSum, nums[idx]);
        }
        return maxSum;
    }
};

class Solution2 {
public:
    // implementation using Kadane's algorithm
    static int maxSubArray(vector<int>& nums) {
        return ranges::max(nums | ranges::views::sliding(2) | ranges::views::transform());
    }
};

int main() {
    vector<int> nums{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << Solution1::maxSubArray(nums) << std::endl;
}