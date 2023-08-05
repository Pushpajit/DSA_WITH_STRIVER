// TC -> O(nlogn) + O(n)
// SC -> O(1)
// Link: https://takeuforward.org/data-structure/merge-overlapping-sub-intervals/

class Solution {
    // comparator
    static bool comp(vector<int> &a, vector<int> &b){
        if(a[0] != b[0])
           return a[0] < b[0];
        else
           return a[1] < b[1]; 
    }

public:
    vector<vector<int>> merge(vector<vector<int>>& v) {
        // We need to sort the array
        sort(v.begin(), v.end(), comp);

        vector<vector<int>> ans;
        // 1st element always going to be considered.
        ans.push_back(v[0]);


        for(int i = 1; i < v.size(); i++){
            // Merging the ith interval if the v[i][0] <= ans[n - 1][1]
            if(v[i][0] <= ans[ans.size() - 1][1])
                // Expand the interval by taking the max of ans[n - 1][1] and v[i][1]
                // and assign it to ans[n - 1][1]
                ans[ans.size() - 1][1] = max(ans[ans.size() - 1][1], v[i][1]);
            else
                // If the ith interval can not merged then push ith interval into ans
                // and use it to merge rest of the intervals.
                ans.push_back(v[i]);
        }

        return ans;
    }
};