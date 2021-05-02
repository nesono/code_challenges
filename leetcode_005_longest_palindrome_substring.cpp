#include <string>
#include <utility>
#include <vector>

#include "leetcode_000_common.h"

using namespace std;

class Solution1 {
public:
    static bool isPalindrome(string::const_iterator front_iter,
                             string::const_iterator back_iter) {
        while (front_iter < back_iter) {
            if (*(front_iter++) != *(back_iter--)) {
                return false;
            }
        }
        return true;
    }

    static string longestPalindrome(const string &s) {
        if (1 >= s.size()) {
            return s;
        }
        // increase the gap from 0 until s.size()-1 -- a single char palindrome
        for (size_t gap_size = 0U; gap_size < s.size()-1; ++gap_size)
        {
            // create longest palindrome candidates with size s.size()-gap_size
            for (size_t offset = 0U; offset <= gap_size; ++offset) {
                // if palindrome found, return it
                if (isPalindrome(begin(s)+offset, end(s)-1-(gap_size-offset))) {
                    return string(begin(s)+offset, end(s)-(gap_size-offset));
                }
            }
        }
        // return first character if nothing found
        return string{s[0]};
    }
};

class Solution2 {
public:
    // expand string to be odd sized pertaining it's symmetry
    static string expand(const string& s) {
        string result;
        result.reserve(s.size() * 2 + 1);
        result.push_back('|');
        for (auto c : s) {
            result.push_back(c);
            result.push_back('|');
        }
        return result;
    }

    static string longestPalindrome(const string &s) {
        if (1 >= s.size()) {
            return s;
        }
        // expand string
        auto ex_s = expand(s);
        // implement Manacher's algorithm
        std::vector<size_t> palindromeRadii{ex_s.size()};
        palindromeRadii.resize(ex_s.size());
        int64_t center = 0;

        while (center < ex_s.size()) {
            int64_t radius = 0;
            while ( center-(radius+1) >= 0 &&
                    center+(radius+1) < ex_s.size() &&
                    ex_s[center-(radius+1)] == ex_s[center+(radius+1)] ) {
                ++radius;
            }
            palindromeRadii[center] = radius;
            ++center;
        }

        std::vector<size_t>::iterator max_elem = std::max_element(std::begin(palindromeRadii),
                                         std::end(palindromeRadii));
        auto centerInExs = std::distance(std::begin(palindromeRadii), max_elem);
        auto centerInS = (centerInExs - 1)/2;
        auto longestRadiusInExS = *max_elem;
        auto longestRadiusInS = (longestRadiusInExS-1) / 2;
        return s.substr(centerInS-longestRadiusInS, longestRadiusInExS);
    }

    static string longestPalindromeManacher(const string &s) {
        if (1 >= s.size()) {
            return s;
        }
        // expand string
        auto ex_s = expand(s);
        // implement Manacher's algorithm
        std::vector<size_t> palindromeRadii{ex_s.size()};
        palindromeRadii.resize(ex_s.size());
        int64_t center = 0;
        int64_t radius = 0;

        while (center < ex_s.size()) {
            while ( center-(radius+1) >= 0 &&
                    center+(radius+1) < ex_s.size() &&
                    ex_s[center-(radius+1)] == ex_s[center+(radius+1)] ) {
                ++radius;
            }
            palindromeRadii[center] = radius;

            auto oldCenter = center;
            auto oldRadius = radius;
            ++center;
            radius = 0;
            while (center <= oldCenter+oldRadius) {
                auto mirroredCenter = oldCenter - (center - oldCenter);
                auto maxMirroredRadius = oldRadius - (center - oldCenter);
                if (palindromeRadii[mirroredCenter] < maxMirroredRadius) {
                    palindromeRadii[center] = palindromeRadii[mirroredCenter];
                    ++center;
                }
                else if (palindromeRadii[mirroredCenter] > maxMirroredRadius) {
                    palindromeRadii[center] = maxMirroredRadius;
                    ++center;
                }
                else { // palindromeRadii[mirroredCenter] == maxMirroredRadius
                    radius = maxMirroredRadius;
                    break;
                }
            }
        }

        std::vector<size_t>::iterator max_elem = std::max_element(std::begin(palindromeRadii),
                                                                  std::end(palindromeRadii));
        auto centerInExs = std::distance(std::begin(palindromeRadii), max_elem);
        auto centerInS = (centerInExs - 1)/2;
        auto longestRadiusInExS = *max_elem;
        auto longestRadiusInS = (longestRadiusInExS-1) / 2;
        return s.substr(centerInS-longestRadiusInS, longestRadiusInExS);
    }
};

class Solution3 {
public:
    // expand string to be odd sized pertaining it's symmetry
    static string expand(const string& s) {
        string result;
        result.reserve(s.size() * 2 + 1);
        result.push_back('|');
        for (auto c : s) {
            result.push_back(c);
            result.push_back('|');
        }
        return result;
    }

    static string longestPalindrome(const string &s) {
        if (1 >= s.size()) {
            return s;
        }
        // expand string
        auto ex_s = expand(s);
        // implement Manacher's algorithm
        std::vector<size_t> palindromeRadii{ex_s.size()};
        palindromeRadii.resize(ex_s.size());
        int64_t center = 0;
        int64_t radius = 0;

        while (center < ex_s.size()) {
            while ( center-(radius+1) >= 0 &&
                    center+(radius+1) < ex_s.size() &&
                    ex_s[center-(radius+1)] == ex_s[center+(radius+1)] ) {
                ++radius;
            }
            palindromeRadii[center] = radius;

            auto oldCenter = center;
            auto oldRadius = radius;
            ++center;
            radius = 0;
            while (center <= oldCenter+oldRadius) {
                auto mirroredCenter = oldCenter - (center - oldCenter);
                auto maxMirroredRadius = oldRadius - (center - oldCenter);
                if (palindromeRadii[mirroredCenter] < maxMirroredRadius) {
                    palindromeRadii[center] = palindromeRadii[mirroredCenter];
                    ++center;
                }
                else if (palindromeRadii[mirroredCenter] > maxMirroredRadius) {
                    palindromeRadii[center] = maxMirroredRadius;
                    ++center;
                }
                else { // palindromeRadii[mirroredCenter] == maxMirroredRadius
                    radius = maxMirroredRadius;
                    break;
                }
            }
        }

        auto max_elem = std::max_element(std::begin(palindromeRadii),
                                         std::end(palindromeRadii));
        auto centerInExs = std::distance(std::begin(palindromeRadii), max_elem);
        auto centerInS = (centerInExs - 1)/2;
        auto longestRadiusInExS = *max_elem;
        auto longestRadiusInS = (longestRadiusInExS-1) / 2;
        return s.substr(centerInS-longestRadiusInS, longestRadiusInExS);
    }
};

using Solution = Solution3;
int main() {
    testSolution( Solution::longestPalindrome,
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
            "aaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    testSolution( Solution::longestPalindrome,
            "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedca"
            "nlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpatea"
            "portionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatt"
            "hatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalar"
            "gersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebra"
            "velmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwe"
            "rtoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayhereb"
            "utitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedhe"
            "retotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedIt"
            "isratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromt"
            "hesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelast"
            "pfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavedi"
            "edinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernm"
            "entofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth",
            "ranynar");
    testSolution( Solution::longestPalindrome,"cbbd", "bb");
    testSolution( Solution::longestPalindrome,"a", "a");
    testSolution( Solution::longestPalindrome,"aa", "aa");
    testSolution( Solution::longestPalindrome,"aaa", "aaa");
    testSolution( Solution::longestPalindrome,"", "");
    testSolution( Solution::longestPalindrome,"babad", "bab");
    testSolution( Solution::longestPalindrome,"dabac", "aba");
    testSolution( Solution::longestPalindrome,"bad", "b");
}
