#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(x) cout << #x << " : " << x << "\n";

const int MAX = 1e6 + 5;
int DP[MAX];

//Normal Method.
ll fib(int n) {
	if (n == 1 || n == 2)
		return 1;
	cout << "Function Call\n";
	return fib(n - 1) + fib(n - 2);
}

//Dynamic Programming.
ll fibdp(int n) {
	DP[0] = 0;
	DP[1] = 1;

	for (int i = 2; i <= n; ++i)
		DP[n] = DP[n - 1] + DP[n - 2];

	return DP[n];
}

ll staircase(int n) {
	DP[0] = 1;
	DP[1] = 1;
	DP[2] = 2;

	for (int i = 3; i <= n; ++i)
		DP[i] = DP[i - 1] + DP[i - 2] + DP[i - 3];

	return DP[n];
}

vector<vector<int>> SubsetOfArray(int A[], int s, int n) {
	if (s == n) {
		vector<vector<int>> ans(1);
		return ans;
	}

	auto ans = SubsetOfArray(A, s + 1, n);
	int size = ans.size();

	for (int i = 0; i < size; ++i)
	{
		vector<int> temp{A[s]};
		for (int j = 0; j < ans[i].size(); ++j)
			temp.push_back(ans[i][j]);

		ans.push_back(temp);

	}

	return ans;
}

//Original DP.
int MinStepToOne(int n) {
	DP[1] = 0;
	DP[2] = 1;

	for (int i = 3; i <= n; ++i)
	{
		int a, b, c;
		a = b = c = INT_MAX;

		if (i % 3 == 0)
			a = DP[i / 3];

		if (i % 2 == 0)
			b = DP[i / 2];

		c = DP[i - 1];

		DP[i] = min(c, min(a, b)) + 1;
	}

	return DP[n];
}


//DP Solution.
int MinimumCount(int n) {
	DP[0] = 0;
	DP[1] = 1;
	DP[2] = 2;
	DP[3] = 3;

	for (int i = 4; i <= n; ++i)
	{
		int MIN = INT_MAX;

		for (int j = 1; j * j <= i; ++j)
			MIN = min(MIN, (DP[i - (j * j)] + 1));

		DP[i] = MIN;
	}

	return DP[n];
}


int LongestIncreasingSubsequence(int A[], int n, int c) {

	int overall = 0;

	for (; c >= 0 ; c--)
	{
		if (DP[c] > 0) {
			overall = max(MAX, overall);
			continue;
		}

		int MAX = 1;
		for (int i = c - 1; i >= 0; --i)
		{
			if (A[c] > A[i])
				MAX = max(MAX, LongestIncreasingSubsequence(A, n, i) + 1);
		}
		overall = max(MAX, overall);
	}

	return DP[c] = overall;
}

string alphatochar(string s) {
	string r = "";
	int num = 0;
	int p = 1;
	for (int i = s.size() - 1; i >= 0; --i)
	{
		num += p * (s[i] - '0');
		p *= 10;
	}

	if (num > 26 || num < 1)
		return r;

	r += char(96 + num);
	return r;
}

vector<string> AlphaCode(string s) {
	vector<string> ans;
	if (s.empty()) {
		ans.push_back(s);
		return ans;
	}
	if (s.size() == 1) {
		ans.push_back(alphatochar(s));
		return ans;
	}

	//For single digit
	auto res1 = AlphaCode(s.substr(1));
	for (int i = 0; i < res1.size(); ++i)
		ans.push_back(alphatochar(s.substr(0, 1)) + res1[i]);

	//Checking for 2 digit. (IF alphatochar() returns "" then it means num > 26 or num < 26) then do nothing
	if (alphatochar(s.substr(0, 2)) != "") {
		auto res2 = AlphaCode(s.substr(2));
		for (int i = 0; i < res2.size(); ++i)
			ans.push_back(alphatochar(s.substr(0, 2)) + res2[i]);
	}


	return ans;

}


int AlphacodeMemoise(string s) {
	if (s.size() == 0 || s.size() == 1)
		return 1;

	if (DP[s.size()] > 0)
		return DP[s.size()];

	int cnt = AlphacodeMemoise(s.substr(1));

	if (((s[0] - '0') * 10) + (s[1] - '0') <= 26)
		cnt += AlphacodeMemoise(s.substr(2));

	return DP[s.size()] = cnt;
}

//DP solution.
int AlphacodeMemoiseittr(string &s) {
	int cnt = 0;
	DP[0] = DP[1] = 1;

	for (int i = 2; i <= s.size(); ++i)
	{
		DP[i] = DP[i - 1];

		if ((s[i - 2] - '0') * 10 + s[i - 1] - '0' <= 26)
			DP[i] += DP[i - 2];

	}

	return DP[s.size()];
}

//Brute Force Recurcive Solution.
int loothouse(vector<int> &v, int n) {
	int loot = 0;

	for (int i = n - 2; i >= 0; --i)
		loot = max(loot, loothouse(v, i));

	return loot + v[n];
}

//Memoization.
int loothouse2(vector<int> &v, int n) {
	if (n == 0) return v[0];
	if (n < 0) return 0;

	if (DP[n] != 0) return DP[n];

	int pick = v[n] + loothouse2(v, n - 2);
	int notpick = 0 + loothouse2(v, n - 1);

	return DP[n] = max(pick, notpick);
}

//DP.
int loothouse3(vector<int> &v) {
	vector<int> DP(v.size() + 1, -1);

	DP[0] = v[0];
	DP[1] = max(v[0], v[1]);

	for (int i = 2; i < v.size(); ++i)
	{
		int pick = v[i] + DP[i - 2];
		int notpick = 0 + DP[i - 1];

		DP[i] = max(pick, notpick);
	}

	return DP[v.size() - 1];
}


int frog(vector<int> &v, int k) {
	DP[0] = 0;
	DP[1] = abs(v[0] - v[1]);

	for (int i = 2; i < v.size(); ++i)
	{
		int j = 1;
		int MIN = INT_MAX;
		//K jumps
		while (j <= k && (i - j) >= 0) {
			MIN = min((DP[i - j] + abs(v[i] - v[i - j])), MIN);
			j++;
		}

		DP[i] = MIN;
	}

	return DP[v.size() - 1];

}

ll DP_2D[100][100];
int ninjaTrainning(vector<vector<int>> &v, int day, int last_task) {
	if (day == 0) {
		//Don't repeat for already computed task.
		//If the maximum point is already computed then that can be found
		//DP[For current day][Last day task]
		if (DP_2D[day][last_task] > 0)
			return DP_2D[day][last_task];

		int MAX = 0;
		// Skip the last day task and take the maximum points and return.
		for (int i = 0; i < v[0].size(); ++i)
		{
			if (i != last_task)
				MAX = max(MAX, v[0][i]);
		}

		//Intuition: For current day if we skip the last day task what is the maximum points we can achive
		//that must be store in DP[current day][for last day last task] = maximum points except the last day task.
		//**Basically current days point is depend upon previous days task.
		return DP_2D[day][last_task] = MAX;
	}

	//Don't repeat, already computed task.
	if (DP_2D[day][last_task] > 0)
		return DP_2D[day][last_task];


	int MAX_point = 0;
	for (int i = 0; i < v[day].size(); ++i)
	{
		int points = 0;
		if (i != last_task)
			//The recursion will return maximum point + you have to add the current day's current point.
			points = ninjaTrainning(v, day - 1, i) + v[day][i];

		MAX_point = max(MAX_point, points);// Take the maximum of all the points in current day.
	}

	//**Current days point is depend upon previous days task.
	return DP_2D[day][last_task] = MAX_point;

}

int ninjaTrainningTabulation(vector<vector<int>> &v) {
	int DPP[v.size() + 1][3];

	//Initialize the base cases.
	DPP[0][0] = max(v[0][1], v[0][2]);
	DPP[0][1] = max(v[0][0], v[0][2]);
	DPP[0][2] = max(v[0][0], v[0][1]);

	//Nothing special just simulate the memoization part coded above.
	for (int day = 1; day < v.size(); ++day)
	{
		//Calculate and store for each last task.
		for (int last = 0; last < 3; last++) {
			//Same as recursion.
			int MAX = 0;
			for (int j = 0; j < 3; j++) {
				int points = 0;
				if (j != last)
					points = DPP[day - 1][j] + v[day][j];
				//Take maximum points.
				MAX = max(points, MAX);
			}
			//Store it to the current day and current last task(if ignored today).
			DPP[day][last] = MAX;
		}
	}

	int n = v.size() - 1;

	return max(DPP[n][0], max(DPP[n][1], DPP[n][2]));
}


int ninjaTrainningSpaceOptimization(vector<vector<int>> &v) {
	vector<int> B(3);

	B[0] = max(v[0][1], v[0][2]);
	B[1] = max(v[0][0], v[0][2]);
	B[2] = max(v[0][0], v[0][1]);

	for (int day = 1; day < v.size(); ++day)
	{
		vector<int> C(3);
		for (int last = 0; last < 3; ++last)
		{
			int MAX = 0;
			for (int task = 0; task < 3; ++task)
			{
				if (task != last) {
					int points = B[task] + v[day][task];
					MAX = max(MAX, points);
				}
			}

			C[last] = MAX;

		}

		B = C;
	}

	return max(B[0], max(B[1], B[2]));

}


//Unique Path from cell (0,0) to reach (n-1, n-1)
//We need to consider about all the possible ways, so let's do recursion.
ll uniquePath(int n, int i, int j) {
	if (i == 0 && j == 0)
		return 1;

	if (i < 0 || j < 0)
		return 0;

	if (DP_2D[i][j] > 0)
		return DP_2D[i][j];

	ll up = uniquePath(n, i - 1, j);
	ll down = uniquePath(n, i, j - 1);

	return DP_2D[i][j] = (up + down);
}

//Tabular
ll uniquePath(int n) {
	//Declearing the DP state.
	ll DP[n][n];

	//Initialize the base case.
	DP[0][0] = 1;

	//Write the recurrence/ Simulate the recursion.
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			//Initialize with 0 is important, else it will add garbage value at line no. 427
			ll left = 0, up = 0;

			//Ignore the base case because it's already been taken care of.
			if (i == 0 && j == 0)
				continue;

			//Check if the indices don't go beyond the boundary.
			if (j > 0)
				left = DP[i][j - 1]; //Bring the answer from the left cell (If the cell exists).

			if (i > 0)
				up = DP[i - 1][j]; //Bring the answer from the above cell (If the cell exists).

			//Save the current calculated path for current cell.
			DP[i][j] = left + up;
		}
	}

	//The answer will be stored at the bottom right most cell.
	return DP[n - 1][n - 1];
}

//Space optimization.
ll uniquePathSpaceOptimization(int n) {
	vector<ll> DP(n, 1);

	for (int i = 1; i < n; ++i)
	{
		vector<ll> current(n, 0);
		for (int j = 0; j < n; ++j)
		{
			ll up = 0, left = 0;

			up = DP[j]; //Bring path count from correseponding upward cell.

			//Bring the path count from left cell of the current cell
			//it always stores the left side path count.
			if (j > 0)
				left = current[j - 1];

			//Save current path count.
			current[j] = up + left;
		}

		//Save current state.
		DP = current;
	}

	//Answer will be stored in the last index of DP[]
	return DP[n - 1];
}


int mazeObsticals(vector<vector<int>> &v, int i, int j) {
	if (i == 0 && j == 0)
		return 1;

	if (i < 0 || j < 0)
		return 0;

	if (v[i][j] == -1)
		return 0;

	if (DP_2D[i][j] > 0)
		return DP_2D[i][j];

	int up = mazeObsticals(v, i - 1, j);
	int left = mazeObsticals(v, i, j - 1);

	return DP_2D[i][j] = up + left;

}

//Tabulation

int mazeObsticalsTabuler(vector<vector<int>> &v, int m, int n) {
	vector<int> DP(n, 0);

	for (int i = 0; i < m; ++i)
	{
		vector<int> current(n, 0);

		for (int j = 0; j < n; ++j)
		{
			int up = 0, left = 0;

			if (i == 0 && j == 0) {
				current[j] = 1;
				continue;
			}
			if (v[i][j] == -1) {
				current[j] = 0;
				continue;
			}

			if (i > 0)
				up = DP[j];
			if (j > 0)
				left = current[j - 1];

			current[j] = up + left;
		}
		DP = current;
	}

	return DP[n - 1];

}


int Triangle(vector<vector<int>> &v, int i, int j) {
	if (i == v.size() - 1)
		return v[i][j];

	if (DP_2D[i][j] > 0)
		return DP_2D[i][j];

	int down = Triangle(v, i + 1, j) + v[i][j];
	int diag = Triangle(v, i + 1, j + 1) + v[i][j];


	return DP_2D[i][j] = min(down, diag);
}//O(2^(n^2))

int MinMaxFallingPath(vector<vector<int>> &v, int i, int j) {

	if (j < 0 || j == v.size())
		return 1e8;

	if (i == v.size() - 1)
		return v[i][j];

	int left = MinMaxFallingPath(v, i + 1, j - 1) + v[i][j];
	int mid = MinMaxFallingPath(v, i + 1, j) + v[i][j];
	int right = MinMaxFallingPath(v, i + 1, j + 1) + v[i][j];

	return min(mid, min(left, right));
}

int DP_3D[100][100][100];
int chocolatePickup(vector<vector<int>> &v, int i, int a, int b) {
	//Check for out of grid
	if (a < 0 || b > v[0].size() - 1)
		return INT_MIN;

	//Base case.
	if (i == v.size() - 1) {
		if (a == b)
			return v[i][a];
		else
			return v[i][a] + v[i][b];
	}

	if (DP_3D[i][a][b] > 0)
		return DP_3D[i][a][b];

	int MAXI = INT_MIN;
	for (int j = -1; j <= 1; ++j)
	{
		for (int k = -1; k <= 1; ++k)
		{
			if (a != b)
				MAXI = max(MAXI, v[i][a] + v[i][b] + chocolatePickup(v, i + 1, a + j, b + k));
			else
				MAXI = max(MAXI, v[i][a] + chocolatePickup(v, i + 1, a + j, b + k));
		}
	}

	return DP_3D[i][a][b] = MAXI;


}

int superJumpOnGrid(vector<vector<int>> &v, int i, int j) {
	if (i == 0 && j == 0)
		return 1;

	int up = i - 1;
	while (up >= 0 && v[up][j] != 0)
		up--;

	if (up >= 0)
		up = superJumpOnGrid(v, up, j);
	else
		up = 0;

	int left = j - 1;
	while (left >= 0 && v[i][left] != 0)
		left--;

	if (left >= 0)
		left = superJumpOnGrid(v, i, left);
	else
		left = 0;


	return up + left;

}

int dp[1005][1005];
bool SubsetSumToK(vector<int> &v, int ind, int k) {
	if (k == 0)
		return true;

	if (ind == 0)
		return v[ind] == k;


	if (dp[ind][k] != -1)
		return dp[ind][k];

	bool not_take = SubsetSumToK(v, ind - 1, k);
	bool take = false;
	if (v[ind] <= k)
		take = SubsetSumToK(v, ind - 1, k - v[ind]);


	return dp[ind][k] = (take || not_take);
}

bool SubsetSumToKTabulation(vector<int> &v, int n, int k) {
	vector<vector<bool>> DP(n, vector<bool>(k + 1, false));
	//For k == 0 it should return true.
	for (int i = 0; i < n; i++)
		DP[i][0] = true;
	//Set the 0th row v[0]th index true in DP array if it is <= k
	if (v[0] <= k)
		DP[0][v[0]] = true;

	for (int i = 1; i < n; i++) {
		for (int t = 1; t <= k; t++) {
			//Just copy the recurrence.
			bool no = DP[i - 1][t];
			bool yes = false;
			if (v[i] <= t)
				yes = DP[i - 1][t - v[i]];

			DP[i][t] = no || yes;
		}
	}

	return DP[n - 1][k];
}

int TotalSubsetSum(vector<int> &v, int i, int k) {
	if (k == 0)
		return 1;
	if (i == 0)
		return v[i] == k;

	if (dp[i][k] != -1)
		return dp[i][k];

	int notpick = TotalSubsetSum(v, i - 1, k);
	int pick = 0;
	if (v[i] <= k)
		pick = TotalSubsetSum(v, i - 1, k - v[i]);

	return dp[i][k] = (notpick + pick);

}

/*int Knapsack(vector<int> &item, vector<int> &weight, int ind, int wt) {
	if (wt == 0)
		return 0;

	if (ind == 0) {
		if (weight[ind] <= wt)
			return item[ind];
		else
			return 0;
	}
	if (DP[ind][wt] != -1)
		return DP[ind][wt];

	int notpick = Knapsack(item, weight, ind - 1, wt);
	int pick = 0;
	if (weight[ind] <= wt)
		pick = item[ind] + Knapsack(item, weight, ind - 1, wt - weight[ind]);

	return DP[ind][wt] = max(notpick, pick);
}*/

int KnapsackTabulation(vector<int> &item, vector<int> &weight, int n, int wt) {
	vector<int> DP(wt + 1, 0);

	//All the weight which are greater than current item's weight,
	//can steal the current item.
	for (int i = weight[0]; i <= wt; i++)
		DP[i] = item[0];

	for (int i = 1; i < n; i++) {
		//Just fill right to left, cuz w = wt needs 0 to wt - 1 elements.
		for (int w = wt; w >= 0; w--) {
			int notpick = DP[w];
			int pick = 0;
			if (weight[i] <= w)
				pick = item[i] + DP[w - weight[i]];

			DP[w] = max(notpick, pick);
		}
	}

	return DP[wt];
}

int coinChange(vector<int> &v, int ind, int T) {
	//In the base case if T is divisible by v[0] then return return how many v[0] needs to form T.
	if (ind == 0) {
		if (T % v[0] == 0)
			return T / v[0];
		else
			return 1e9;
	}

	if (dp[ind][T] != -1)
		return dp[ind][T];

	//All subsequence problem you have 2 options, pick and notpick.
	int notpick = 0 + coinChange(v, ind - 1, T);
	int pick = 1e9;
	//If there is infinite supply of anything then check from "ind" itself don't do (ind - 1),
	//In other word if we have to take current element multiple times.
	if (v[ind] <= T)
		pick = 1 + coinChange(v, ind, T - v[ind]);

	return dp[ind][T] = min(notpick, pick);
}


int coinChangeTabulation(vector<int> &v, int n, int T) {
	vector<vector<int>> DP(n, vector<int>(T + 1, 1e9));

	//0th index in each row is 0, because Target = 0 can always achiveable.
	for (int i = 0; i < n; i++) DP[i][0] = 0;

	//Mark all t which are divisible by v[0] to t / v[0]
	for (int t = 0; t <= T; ++t)
	{
		if (t % v[0] == 0)
			DP[0][t] = t / v[0];
	}

	for (int i = 1; i < n; ++i)
	{
		//Just copy and paste the recurrence.
		for (int t = 1; t <= T; ++t)
		{
			int notpick = 0 + DP[i - 1][t];
			int pick = 1e9;
			if (v[i] <= t)
				pick = 1 + DP[i][t - v[i]];

			DP[i][t] = min(pick, notpick);
		}
	}
	return DP[n - 1][T];
}



map<pair<int, int>, int> HSH_DP; //We see that this T is getting -ve sometimes so we used map.
int TargetSum(vector<int> &v, int ind, int T, int Target) {
	//Striver base case written technique, we need to go deep.
	if (ind == 0) {
		//If v[0] is 0 and we found the terget and with 0 we can do both operation + and -
		//So return 2 cuz we have 2 options.
		if (v[0] == 0 && T == Target)
			return 2;
		//Check if any opration with v[0] gives the Target return 1
		else if (T + v[ind] == Target || T - v[ind] == Target)
			return 1;
		else
			return 0;
	}

	//If the key is exists then return the correspoding value.
	if (HSH_DP.count({ind, T}) > 0)
		return HSH_DP[ {ind, T}];

	//We have 2 option either take plus or take minus.
	int plus = TargetSum(v, ind - 1, T + v[ind], Target);
	int minus = TargetSum(v, ind - 1, T - v[ind], Target);

	//Save and return.
	return HSH_DP[ {ind, T}] = (plus + minus);
}


string LCS(string &s1, string &s2, int ind1, int ind2, vector<vector<string>> &DP) {
	//If any one of the index is -ve then return 0 as LCS.
	if (ind1 < 0 || ind2 < 0)
		return "";

	if (DP[ind1][ind2] != "")
		return DP[ind1][ind2];

	if (s1[ind1] == s2[ind2]) {
		return DP[ind1][ind2] = LCS(s1, s2, ind1 - 1, ind2 - 1, DP) + s1[ind1];
	}
	else { //Not Match then max of f(ind1 - 1, ind2) and f(ind1, ind2 - 1)
		string A = LCS(s1, s2, ind1 - 1, ind2, DP);
		string B = LCS(s1, s2, ind1, ind2 - 1, DP);
		if (A.size() > B.size())
			return DP[ind1][ind2] = A;
		else
			return DP[ind1][ind2] = B;
	}
}

void LCStabulation(string &s1, string &s2) {
	int n = s1.size();
	int m = s2.size();
	vector<vector<string>> DP(n + 1, vector<string>(m + 1, ""));
	//We shifted index one to the right, because base case is -1 and array index can't be -ve.
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s1[i - 1] == s2[j - 1])
				DP[i][j] = DP[i - 1][j - 1] + s1[i - 1];
			else {
				string A = DP[i - 1][j];
				string B = DP[i][j - 1];
				if (A.size() > B.size())
					DP[i][j] = A;
				else
					DP[i][j] = B;
			}
		}
	}

	int S = DP[n][m].size();
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= m; ++j)
		{
			if (DP[i][j].size() == S)
				cout << DP[i][j] << endl;
		}
	}
	// for (int i = 0; i <= m; ++i)
	// {
	// 	cout << DP[n][i] << " ";
	// }
}


void LCSStriver(string &s1, string &s2) {
	int n = s1.size();
	int m = s2.size();
	vector<vector<int>> DP(n + 1, vector<int>(m + 1, 0));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s1[i - 1] == s2[j - 1])
				DP[i][j] = 1 + DP[i - 1][j - 1];
			else
				DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
		}
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; ++j)
		{
			cout << DP[i][j] << " ";
		}
		cout << endl;
	}

}



int LongestCommonSubstring(string &s1, string &s2) {
	int n = s1.size();
	int m = s2.size();
	vector<vector<int>> DP(n + 1, vector<int>(m + 1, 0));

	int MAX = INT_MIN;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (s1[i - 1] == s2[j - 1]) //If the both charecter mathches only take that part.
				DP[i][j] = 1 + DP[i - 1][j - 1];

			MAX = max(MAX, DP[i][j]); //Take the maximum.
		}
	}

	return MAX;
}

string LPC(string &s1, string &s2) {
	int n = s1.size();
	vector<vector<int>> DP(n + 1, vector<int>(n + 1, 0));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (s1[i - 1] == s2[j - 1])
				DP[i][j] = 1 + DP[i - 1][j - 1];
			else
				DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
		}
	}

	string ans = "";
	int i = n, j = n;
	while (i > 0 && j > 0) {
		if (s1[i - 1] == s2[j - 1]) {
			ans = s1[i - 1] + ans;
			i--; j--;
		}
		else {
			if (DP[i - 1][j] > DP[i][j - 1])
				i--;
			else
				j--;
		}
	}

	return ans;
}

string shorteseSupersequence(string &s1, string &s2) {
	int n = s1.size();
	int m = s2.size();
	vector<vector<int>> DP(n + 1, vector<int>(m + 1, 0));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s1[i - 1] == s2[j - 1])
				DP[i][j] = 1 + DP[i - 1][j - 1];
			else
				DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
		}
	}

	string lcs = "";
	int i = n, j = m;
	while (i > 0 && j > 0) {
		if (s1[i - 1] == s2[j - 1]) {
			lcs = s1[i - 1] + lcs;
			i--; j--;
		}
		else {
			if (DP[i - 1][j] > DP[i][j - 1])
				i--;
			else
				j--;
		}
	}
	// cout << "LCS: " << lcs << endl;

	i = 0, j = 0;
	int k = 0;
	string super = "";
	while (i < s1.size() && j < s2.size()) {
		if (s1[i] == lcs[k] && s2[j] == lcs[k]) {
			super += lcs[k];
			i++; j++; k++;
		}
		else if (s1[i] == lcs[k]) {
			super += s2[j];
			j++;
		}
		else if (s2[j] == lcs[k]) {
			super += s1[i];
			i++;
		}
		else {
			super += s1[i];
			super += s2[j];
			i++; j++;
		}
	}

	//Just merge the rest of the string.
	if (i < s1.size())
		super += s1.substr(i);
	else
		super += s2.substr(j);

	return super;
}

int DistinctSubsequence(string &s1, string &s2, int i, int j) {
	if (j < 0)
		return 1;
	if (i < 0)
		return 0;

	if (s1[i] == s2[j])
		return DistinctSubsequence(s1, s2, i - 1, j - 1) + DistinctSubsequence(s1, s2, i - 1, j);
	else
		return DistinctSubsequence(s1, s2, i - 1, j);

}

int DSTabulation(string &s1, string &s2) {
	int n = s1.size();
	int m = s2.size();

	vector<vector<int>> DP(n + 1, vector<int>(m + 1, 0));

	for (int i = 0; i <= n; ++i)
		DP[i][0] = 1;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (s1[i - 1] == s2[j - 1])
				DP[i][j] = DP[i - 1][j - 1] + DP[i - 1][j];
			else
				DP[i][j] = DP[i - 1][j];
		}
	}

	return DP[n][m];
}

//*Important
int EditDistance(string &s1, string &s2, int i, int j, vector<vector<int>> &DP) {
	if (j < 0)
		return i + 1; //If s2 got exhausted then i + 1 charecters delete from s1.
	if (i < 0)
		return j + 1; //If s1 got exhausted then j + 1 charecters insert into s1.

	if (DP[i][j] != - 1)
		return DP[i][j];

	//If matches.
	if (s1[i] == s2[j])
		return 0 + EditDistance(s1, s2, i - 1, j - 1, DP);

	//If not matches.
	int ins = 1 + EditDistance(s1, s2, i, j - 1, DP); //If one char is inserted then ovbiously it matches so only reduce j because one char is inserted after i in s1.
	int del = 1 + EditDistance(s1, s2, i - 1, j, DP); //If one char is deleted from s1, then reduce i and j remain same for next char comparison in s2.
	int rep = 1 + EditDistance(s1, s2, i - 1, j - 1, DP); //If replace s1[i] with the same char of s2[j] then both will be matched then reduce both i and j.

	return DP[i][j] = min(ins, min(del, rep)); //Then return minimum of all the three operation.
}

int EditDistanceTabulation(string &s1, string &s2) {
	int n = s1.size();
	int m = s2.size();
	vector<vector<int>> DP(n + 1, vector<int>(m + 1, 0));

	for (int j = 0; j <= m; ++j)
		DP[0][j] = j;

	for (int i = 0; i <= n; ++i)
		DP[i][0] = i;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (s1[i - 1] == s2[j - 1])
				DP[i][j] = 0 + DP[i - 1][j - 1];
			else {
				int ins = 1 + DP[i][j - 1];
				int del = 1 + DP[i - 1][j];
				int rep = 1 + DP[i - 1][j - 1];
				DP[i][j] = min(ins, min(del, rep));
			}
		}
	}

	return DP[n][m];
}

bool wildcardMatching(string &s1, string &s2, int i, int j) {
	//If both the strings got exhausted.
	if (i < 0 && j < 0)
		return true;

	//If s1 got exhausted and s2 still left for checking.
	if (i < 0 && j >= 0)
		return false;

	//If s2 got exhausted and s1 is still left to check.
	//Then go from 0 to i in s1 and check if all s1[0,1,2..i] is '*' then only return true else false
	if (j < 0 && i >= 0) {
		for (int c = 0; c <= i ; ++c)
			if (s1[c] != '*') return false;

		return true;
	}

	if (s1[i] == s2[j] || s1[i] == '?')
		return wildcardMatching(s1, s2, i - 1, j - 1);

	if (s1[i] == '*')
		return wildcardMatching(s1, s2, i - 1, j) || wildcardMatching(s1, s2, i, j - 1);

	return false;
}

int Stock(vector<int> &v) {
	int profit = 0;
	int mini = v[0];

	for (int i = 1; i < v.size(); ++i)
	{
		int cost = v[i] - mini;
		profit = max(profit, cost);
		mini = min(mini, v[i]);
	}

	return profit;
}

int Stock2(vector<int> &v, int i, bool canbuy) {
	if (i == v.size())
		return 0;

	int profit = 0;
	if (canbuy)
		profit = max(-v[i] + Stock2(v, i + 1, 0), 0 + Stock2(v, i + 1, 1));
	else

		profit = max(v[i] + Stock2(v, i + 1, 1), 0 + Stock2(v, i + 1, 0));

	return profit;

}

int LIS(vector<int> &v, int ind, int prev, vector<vector<int>> &DP) {
	if (ind == v.size())
		return 0;

	if (prev != -1 && DP[ind][prev] != -1)
		return DP[ind][prev];

	int notpick = 0 + LIS(v, ind + 1, prev, DP);
	int pick = 0;
	if (prev == -1 || v[ind] > v[prev])
		pick = 1 + LIS(v, ind + 1, ind, DP);

	return DP[ind][prev] = max(pick, notpick);
}

int LISTabulation(vector<int> &v) {
	int n = v.size();
	vector<vector<int>> DP(n + 1, vector<int>(n + 1, 0));

	for (int ind = n - 1; ind >= 0; --ind)
	{
		for (int prev = ind - 1; prev >= -1 ; --prev)
		{
			int notpick = 0 + DP[ind + 1][prev + 1];
			int pick = 0;
			if (v[ind] > v[prev] || prev == -1)
				pick = 1 + DP[ind + 1][ind + 1];

			DP[ind][prev + 1] = max(pick, notpick);
		}
	}

	return DP[0][0];
}

int LIS_BinarySearch(vector<int> &arr, int n) {
	vector<int> lis;
	lis.push_back(arr[0]);

	for (int i = 1; i < n; i++) {
		if (arr[i] > lis.back())
			lis.push_back(arr[i]);
		else {
			//find the lower_bound of the element and replace it,
			//that's how we can keep the record of length of LIS
			int ind = lower_bound(lis.begin(), lis.end(), arr[i]) - lis.begin();
			lis[ind] = arr[i];
		}
	}

	return lis.size();
}
/*
void LDS(vector<int> &v) {
	int n = v.size();
	int MAXi = 0;
	vector<int> DP(n, 1);
	vector<int> backtrack(n);

	//Storing the index into the backtrack array (0 to n - 1)
	for (int i = 0; i < n; i++) backtrack[i] = i;

	//Make this as a LIS problem we have to sort the array.
	//let's say 1,4,7,8,16 --> 1,4,8 if 8 is divisible by 4 then we know that 8 should be divisible by 1 also, because array is sorted.
	sort(v.begin(), v.end());

	//Straight forward LIS with suttle change is if condition.
	for (int i = 1; i < n; i++) {
		for (int prev = 0; prev < i; prev++) {
			if (v[i] % v[prev] == 0 && 1 + DP[prev] > DP[i])
			{
				DP[i] = DP[prev] + 1;
				//Store the previous index into the current index as value.
				backtrack[i] = prev;
			}
			//Update the max index by the index which contains the longest divisible subset.
			if (DP[i] > DP[MAXi])
				MAXi = i;
		}
	}

	//Retriving the divisible subset by the help of backtrack array.
	vector<int> ans;
	int i = MAXi;
	ans.push_back(v[i]);

	while (backtrack[i] != i) {
		ans.push_back(v[backtrack[i]]);
		i = backtrack[i];
	}


	return ans;
}*/

int main() {
	string s1;
	cin >> s1;
	string s2 = s1;
	reverse(s2.begin(), s2.end());
	cout << LongestCommonSubstring(s1, s2);

	// vector<vector<int>> DP(s1.size(), vector<int>(s2.size(), -1));
	// cout << wildcardMatching(s1, s2, s1.size() - 1, s2.size() - 1);
	// cout << EditDistanceTabulation(s1, s2);


}

/*
3
50 70 60
70 80 50
50 60 40

*/
