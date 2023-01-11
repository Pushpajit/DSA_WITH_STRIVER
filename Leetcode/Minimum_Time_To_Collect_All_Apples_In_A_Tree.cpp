/*
leetcode:
     https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/description/

*/



class Solution {
    int dfs(vector<vector<int>>& adj, int ind, vector<bool>& hasApple, vector<int> &vis) {
        // Initialize time = 0
        int time = 0;

        // Mark current node as visited.
        vis[ind] = true;

        for (int node : adj[ind]) {
            // If the node is not visited yet.
            if (!vis[node]) {
                int res = dfs(adj, node, hasApple, vis);
                // If any children contains apple then take the edge(i.e path) and add +1 sec.
                if (res)
                    time += (1 + res);
            }

        }

        // If cuurent vertex's children contains apple then take the edge(i.e path).
        if (time)
            // For vertex 0, no need to add the time  because it's the top vertex and take 0 sec.
            // Else add +1 time for walking over the edge every time.
            return (ind == 0 ? time : time + 1);
        else
            // Similarly if vertex 0 has an apple or no apple every case it will take 0 sec.
            // For other vertex it will take 1 sec.
            return (ind == 0 ? 0 : hasApple[ind]);
    }
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        vector<vector<int>> adj(n);
        vector<int> vis(n);

        // Make undirected adjacent list
        for (auto vec : edges) {
            adj[vec[0]].push_back(vec[1]);
            adj[vec[1]].push_back(vec[0]);
        }

        return dfs(adj, 0, hasApple, vis);

    }
};