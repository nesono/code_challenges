#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "leetcode_000_common.h"

using namespace std;

class Solution1 {
public:
  static uint32_t getFirstRowOffset(uint32_t numRows) {
    if (numRows == 1) {
      return 1;
    } else {
      return (numRows - 1) * 2;
    }
  }

  static string convert(const string &s, uint32_t numRows) {
    string result;
    result.resize(s.size());

    uint32_t even_row_offset = getFirstRowOffset(numRows);
    uint32_t odd_row_offset = 0;

    uint32_t out_idx = 0;

    for (uint32_t r = 0U; r < numRows; ++r) {
      uint32_t idx = r;
      while (idx < s.size()) {
        if (even_row_offset != 0 && idx < s.size()) {
          result[out_idx++] = s[idx];
          idx += even_row_offset;
        }
        if (odd_row_offset != 0 && idx < s.size()) {
          result[out_idx++] = s[idx];
          idx += odd_row_offset;
        }
      }
      even_row_offset -= 2;
      odd_row_offset += 2;
    }
    return result;
  }
};

using TestParamType =
    vector<tuple<function<string(const string &, int)>,
                 const tuple<const string &, int>, const string &>>;

int main() {
  const string input{"PAYPALISHIRING"};
  TestParamType params = {{Solution1::convert, {input, 3}, "PAHNAPLSIIGYIR"},
                          {Solution1::convert, {input, 4}, "PINALSIGYAHRPI"}};
  return testMain(params);
}
