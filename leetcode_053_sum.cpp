#include <iostream>
#include <vector>
#include <numeric>

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

int main() {
    vector<int> nums{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << Solution1::maxSubArray(nums) << std::endl;
}