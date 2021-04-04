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

        std::unordered_set<char> seenChars;
        int result = 0;

        for (const auto& c : s) {
            if (seenChars.find(c) != seenChars.end()) {
                seenChars.clear();
            }
            seenChars.insert(c);
            result = std::max(result, static_cast<int>(seenChars.size()));

        }
        return result;

    }
};


int main() {
     std::cout << "Solution for dvdf (3): " << Solution::lengthOfLongestSubstring("dvdf") << std::endl;

}