#include <vector>
#include <string>
#include <iostream>
#include <tuple>

#include "leetcode_000_common.h"

using namespace std;

class Solution1 {
public:
    static int getFirstRowOffset(int numRows) {
        if (numRows == 1) {
            return 1;
        }
        else {
            return (numRows-1) * 2;
        }
    }

    static string convert(const string& s, int numRows) {
        string result;
        result.resize(s.size());

        int even_row_offset = getFirstRowOffset(numRows);
        int odd_row_offset = 0;

        int out_idx = 0;

        for (int r = 0; r < numRows; ++r) {
            int idx = r;
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

using TestParamType = vector<tuple<function<string(const string&, int)>, const tuple<const string&, int>, const string&>>;

int main() {
    const string input{"PAYPALISHIRING"};
    TestParamType params = {
            {Solution1::convert, {input, 3}, "PAHNAPLSIIGYIR"},
            {Solution1::convert, {input, 4}, "PINALSIGYAHRPI"}
    };
    return testMain(params);
}