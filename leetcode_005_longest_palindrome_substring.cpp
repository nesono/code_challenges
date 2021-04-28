#include <chrono>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    static bool isPalindrome(string::const_iterator front_iter,
                             string::const_iterator back_iter) {
        string helper(front_iter, back_iter + 1);
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
        string result{s[0]};
        for (string::const_iterator right_iter = std::cend(s) - 1;
             right_iter < std::cend(s); ++right_iter) {
            for (string::const_iterator front_iter = std::cbegin(s);
                 front_iter < right_iter; ++front_iter) {
                if (isPalindrome(front_iter, right_iter)) {
                    if ((right_iter - front_iter + 1) > result.size()) {
                        result = string(front_iter, right_iter + 1);
                    }
                }
            }
        }
        return result;
    }
};

void test_longestPalindrome(const string &input, const string &expected) {
    cout << "Testing longest palindrome substring  with input '" << input
         << "'\n";
    auto result = Solution::longestPalindrome(input);
    if (result != expected) {
        cout << "Test FAILED, expected: '" << expected << "' result: '"
             << result
             << "'\n";
        return;
    }
    cout << "Test succeeded, result: '" << result << "'\n";

    cout << "Starting benchmark\n";
    auto start = std::chrono::steady_clock::now();

    for (auto count = 0U; count < 1000; ++count) {
        result = Solution::longestPalindrome(input);
        auto current = std::chrono::steady_clock::now();
        auto elapsed =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                        current - start);
        if (elapsed.count() >= 400) {
            cout << "    timeout exceeded at count " << count << ". Stopping benchmark.\n";
            break;
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "    Time elapsed: " << elapsed.count() << " ms\n";
    cout << "Test case finished\n\n";
}

int main() {
    test_longestPalindrome(
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
    test_longestPalindrome(
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
    test_longestPalindrome("cbbd", "bb");
    test_longestPalindrome("a", "a");
    test_longestPalindrome("aa", "aa");
    test_longestPalindrome("aaa", "aaa");
    test_longestPalindrome("", "");
    test_longestPalindrome("babad", "bab");
    test_longestPalindrome("dabac", "aba");
    test_longestPalindrome("bad", "b");
}
