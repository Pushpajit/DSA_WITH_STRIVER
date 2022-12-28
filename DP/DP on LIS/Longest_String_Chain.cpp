class Solution {
    bool compare(string &s1, string &s2) {
        // s2.size() should be one less than s1.size()
        // If not then return false.
        if (s1.size() != s2.size() + 1)
            return false;

        int i = 0, j = 0;

        // Check if (S1 ⩃ S2) == S2
        while (i < s1.size()) {

            if (s1[i] == s2[j]) {
                i++;
                j++;
            }
            else
                i++;
        }

        return i == s1.size() && j == s2.size();
    }


    // Comparator
    static bool cmp(string &s1, string &s2) {
        return s1.size() < s2.size();
    }


public:
    int longestStrChain(vector<string>& words) {
        int n = words.size();
        int maxlength = 1;
        vector<int> DP(n, 1);

        // Sort the array by string's length
        sort(words.begin(), words.end(), cmp);

        // LIS
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {

                if (compare(words[i], words[j]) && DP[j] + 1 > DP[i])
                    DP[i] = DP[j] + 1;

            }

            maxlength = max(maxlength, DP[i]);
        }

        return maxlength;
    }
};