#include <iostream>
#include <vector>

using namespace std;


vector<int> bfsOfGraph(int V, vector<vector<int>> &adj) {
	vector<int> visited(V + 1, 0); //For checking if the node is visited or not.
	vector<int> bfs; //For storing the answer.
	visited[0] = 1; //Mark the 1st node checked.
	queue<int> wait;
	wait.push(0); //Push the 1st node into the queue.

	while (!wait.empty()) {
		int node = wait.front();
		wait.pop();
		bfs.push_back(node); //Store the poped node into the bfs answer array.

		for (int i : adj[node]) { //Travers all the connected neighbour nodes.
			if (visited[i] == 0) { //If the neighbour node are not checked,
				wait.push(i); //Push the neighbour node into the queue.
				visited[i] = 1; //Mark the neighbour node checked.
			}
		}
	}

	return bfs;
}// TC = O(n) + O(2E) [number of nodes + Total degree of the graph]
//  SC = O(n)




vector<int> ans; //For storing the output.
void dfs(vector<int> adj[], int node, int visited[]) {
	ans.push_back(node); //Store the current node data.

	visited[it] = 1; //Mark it as 1 (i.e visited)

	for (auto it : adj[node]) {// Traverse over all the neighbours of the current node.
		if (visited[it] == 0) {// If the neighbour is not visited only then call the dfs for that neighbour.
			dfs(adj, it, visited);
		}
	}
}
//SC => O(n) + O(n) + O(n) [ans + visited + stack space]
//TC => O(n) + O(2E)

vector<int> dfsOfGraph(int V, vector<int> adj[]) {
	int visited[V] = {0}; //Make a visited array.
	visited[0] = 1; //1st node is visited.
	dfs(adj, 0, visited);
	return ans;
}

class Provinces {
public:
	void DFS(vector<vector<int>> &list, int node,  vector<int> &visited) {
		visited[node] = 1;

		for (int i : list[node]) {
			if (visited[i] == 0)
				DFS(list, i, visited);
		}
	}//O(N + 2E)

	int numProvinces(vector<vector<int>> adj, int V) {
		vector<int> visited(V, 0);
		vector<vector<int>> list(V);

		//convert adjacency matrix into adjacency list.
		for (int i = 0; i < adj.size(); i++) {
			for (int j = 0; j < adj[i].size(); j++) {
				if (adj[i][j] && j != i) {
					list[i].push_back(j);
				}
			}
		}

		int provinces = 0;
		//Count total no of components.
		for (int i = 0; i < adj.size(); i++) {
			if (visited[i] == 0) { //check if current node is a separate component or what.
				DFS(list, i, visited); //call dfs over all the components root node.
				provinces++;
			}
		}

		return provinces;
	}//O(N)
};

class ConnectedIsland {
public:
	void dfs(vector<vector<char>> &grid, pair<int, int> p, vector<vector<int>> &visited) {
		int i = p.first;
		int j = p.second;

		visited[i][j] = 1;

		//Left
		if ((j != 0 && !visited[i][j - 1]) && grid[i][j - 1] == '1')
			dfs(grid, {i, j - 1}, visited);

		//Right
		if ((j != grid[0].size() - 1 && !visited[i][j + 1]) && grid[i][j + 1] == '1')
			dfs(grid, {i, j + 1}, visited);

		//Up
		if ((i != 0 && !visited[i - 1][j]) && grid[i - 1][j] == '1')
			dfs(grid, {i - 1, j}, visited);

		//Down
		if ((i != grid.size() - 1 && !visited[i + 1][j]) && grid[i + 1][j] == '1')
			dfs(grid, {i + 1, j}, visited);

	}

	int numIslands(vector<vector<char>>& grid) {
		vector<vector<int>> visited(grid.size(), vector<int>(grid[0].size(), 0));
		int cnt = 0;

		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[i].size(); j++) {
				if (!visited[i][j] && grid[i][j] != '0') {
					dfs(grid, {i, j}, visited);
					cnt++;
				}
			}
		}

		return cnt;
	}
};


class FloodFill {
public:
	void DFS(vector<vector<int>>& image, int i, int j, int nc, int old_color, vector<vector<int>> &visited) {
		image[i][j] = nc; //Change the color of the cell to new color.
		visited[i][j] = 1; //Mark the current cell visited.

		//Left
		if (j > 0 && image[i][j - 1] == old_color && !visited[i][j - 1]) //If it is not the 0th column and the cell is not colored yet with new color and it's not visited yet, onle then call DFS
			DFS(image, i, j - 1, nc, old_color, visited);

		//Right
		if (j < image[0].size() - 1  && image[i][j + 1] == old_color && !visited[i][j + 1])
			DFS(image, i, j + 1, nc, old_color, visited);
		//Up
		if (i > 0 && image[i - 1][j] == old_color && !visited[i - 1][j])
			DFS(image, i - 1, j, nc, old_color, visited);
		//Down
		if (i < image.size() - 1 && image[i + 1][j] == old_color && !visited[i + 1][j])
			DFS(image, i + 1, j, nc, old_color, visited);

	}
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
		vector<vector<int>> visited(image.size(), vector<int>(image[0].size(), 0)); //Make a visited array (2D DP)
		int old_color = image[sr][sc]; //Store the current color as old color.
		DFS(image, sr, sc, newColor, old_color, visited);
		return image;
	}
};

class RottenOranges
{
	int bfs(vector<vector<int>>& grid, queue<vector<int>> &wait, vector<vector<int>> &visited, int fresh) {
		int Time = 0;

		while (!wait.empty()) {
			int n = wait.size();
			while (n--) {
				int i = wait.front()[0];
				int j = wait.front()[1];
				int T = wait.front()[2]; //The time, when it was rotted.
				wait.pop();

				/*
				NOTE: In 1 unit of time a rotten orange can rote 4 neighbour fresh oranges at the same time.
				DFS will not work, because DFS will take +1 time to rote all the connected oranges. (It cannot minimize the time, cuz it can't work with simultaneous neghbours)
				*/

				//LEFT
				if (j > 0 && !visited[i][j - 1] && grid[i][j - 1] == 1) {
					wait.push({i, j - 1, T + 1});
					visited[i][j - 1] = 2;
					fresh--;
					Time = T + 1; // +1 unit of time needed for rotten fresh oranges.
				}

				//RIGHT
				if (j < grid[0].size() - 1 && !visited[i][j + 1] && grid[i][j + 1] == 1) {
					wait.push({i, j + 1, T + 1});
					visited[i][j + 1] = 2;
					fresh--;
					Time = T + 1; //+1 unit of time needed for rotten fresh oranges.
				}

				//UP
				if (i > 0 && !visited[i - 1][j] && grid[i - 1][j] == 1) {
					wait.push({i - 1, j, T + 1});
					visited[i - 1][j] = 2;
					fresh--;
					Time = T + 1; //+1 unit of time needed for rotten fresh oranges.
				}

				//DOWN
				if (i < grid.size() - 1  && !visited[i + 1][j] && grid[i + 1][j] == 1) {
					wait.push({i + 1, j, T + 1});
					visited[i + 1][j] = 2;
					fresh--;
					Time = T + 1; //+1 unit of time needed for rotten fresh oranges.
				}

			}
		}

		if (fresh == 0) //If all fresh oranges are rotten then return the minimum Time
			return Time;
		else
			return -1;
	}
public:
	//Function to find minimum time required to rot all oranges.
	int orangesRotting(vector<vector<int>>& grid) {
		int fresh = 0;
		queue<vector<int>> wait;
		vector<vector<int>> visited(grid.size(), vector<int>(grid[0].size(), 0));
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[i].size(); j++) {
				if (grid[i][j] == 1)
					fresh++;
				if (grid[i][j] == 2) {
					wait.push({i, j, 0});
					visited[i][j] = 2;
				}
			}
		}


		return bfs(grid, wait, visited, fresh);
	}
};


//link: https://practice.geeksforgeeks.org/problems/distance-of-nearest-cell-having-1-1587115620/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=distance-of-nearest-cell-having-1
class Distance_Of_Nearest_Cell_Having_1
{
	void bfs(vector<vector<int>>&grid, vector<vector<int>>&vis, vector<vector<int>> &ans, queue<vector<int>> &wait) {
		while (!wait.empty()) {
			int n = wait.size();
			while (n--) {
				int r = wait.front()[0];
				int c = wait.front()[1];
				int v = wait.front()[2];
				wait.pop();

				if (r > 0 && grid[r - 1][c] == 0 && !vis[r - 1][c]) {
					ans[r - 1][c] = v + 1; // Storing the distance.
					vis[r - 1][c] = 1; // Marking as visited.
					wait.push({r - 1, c, v + 1}); // Push the neighbour data into queue.
				}
				if (r < grid.size() - 1 && grid[r + 1][c] == 0 && !vis[r + 1][c]) {
					ans[r + 1][c] = v + 1;
					vis[r + 1][c] = 1;
					wait.push({r + 1, c, v + 1});
				}
				if (c > 0 && grid[r][c - 1] == 0 && !vis[r][c - 1]) {
					ans[r][c - 1] = v + 1;
					vis[r][c - 1] = 1;
					wait.push({r, c - 1, v + 1});
				}
				if (c < grid[0].size() - 1 && grid[r][c + 1] == 0 && !vis[r][c + 1]) {
					ans[r][c + 1] = v + 1;
					vis[r][c + 1] = 1;
					wait.push({r, c + 1, v + 1});
				}

			}
		}
	}

public:
	//Function to find distance of nearest 1 in the grid for each cell.
	vector<vector<int>>nearest(vector<vector<int>>&grid)
	{
		int n = grid.size();
		int m = grid[0].size();
		queue<vector<int>> wait;
		vector<vector<int>> ans(n, vector<int>(m, 0));
		vector<vector<int>> vis(n, vector<int>(m, 0));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == 1) {
					wait.push({i, j, 0}); //Pushing all the 1's position into queue
					vis[i][j] = 1; // Mark all 1 as visited

				}
			}
		}
		// cout << wait.size() << "\n";
		bfs(grid, vis, ans, wait);
		return ans;
	}
};


class SurroundedRegion {
	/*
	    Main intuition is that if a O is at any of the boundary then all the connected O can not called surrounded regeion.
	    So found all that O and mark it as visited (i.e those are not gonna convert to X)
	*/
	void dfs(vector<vector<char>> &mat, int n, int m, int i, int j, vector<vector<char>> &vis) {
		vis[i][j] = 1;
		//Left
		if (j > 0 && mat[i][j - 1] == 'O' && !vis[i][j - 1])
			dfs(mat, n, m, i, j - 1, vis);
		//Right
		if (j < m - 1 && mat[i][j + 1] == 'O' && !vis[i][j + 1])
			dfs(mat, n, m, i, j + 1, vis);
		//Up
		if (i > 0 && mat[i - 1][j] == 'O' && !vis[i - 1][j])
			dfs(mat, n, m, i - 1, j, vis);
		// Down
		if (i < n - 1 && mat[i + 1][j] == 'O' && !vis[i + 1][j])
			dfs(mat, n, m, i + 1, j, vis);
	}

public:
	vector<vector<char>> fill(int n, int m, vector<vector<char>> mat)
	{
		vector<vector<char>> vis(n, vector<char>(m));


		//Traversing the left boundary.
		for (int i = 0; i < n; i++) {
			if (mat[i][0] == 'O' && !vis[i][0])
				dfs(mat, n, m, i, 0, vis);
		}

		//Traversing the right boundary.
		for (int i = 0; i < n; i++) {
			if (mat[i][m - 1] == 'O' && !vis[i][m - 1])
				dfs(mat, n, m, i, m - 1, vis);
		}

		//Traversing the top boundary.
		for (int i = 0; i < m; i++) {
			if (mat[0][i] == 'O' && !vis[0][i])
				dfs(mat, n, m, 0, i, vis);
		}

		//Traversing the bottom boundary.
		for (int i = 0; i < m; i++) {
			if (mat[n - 1][i] == 'O' && !vis[n - 1][i])
				dfs(mat, n, m, n - 1, i, vis);
		}

		//All the O that are not visited, those are surely surrounded region, so convert those O's to X.
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (mat[i][j] == 'O' && !vis[i][j])
					mat[i][j] = 'X';
			}
		}

		return mat;

	}
};


class CountDistinctIslands {
	void dfs(vector<vector<int>>& grid, int i, int j, vector<vector<int>> &vis, pair<int, int> org, vector<pair<int, int>> &shape) {
		vis[i][j] = 1;
		//To achive the shape of the island, substract all the co-ordinates from the origin.
		shape.push_back({i - org.ff, j - org.ss});

		int n = grid.size();
		int m = grid[0].size();

		//Right
		if (j < m - 1 && grid[i][j + 1] == 1 && !vis[i][j + 1])
			dfs(grid, i, j + 1, vis, org, shape);

		//Down
		if (i < n - 1 && grid[i + 1][j] == 1 && !vis[i + 1][j])
			dfs(grid, i + 1, j, vis, org, shape);

		//Left
		if (j > 0 && grid[i][j - 1] == 1 && !vis[i][j - 1])
			dfs(grid, i, j - 1, vis, org, shape);

		//UP
		if (i > 0 && grid[i - 1][j] == 1 && !vis[i - 1][j])
			dfs(grid, i - 1, j, vis, org, shape);

	}// TC --> O(N x M) SC--> O(N x M)
public:
	int countDistinctIslands(vector<vector<int>>& grid) {
		int n = grid.size();
		int m = grid[0].size();

		vector<vector<int>> vis(n, vector<int>(m)); //O(N x M)
		//For storing the distinct islands.
		set<vector<pair<int, int>>> st; //O(No. of distinct island)

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == 1 && !vis[i][j]) {
					//For storing the shapes of the island.
					vector<pair<int, int>> shape;
					dfs(grid, i, j, vis, {i, j}, shape);
					//Insert distinct shaped island into the set.
					st.insert(shape);
				}
			}
		}


		return st.size();
	}
};


class BipartiteGraph {
	bool bfs(vector<int>adj[], int start, vector<int> &color) {
		queue<int> wait;
		//Push the 1st vertex into the queue.
		wait.push(start);
		//Always color the 1st vertex of the graph as 0
		color[start] = 0;

		while (!wait.empty()) {
			int vertex = wait.front();
			wait.pop();

			for (int i : adj[vertex]) {
				if (color[i] == -1) { // If the vertex is not colored yet.
					color[i] = !color[vertex]; //color it with it parents's opposite color
					wait.push(i); //Then push it to the queue.
				}
				else {
					if (color[i] == color[vertex]) // If parent and the child has the same color then it's not Bipartite
						return false;
				}
			}
		}

		return true;
	}
public:
	bool isBipartite(int V, vector<int>adj[]) {
		vector<int> color(V, -1);

		//Check for multiple graph components.
		for (int i = 0; i < V; i++) {
			if (color[i] == -1) {
				if (bfs(adj, i, color) == false)
					return false;
			}
		}

		return true;

	}

};


class Detect_Cycle_In_DirectedGraph {
	bool dfs(vector<int> adj[], int i, vector<int> &vis) {
		//Mark the current node as visited and also path visited (denoted as 2)
		vis[i] = 2;

		for (int v : adj[i]) {
			//If the current node is visited and also path visited then it's a cycle.
			if (vis[v] == 2)
				return true;
			if (!vis[v]) {
				if (dfs(adj, v, vis)) //If we found a cycle just return true from here.
					return true;
			}
		}

		//Undo the path visited (because there could be unique paths, if cycle is not detected).
		//Make it as only visietd (deboetd as 1)
		vis[i] = 1;

		//We didn't detect a cycle yet.
		return false;
	}
public:
	// Function to detect cycle in a directed graph.
	bool isCyclic(int V, vector<int> adj[]) {
		vector<int> vis(V);

		//Go for all the node which are not visited.
		for (int i = 0; i < V; i++) {
			if (!vis[i])
				if (dfs(adj, i, vis)) //A cycle is detected.
					return true;
		}

		return false;
	}
};


class Eventual_Safe_States {
	//Normal Cycle detection algorithm.
	bool dfs(vector<int> adj[], int i, vector<int> &vis) {
		vis[i] = 2;

		for (int v : adj[i]) {
			if (vis[v] == 2)
				return true;

			if (!vis[v]) {
				if (dfs(adj, v, vis))
					return true;
			}
		}

		vis[i] = 1;
		return false;

	}

	//Using Kahn's Algorithm.
	vector<int> bfs(int V, vector<int> adj[]) {
		vector<vector<int>> adjrev(V);
		vector<int> indegree(V);
		queue<int> Q;
		vector<int> topo;

		//Reverse the edge connection. (For intuition just dry run for GOD SHAKE)
		for (int i = 0; i < V; i++) {
			for (int n : adj[i]) {
				adjrev[n].push_back(i);
			}
		}

		//Count all the indegree of all vertices of new reversed edge graph.
		for (int i = 0; i < V; i++) {
			for (int n : adjrev[i])
				indegree[n]++;
		}

		//Push all the vertices which have indegree equal to 0
		for (int i = 0; i < V; i++) {
			if (indegree[i] == 0)
				Q.push(i);
		}

		while (!Q.empty()) {
			int ver = Q.front();
			Q.pop();
			topo.push_back(ver);

			for (int n : adjrev[ver]) {
				indegree[n]--;
				if (indegree[n] == 0)
					Q.push(n);
			}
		}


		//The determined topological oreder vertices are the only safe node.
		//Because those nodes which will have cycle, that vertices will never be in the queue.
		return topo;


	}
public:
	vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
		vector<int> vis(V);
		vector<int> ans;

		for (int i = 0; i < V; i++) {
			//If vis[i] == 2 then it means that path take us to a cycle, so ignore that path.
			if (vis[i] != 2) {
				//If the node is leads to the terminal node then it's a safe node (That is we don't detect a cycle following this node)
				if (!dfs(adj, i, vis))
					ans.push_back(i);
			}
		}

		//Because they wanted the safe node as accending order.
		sort(ans.begin(), ans.end());

		return ans;

	}
};


class Topological_Sort
{
	void dfs(vector<int> adj[], int i, stack<int> &st, vector<int> &vis) {
		vis[i] = 1;

		for (int v : adj[i]) {
			if (!vis[v])
				dfs(adj, v, st, vis);
		}

		//After visiting all neighbour nodes of current node, push the ode into the stack.
		st.push(i);
	}

	//Khan's Algorithm, by using indegree BFS.
	vector<int> bfs(vector<int> adj[], int V) {
		queue<int> wait;
		vector<int> indegree(V);
		vector<int> ans;

		//Count the indegree of all node (i.e no of incoming edges)
		for (int i = 0; i < V; i++) {
			for (int node : adj[i]) {
				indegree[node]++;
			}
		}

		//Push the vertices which has 0 no of incoming edges.
		for (int i = 0; i < V; i++) {
			if (indegree[i] == 0)
				wait.push(i);
		}


		while (!wait.empty()) {
			//Queue only contains the vetices which has 0 indegree.
			int node = wait.front();

			//Add the 0 indegree vetices to the answer.
			ans.push_back(node);

			wait.pop();

			//Delete the number of incoming edges to all the neighbour of current vertices.
			for (int i : adj[node]) {
				indegree[i]--;
				//If any vertices become a 0 indegree vertices then add it to the queue.
				if (indegree[i] == 0)
					wait.push(i);
			}
		}

		return ans;
	}
public:
	//Function to return list containing vertices in Topological order.
	vector<int> topoSort(int V, vector<int> adj[])
	{
		vector<int> topo;
		stack<int> st;
		vector<int> vis(V);

		for (int i = 0; i < V; i++) {
			if (!vis[i])
				dfs(adj, i, st, vis);
		}

		//Store the LIFO order into the stack.
		while (!st.empty()) {
			topo.push_back(st.top());
			st.pop();
		}

		return topo;
	}
};


class Prerequisite_Tasks {
public:
	bool isPossible(int N, vector<pair<int, int> >& pre) {
		vector<vector<int>> adj(N);
		vector<int> indegree(N);
		vector<int> topo;
		queue<int> Q;

		//Covert the given prerequisite task into adj list.
		//Also calculate the indegree for applying kahs's algorithm.
		for (auto p : pre) {
			adj[p.second].push_back(p.first);
			indegree[p.first]++;
		}


		//Whichever vertex has indegree 0 just push it to the queue.
		for (int i = 0; i < N; i++) {
			if (indegree[i] == 0)
				Q.push(i);
		}

		//BFS
		while (!Q.empty()) {
			int ver = Q.front();
			Q.pop();
			//Add the elements from the queue to the topological array.
			topo.push_back(ver);

			for (int i : adj[ver]) {
				//Reduce the indegree of neighbour vertices.
				indegree[i]--;
				//If any neighbour vertices has 0 indegree then push it to the queue.
				if (indegree[i] == 0)
					Q.push(i);
			}
		}

		//If topo size is euqal to N, it means we have no cycle and we can finish all the task.
		return topo.size() == N;
	}
};


class Alien_Dictionary {
public:
	string findOrder(string dict[], int N, int K) {

		//Initializing the resources.
		unordered_map<int, vector<int>> adj;
		vector<int> indegree(K);
		queue<int> Q;
		vector<int> topo;
		string ans = "";


		//Making the directed graph connection for 1st K alphabets.
		for (int i = 0; i < N - 1; i++) {

			int I = 0, J = 0;

			//Untill one of the string got exhausted.
			while (I < dict[i].size() && J < dict[i + 1].size()) {
				//If Ith charecter is not equal to the Jth charecter, it means Ith char has a directed edge toward Jth char (i.e Ith --> Jth)
				if (dict[i][I] != dict[i + 1][J]) {
					//So make the connection to Ith --> Jth
					//Representing all the alphabet in terms of numbers.
					adj[dict[i][I] - 'a'].push_back(dict[i + 1][J] - 'a');
					//No need to check further, because ith string is already smaller than i+1th string.
					break;
				}

				//Else both the Ith and Jth char is same, so increment the values.
				I++, J++;
			}
		}

		//Count the Indegree.
		for (int i = 0; i < K; i++) {
			//Because adj is a map so adj[i] <-- this statement will also add the key == i in map representation (Multiple Graph Component).
			for (int node : adj[i])
				indegree[node]++;
		}


		//Push the virtices of 0 indegree to the queue.
		for (int i = 0; i < K; i++) {
			if (indegree[i] == 0)
				Q.push(i);
		}


		//Normal Kahn's algorithm to find the topological path.
		while (!Q.empty()) {
			int ver = Q.front();
			Q.pop();
			topo.push_back(ver);

			for (int n : adj[ver]) {
				//Reduce the indegree of neighbour nodes.
				indegree[n]--;
				//If any of the neighbour node has 0 indegree then push it to the queue.
				if (indegree[n] == 0)
					Q.push(n);
			}
		}

		//Re-convert the topologican path to it's corresponding alphabet and add to the answer.
		for (int i : topo) {
			ans += 'a' + i;
		}

		return ans;
	}
};

class Dijkstra
{
public:
	//Function to find the shortest distance of all the vertices
	//from the source vertex S.
	vector <int> dijkstra(int V, vector<vector<int>> adj[], int S)
	{
		// Creating distance array.
		vector<int> dist(V, INT_MAX);
		// Min heap for storing pair<min_distance, vertex>
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

		// Push the source vertex and the min_distance = 0 in PQ
		pq.push({0, S});
		// Initialize Source vertex distance as 0
		dist[S] = 0;

		// Djikstra Algorithm.
		while (!pq.empty()) {
			// Get the top vertex(vertex stored in pair.second) of the PQ
			int ver = pq.top().second;
			// Pop up the top
			pq.pop();

			// Go to all adjacence nodes.
			for (auto it : adj[ver]) {
				// Check for each adjacence node if a minimum distance is found or not.
				// If found then update it's distance and push it to the PQ.
				if (dist[ver] + it[1] < dist[it[0]]) {
					dist[it[0]] = dist[ver] + it[1];
					pq.push({dist[it[0]], it[0]});
				}
			}
		}

		return dist;

	} // TC --> O(ElogV)
};

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n + 1);

	//Taking input of an un-directed graph.
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	//Displaying of an un-directed graph.
	for (int i = 1; i <= n; ++i)
	{
		cout << i << " : ";
		for (int x : adj[i]) cout << x << " ";
		cout << endl;
	}


}
