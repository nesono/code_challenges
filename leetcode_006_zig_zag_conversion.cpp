#include <vector>
#include <string>
#include <iostream>

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

bool test_convert(const string& input, int row_count, const string& expected) {
    cout << "\nTesting " << input << " row count: " << row_count << "\n";
    auto result = Solution1::convert(input, row_count);
    if (result != expected) {
        cout << "Test failed! expected: " << expected << " result: " << result << "\n";
        return false;
    }
    cout << "Test succeeded!\n";
    return true;
}
int main() {
    const string input{"PAYPALISHIRING"};
    // Input: s = "PAYPALISHIRING", numRows = 3
    // Output: "PAHNAPLSIIGYIR"
    test_convert(input, 3, "PAHNAPLSIIGYIR");
    test_convert(input, 4, "PINALSIGYAHRPI");
}