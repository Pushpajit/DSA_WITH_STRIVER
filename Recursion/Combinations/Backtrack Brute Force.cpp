// TC -> O(2^n)
// SC -> O(n + k)[v, comb] + O(n*k)[ans] + O(2^n)[memory stack]
// URL-> https://leetcode.com/problems/combinations

class Solution
{

    vector<vector<int>> fun(vector<int> &v, int k, vector<int> &comb, int ind)
    {
        vector<vector<int>> ans;

        // If k is 0 it means we found a combination.
        if (k == 0)
        {
            // Push the combination into the ans
            ans.push_back(comb);
            return ans;
        }

        // If ind is off limit then just return the ans.
        if (ind == v.size())
            return ans;

        // Case 1: Take the current element.
        comb.push_back(v[ind]);
        auto pick = fun(v, k - 1, comb, ind + 1);

        // Case 2: Not take the current element. (Backtrack)
        comb.pop_back();
        auto notpick = fun(v, k, comb, ind + 1);

        // Merge the results of take and nottake array into ans.
        for (auto vec : notpick)
        {
            ans.push_back(vec);
        }

        for (auto vec : pick)
        {
            ans.push_back(vec);
        }

        return ans;
    }

public:
    vector<vector<int>> combine(int n, int k)
    {
        vector<int> v(n);
        vector<int> comb;

        // Make an array contains 1 to n elements.
        for (int i = 0; i < n; i++)
            v[i] = i + 1;

        return fun(v, k, comb, 0);
    }
};