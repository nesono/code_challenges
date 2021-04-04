#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    static int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }

        size_t left = 0;
        size_t result = 1;
        size_t count = 1;

        for (size_t right = 1; right < s.size(); ++right) {
            for (size_t idx = left; idx < right; ++idx) {
                if (s[idx] != s[right]) {
                    ++count;
                } else {
                    left = idx + 1;
                    break;
                }
            }
            result = std::max(result, count);
            count = 1;

        }
        return result;
    }
};


int main() {
    std::cout << "Solution for abcabcbb (3): " << Solution::lengthOfLongestSubstring("abcabcbb") << std::endl;
    std::cout << "Solution for bbbbb (1): " << Solution::lengthOfLongestSubstring("bbbbb") << std::endl;
    std::cout << "Solution for pwwkew (3): " << Solution::lengthOfLongestSubstring("pwwkew") << std::endl;
    std::cout << "Solution for '' (0): " << Solution::lengthOfLongestSubstring("") << std::endl;
    std::cout << "Solution for dvdf (3): " << Solution::lengthOfLongestSubstring("dvdf") << std::endl;
}