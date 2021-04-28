#include <vector>
#include <cassert>
// #include <iostream>
using namespace std;

class Solution1 {
public:
    static int uniquePathCountHelper(vector<vector<int>>& obstacleGrid, size_t x, size_t y,
                                     size_t dim_x, size_t dim_y) {
        // return early if we found a path
        if (obstacleGrid[y][x] < 0) {
            return -obstacleGrid[y][x];
        }
        int result = 0;

        // right
        size_t right_x = x + 1;
        if (right_x <  dim_x && obstacleGrid[y][right_x] != 1)
        {
            result = uniquePathCountHelper(obstacleGrid, right_x, y, dim_x, dim_y);
        }
        // down
        size_t down_y = y + 1;
        if (down_y < dim_y && obstacleGrid[down_y][x] != 1)
        {
            result += uniquePathCountHelper(obstacleGrid, x, down_y, dim_x, dim_y);
        }

        if (x == dim_x-1 && y == dim_y-1) {
            result = 1;
        }

        obstacleGrid[y][x] = -result;
        return result;
    }

    static int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        size_t x = 0, y = 0;
        if (obstacleGrid.empty() || obstacleGrid[0].empty()) {
            return 0;
        }
        if (obstacleGrid[0][0] == 1) {
            return 0;
        }
        return uniquePathCountHelper(obstacleGrid, x, y, obstacleGrid[0].size(), obstacleGrid.size());
    }
};

int main() {
    {
        vector<vector<int>> obstacleGrid{{0, 0, 0},
                                         {0, 1, 0},
                                         {0, 0, 0}};
        assert(Solution1::uniquePathsWithObstacles(obstacleGrid) == 2);
    }
    {
        vector<vector<int>> obstacleGrid{{0, 1},
                                         {0, 0}};
        assert(Solution1::uniquePathsWithObstacles(obstacleGrid) == 1);
    }
    {
        vector<vector<int>> obstacleGrid{{1}};
        assert(Solution1::uniquePathsWithObstacles(obstacleGrid) == 0);
    }
    {
        vector<vector<int>> obstacleGrid{{0,0}};
        assert(Solution1::uniquePathsWithObstacles(obstacleGrid) == 1);
    }
    {
        vector<vector<int>> obstacleGrid{{}};
        assert(Solution1::uniquePathsWithObstacles(obstacleGrid) == 0);
    }
    {
        vector<vector<int>> obstacleGrid{{1,0}};
        assert(Solution1::uniquePathsWithObstacles(obstacleGrid) == 0);
    }
    {
        vector<vector<int>> obstacleGrid{{0,0,0,0},{0,1,0,0},{0,0,0,0},{0,0,1,0},{0,0,0,0}};
        assert(Solution1::uniquePathsWithObstacles(obstacleGrid) == 7);
    }

    return 0;
}