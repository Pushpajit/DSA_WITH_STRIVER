/*
    leetcode:
        https://leetcode.com/problems/longest-path-with-different-adjacent-characters/description/

*/


class Solution {
    int dfs(vector<vector<int>> &adj, int ind, vector<int> &vis, vector<int>& p, string &s, int &ans) {
        // Mark current node as visited.
        vis[ind] = true;

        // For storing the max 2 branch which has maximum length.
        int max1, max2;
        max1 = max2 = 0;

        for (int node : adj[ind]) {
            if (!vis[node]) {
                // Go to the branches and calculate the length.
                int len = dfs(adj, node, vis, p, s, ans);

                // Update max1 with len and max2 with max1
                if (len >= max1) {
                    max2 = max1;
                    max1 = len;
                }
                else // Else keep max2 updated.
                    max2 = max(max2, len); // We also want max2 as max as possible
            }
        }

        ans = max(ans, max1 + max2 + 1); // Update the answer with max diameter.

        // If child and parent has the same label then cut that path and return 0
        if (ind != 0 && s[ind] == s[p[ind]])
            return 0;
        else
            return max1 + 1; // Between multiple branches of a tree we chose the largest one

    }

public:
    int longestPath(vector<int>& p, string &s) {
        vector<vector<int>> adj(p.size());
        vector<int> vis(p.size());
        int ans = INT_MIN;

        // Make adj list
        for (int i = 1; i < p.size(); i++) {
            adj[p[i]].push_back(i);
            adj[i].push_back(p[i]);
        }

        dfs(adj, 0, vis, p, s, ans);

        return ans;
    }
};