// If you solved all other part of this problem then it's a cakewalk for ya.

class Solution {
    int fun(vector<int>& stock, int ind, int buy, int fee, vector<vector<int>> DP) {
        if (ind == stock.size())
            return 0;

        if (DP[ind][buy] != -1)
            return DP[ind][buy];

        int profit = 0;
        if (buy)
            profit = max(-stock[ind] + fun(stock, ind + 1, false, fee, DP), fun(stock, ind + 1, true, fee, DP));

        else
            profit = max(+stock[ind] + fun(stock, ind + 1, true, fee, DP) - fee, fun(stock, ind + 1, false, fee, DP));


        return DP[ind][buy] = profit;
    }



    //Without Space Optimized.
    int Tabulation1(vector<int>& stock, int fee) {
        int n = stock.size();
        vector<vector<int>> DP(n + 1, vector<int>(2, 0));

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {

                int profit = 0;
                if (buy)
                    profit = max(-stock[ind] + DP[ind + 1][false], DP[ind + 1] [true]);

                else
                    profit = max(+stock[ind] + DP[ind + 1][true] - fee, DP[ind + 1][false]);
                DP[ind][buy] = profit;
            }

        }

        return DP[0][true];
    }



    //Space Optimized.
    int Tabulation2(vector<int>& stock, int fee) {
        int n = stock.size();
        vector<int> DP(2, 0);

        for (int ind = n - 1; ind >= 0; ind--) {
            vector<int> curr(2, 0);

            for (int buy = 0; buy <= 1; buy++) {

                int profit = 0;
                if (buy)
                    profit = max(-stock[ind] + DP[false], DP[true]);

                else
                    profit = max(+stock[ind] + DP[true] - fee, DP[false]);
                curr[buy] = profit;
            }

            DP = curr;

        }

        return DP[true];
    }

public:
    int maxProfit(vector<int>& prices, int fee) {
        // vector<vector<int>> DP(prices.size(), vector<int>(2, -1));
        // return fun(prices, 0, true, fee, DP);

        return Tabulation2(prices, fee);
    }
};