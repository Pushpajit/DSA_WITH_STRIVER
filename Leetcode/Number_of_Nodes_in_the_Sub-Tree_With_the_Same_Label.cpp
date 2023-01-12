/*
    leetcode:
        https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/description/

*/


#define um unordered_map

class Solution {
    um<char, int> dfs(vector<vector<int>> &adj, int ind, vector<int> &ans, string &labels, vector<int> &vis) {

        um<char, int> hsh;
        // Insert labels[ind] into hashmap.
        hsh[labels[ind]]++;

        // Mark current node as visited.
        vis[ind] = true;

        // Go to all subtree on current node.
        for (int node : adj[ind]) {

            // If node is not visited.
            if (!vis[node]) {
                // Go to all child nodes and calculate the frequency of the char.
                auto res = dfs(adj, node, ans, labels, vis);

                // After calculating, merge the 'res' hash into the 'hsh' .
                for (auto p : res)
                    hsh[p.first] += p.second;
            }
        }

        // So after that, the hsh will store the total number of nodes in the sub-tree with the
        // same label. Just assign it to ans[ind] .

        ans[ind] = hsh[labels[ind]];


        // Return the merged hash to it's parent.
        return hsh;
    }

public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string &labels) {
        vector<vector<int>> adj(n);
        vector<int> ans(n);
        vector<int> vis(n);

        // Making adjacency list .
        for (auto vec : edges) {
            adj[vec[0]].push_back(vec[1]);
            adj[vec[1]].push_back(vec[0]);
        }


        dfs(adj, 0, ans, labels, vis);

        return ans;
    }
};