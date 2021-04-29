#include <string>

#include "leetcode_000_common.h"

using namespace std;

class Solution {
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
