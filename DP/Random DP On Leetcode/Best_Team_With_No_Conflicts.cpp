/*

leetcode:
    https://leetcode.com/problems/best-team-with-no-conflicts/description/

*/


class Solution {
    int fun(vector<vector<int>> &v, int n) {
        int maxscore = INT_MIN;
        vector<int> DP(n);

        // Simple LIS wor kuch nhi h.
        // bas condition m shuttle changes hoga.
        for (int i = 0; i < n; i++) {
            int score = v[i][0];
            for (int j = 0; j < i; j++) {
                // Check conflict condition. (If conflict happens then skip current j)
                if ((v[j][1] < v[i][1] && v[j][0] > v[i][0]) || (v[j][1] > v[i][1] && v[j][0] < v[i][0]))
                    continue;

                // Update the score with max score value from 0 till (i - 1)
                score = max(score, v[i][0] + DP[j]);

            }

            // Store the max score into DP[i]
            DP[i] = score;

            // Update the answer.
            maxscore = max(maxscore, DP[i]);
        }


        return maxscore;
    }

public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = ages.size();
        vector<vector<int>> v(n);

        // Make vector of <age, score>
        for (int i = 0; i < n; i++)
            v[i] = {scores[i], ages[i]};

        // Then sort it according to the age, now we can apply LIS to find max score without
        // any conflict.
        sort(v.begin(), v.end());

        return fun(v, n);
    }
};