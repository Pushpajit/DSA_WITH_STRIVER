/*
    leetcode:
        https://leetcode.com/problems/as-far-from-land-as-possible/description/
*/

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        // This problem is exactly same as
        // (Distance of nearest cell having 1 in 0/1 matrix STRIVER G-13 GRAPH)

        int n = grid.size();
        int maxDis = 0;
        queue<vector<int>> wait;
        vector<vector<int>> vis(n, vector<int>(n));

        // Push all 1's cell location and dis into queue. (i.e [i,j,0])
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    wait.push({i, j, 0});
                    vis[i][j] = 1;
                }
            }
        }


        // BFS
        while (!wait.empty()) {
            int m = wait.size();

            for (int _ = 0; _ < m; _++) {

                // Taking the front elemtns from the Queue.
                int i = wait.front()[0];
                int j = wait.front()[1];
                int dis = wait.front()[2];

                // Updating the maxDis
                maxDis = max(maxDis, dis);

                // Pop the elelement from the Queue.
                wait.pop();

                // Go UP and marks the cell as visited.
                if (i > 0 && !vis[i - 1][j]) {
                    wait.push({i - 1, j, dis + 1});
                    vis[i - 1][j] = 1;
                }

                // Go DOWN and marks the cell as visited.
                if (i < n - 1 && !vis[i + 1][j]) {
                    wait.push({i + 1, j, dis + 1});
                    vis[i + 1][j] = 1;
                }

                // Go LEFT and marks the cell as visited.
                if (j > 0 && !vis[i][j - 1]) {
                    wait.push({i, j - 1, dis + 1});
                    vis[i][j - 1] = 1;
                }

                // Go RIGHT and marks the cell as visited.
                if (j < n - 1 && !vis[i][j + 1]) {
                    wait.push({i, j + 1, dis + 1});
                    vis[i][j + 1] = 1;
                }
            }
        }

        // It means there is no land/water.
        if (maxDis == 0)
            return -1;

        return maxDis;


    }
};