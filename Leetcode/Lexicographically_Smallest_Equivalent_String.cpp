/*
    leetcode:
        https://leetcode.com/problems/lexicographically-smallest-equivalent-string/description/

*/

class Solution {
    char dfs(unordered_map<char, vector<char>> &adj, char curr, vector<int> &vis) {
        // Initialize current node as minimum.

        char MIN = curr;
        // Mark current node as visited.
        vis[curr - 'a'] = true;

        // Simple dfs call for all neighbour.
        for (auto node : adj[curr]) {

            if (!vis[node - 'a'])
                MIN = min(MIN, dfs(adj, node, vis));

        }

        return MIN;
    }

public:
    string smallestEquivalentString(string &s1, string &s2, string &baseStr) {
        int n = s1.size();
        string ans = "";
        unordered_map<char, vector<char>> adj;

        // Making adj list.
        for (int i = 0; i < n; i++) {
            adj[s1[i]].push_back(s2[i]);
            adj[s2[i]].push_back(s1[i]);
        }


        // Go thouch every char of baseStr and find the minimum for that char.
        for (int i = 0; i < baseStr.size(); i++) {
            // visited array of size 26 for a-z
            vector<int> vis(26);

            // Add minimum char to the answer.
            ans += dfs(adj, baseStr[i]o, vis);
        }

        return ans;

    }
};