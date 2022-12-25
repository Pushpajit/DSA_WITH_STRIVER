class Solution {
public:
    int lengthOfLIS(vector<int>& v) {
        int n = v.size();
        vector<int> DP(n, 1);

        //Tabulation For LIS
        for (int ind = 0; ind < n; ind++) {

            int cnt = 0;

            // From 0 to (ind - 1) find the LIS length then add with DP[ind]
            for (int j = 0; j < ind; j++) {

                if (v[j] < v[ind])
                    cnt = max(cnt, DP[j]);
            }

            // Add the maxmimum length to current DP[ind] length.
            DP[ind] += cnt;
        }

        // Find the maximum length stired in DP vector.
        int MAX = 1;
        for (int i : DP) MAX = max(MAX, i);

        return MAX;
    }
};