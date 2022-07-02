#include <cassert>
#include <cstdint>
#include <functional>
#include <string>
#include <tuple>
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
    for (size_t gap_size = 0U; gap_size < s.size() - 1; ++gap_size) {
      // create longest palindrome candidates with size s.size()-gap_size
      for (size_t offset = 0U; offset <= gap_size; ++offset) {
        // if palindrome found, return it
        if (isPalindrome(begin(s) + offset, end(s) - 1 - (gap_size - offset))) {
          return string(begin(s) + offset, end(s) - (gap_size - offset));
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
  static string expand(const string &s) {
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
    // make sure there is no overflow below
    assert(ex_s.size() <= std::numeric_limits<int64_t>::max());
    int64_t ex_s_size = static_cast<int64_t>(ex_s.size());

    std::vector<size_t> palindromeRadii{ex_s.size()};
    palindromeRadii.resize(ex_s_size);
    int64_t center = 0;

    while (center < ex_s_size) {
      int64_t radius = 0;
      while (center - (radius + 1) >= 0 && center + (radius + 1) < ex_s_size &&
             ex_s[center - (radius + 1)] == ex_s[center + (radius + 1)]) {
        ++radius;
      }
      palindromeRadii[center] = radius;
      ++center;
    }

    std::vector<size_t>::iterator max_elem = std::max_element(
        std::begin(palindromeRadii), std::end(palindromeRadii));
    auto centerInExs = std::distance(std::begin(palindromeRadii), max_elem);
    auto centerInS = (centerInExs - 1) / 2;
    auto longestRadiusInExS = *max_elem;
    auto longestRadiusInS = (longestRadiusInExS - 1) / 2;
    return s.substr(centerInS - longestRadiusInS, longestRadiusInExS);
  }

  static string longestPalindromeManacher(const string &s) {
    if (1 >= s.size()) {
      return s;
    }
    // expand string
    auto ex_s = expand(s);
    // make sure there is no overflow below
    assert(ex_s.size() <= std::numeric_limits<int64_t>::max());
    int64_t ex_s_size = static_cast<int64_t>(ex_s.size());

    // implement Manacher's algorithm
    std::vector<size_t> palindromeRadii{ex_s.size()};
    palindromeRadii.resize(ex_s_size);
    int64_t center = 0;
    int64_t radius = 0;

    while (center < ex_s_size) {
      while (center - (radius + 1) >= 0 && center + (radius + 1) < ex_s_size &&
             ex_s[center - (radius + 1)] == ex_s[center + (radius + 1)]) {
        ++radius;
      }
      palindromeRadii[center] = radius;

      auto oldCenter = center;
      auto oldRadius = radius;
      ++center;
      radius = 0;
      while (center <= oldCenter + oldRadius) {
        auto mirroredCenter = oldCenter - (center - oldCenter);
        auto maxMirroredRadius = oldRadius - (center - oldCenter);
        if (static_cast<int64_t>(palindromeRadii[mirroredCenter]) <
            maxMirroredRadius) {
          palindromeRadii[center] = palindromeRadii[mirroredCenter];
          ++center;
        } else if (static_cast<int64_t>(palindromeRadii[mirroredCenter]) >
                   maxMirroredRadius) {
          palindromeRadii[center] = maxMirroredRadius;
          ++center;
        } else { // palindromeRadii[mirroredCenter] == maxMirroredRadius
          radius = maxMirroredRadius;
          break;
        }
      }
    }

    std::vector<size_t>::iterator max_elem = std::max_element(
        std::begin(palindromeRadii), std::end(palindromeRadii));
    auto centerInExs = std::distance(std::begin(palindromeRadii), max_elem);
    auto centerInS = (centerInExs - 1) / 2;
    auto longestRadiusInExS = *max_elem;
    auto longestRadiusInS = (longestRadiusInExS - 1) / 2;
    return s.substr(centerInS - longestRadiusInS, longestRadiusInExS);
  }
};

class Solution3 {
public:
  // expand string to be odd sized pertaining it's symmetry
  static string expand(const string &s) {
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
    // make sure there is no overflow below
    assert(ex_s.size() <= std::numeric_limits<int64_t>::max());
    int64_t ex_s_size = static_cast<int64_t>(ex_s.size());

    // implement Manacher's algorithm
    std::vector<size_t> palindromeRadii{ex_s.size()};
    palindromeRadii.resize(ex_s.size());
    int64_t center = 0;
    int64_t radius = 0;

    while (center < ex_s_size) {
      while (center - (radius + 1) >= 0 && center + (radius + 1) < ex_s_size &&
             ex_s[center - (radius + 1)] == ex_s[center + (radius + 1)]) {
        ++radius;
      }
      palindromeRadii[center] = radius;

      auto oldCenter = center;
      auto oldRadius = radius;
      ++center;
      radius = 0;
      while (center <= oldCenter + oldRadius) {
        auto mirroredCenter = oldCenter - (center - oldCenter);
        auto maxMirroredRadius = oldRadius - (center - oldCenter);
        if (static_cast<int64_t>(palindromeRadii[mirroredCenter]) <
            maxMirroredRadius) {
          palindromeRadii[center] = palindromeRadii[mirroredCenter];
          ++center;
        } else if (static_cast<int64_t>(palindromeRadii[mirroredCenter]) >
                   maxMirroredRadius) {
          palindromeRadii[center] = maxMirroredRadius;
          ++center;
        } else { // palindromeRadii[mirroredCenter] == maxMirroredRadius
          radius = maxMirroredRadius;
          break;
        }
      }
    }

    auto max_elem = std::max_element(std::begin(palindromeRadii),
                                     std::end(palindromeRadii));
    auto centerInExs = std::distance(std::begin(palindromeRadii), max_elem);
    auto centerInS = (centerInExs - 1) / 2;
    auto longestRadiusInExS = *max_elem;
    auto longestRadiusInS = (longestRadiusInExS - 1) / 2;
    return s.substr(centerInS - longestRadiusInS, longestRadiusInExS);
  }
};

using Solution = Solution3;

int main() {
  auto params = vector<
      tuple<function<string(const string)>, tuple<const string>, string>>{
      {Solution::longestPalindrome,
       {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabc"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"},
       {"aaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}},
      {Solution::longestPalindrome,
       {"civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicated"
        "ca"
        "nlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpat"
        "ea"
        "portionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivestha"
        "tt"
        "hatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinal"
        "ar"
        "gersensewecannotdedicatewecannotconsecratewecannothallowthisgroundTheb"
        "ra"
        "velmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorpon"
        "we"
        "rtoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayher"
        "eb"
        "utitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicated"
        "he"
        "retotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvanced"
        "It"
        "isratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfro"
        "mt"
        "hesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethela"
        "st"
        "pfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothave"
        "di"
        "edinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgover"
        "nm"
        "entofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth"},
       {"ranynar"}},
      {Solution::longestPalindrome, {"cbbd"}, {"bb"}},
      {Solution::longestPalindrome, {"a"}, {"a"}},
      {Solution::longestPalindrome, {"aa"}, {"aa"}},
      {Solution::longestPalindrome, {"aaa"}, {"aaa"}},
      {Solution::longestPalindrome, {""}, {""}},
      {Solution::longestPalindrome, {"babad"}, {"bab"}},
      {Solution::longestPalindrome, {"dabac"}, {"aba"}},
      {Solution::longestPalindrome, {"bad"}, {"b"}},
  };
  return testMain(params);
}
