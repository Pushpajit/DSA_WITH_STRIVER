class Solution {
    int fun(vector<int>& stock, int ind, bool buy, vector<vector<int>> &DP) {
        // If all days are exhausted then return 0 cuz there will be no profit.
        if (ind == stock.size())
            return 0;

        // Initialize profit to 0
        int profit = 0;

        // Check if already have been calculated or not.
        if (DP[ind][buy] != -1)
            return DP[ind][buy];

        if (buy)
            // profit = max(buy the current stock, not buy the  current stock)
            // If buyed then (sell - buy = profit) that's why there is -stock[ind], beacuse  you bought the stock and MONEY IS GONE, else don't buy so there is 0 .

            profit = max(-stock[ind] + fun(stock, ind + 1, false, DP), 0 + fun(stock, ind + 1, true, DP));
        else
            // To sell the stock we do +stock[ind] beacuse MONEY IS COMING.

            profit = max(+stock[ind] + fun(stock, ind + 1, true, DP), 0 + fun(stock, ind + 1, false, DP));

        // Memoization.
        return DP[ind][buy] = profit;

    }



    // Without Space Optimization.
    int Tabulation1(vector<int>& stock) {
        int n = stock.size();
        vector<vector<int>> DP(n + 1, vector<int>(2, -1));

        //Base case.
        DP[n][true] = DP[n][false] = 0;

        //Recurrence.
        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 1; buy >= 0; buy--) {

                int profit = 0;
                if (buy)
                    profit = max(-stock[ind] + DP[ind + 1][false], 0 + DP[ind + 1][true]);
                else
                    profit = max(+stock[ind] + DP[ind + 1][true], 0 + DP[ind + 1][false]);

                DP[ind][buy] = profit;
            }
        }

        return DP[0][1];
    }



    // Space optimized, vector of size 2
    int Tabulation2(vector<int>& stock) {
        int n = stock.size();
        vector<int> DP(2, -1);

        //Base case.
        DP[true] = DP[false] = 0;

        //Recurrence.
        for (int ind = n - 1; ind >= 0; ind--) {
            // 'curr' vector will become my previous vector.
            /*
                c = calculate
                a = b
                b = c

                If you know what I mean by this.
            */
            vector<int> curr(2, 0);

            for (int buy = 1; buy >= 0; buy--) {

                int profit = 0;
                if (buy)
                    profit = max(-stock[ind] + DP[false], 0 + DP[true]);
                else
                    profit = max(+stock[ind] + DP[true], 0 + DP[false]);

                curr[buy] = profit;
            }
            // Copy 'curr' to the 'DP' beacuse DP is become previous for next 'ind'
            DP = curr;
        }

        return DP[1];
    }

public:
    int maxProfit(vector<int>& prices) {
        // vector<vector<int>> DP(prices.size(), vector<int>(2, -1));
        // return fun(prices, 0, 1, DP);
        return Tabulation2(prices);
    }
};