// Very simple as part III and part IV
// There is a cooldown factor only, after a transaction complete just skip to the next day
// because there is one day for cooldown.

class Solution {
    int fun(vector<int>& stock, int ind, bool buy, bool cooldown, vector<vector<vector<int>>> &DP) {
        // If all days are exhausted then return 0 cuz there will be no profit.
        if (ind == stock.size())
            return 0;

        // Check if already have been calculated or not.
        if (DP[ind][buy][cooldown] != -1)
            return DP[ind][buy][cooldown];

        int profit = 0;

        // profit = max(buy the current stock, not buy the  current stock)
        // If buyed then (sell - buy = profit) that's why there is -stock[ind], beacuse  you bought the stock and MONEY IS GONE, else don't buy so there is 0 .
        if (buy && !cooldown)
            profit = max(-stock[ind] + fun(stock, ind + 1, false, false, DP), fun(stock, ind + 1, true, false, DP));

        else if (cooldown) //If there is a cooldown then simply skip to the next day with cooldown = false.
            profit = 0 + fun(stock, ind + 1, true, false, DP);

        else
            //After a transaction completed mark pass cooldown = true.
            profit = max(+stock[ind] + fun(stock, ind + 1, true, true, DP), fun(stock, ind + 1, false, false, DP));

        // Memoization.
        return DP[ind][buy][cooldown] = profit;
    }




    // Tabulation Without Space Optimization.
    int Tabulation1(vector<int>& stock) {
        int n = stock.size();
        vector<vector<vector<int>>> DP(n + 1, vector<vector<int>>(2, vector<int>(2, 0)));

        //Recurrence. (There are three loops because it is 3D DP state)
        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cldwn = 0; cldwn <= 1; cldwn++) {

                    int profit = 0;
                    if (buy && !cldwn)
                        profit = max(-stock[ind] + DP[ind + 1][false][false], DP[ind + 1][true][false]);
                    else if (cldwn)
                        profit = 0 + DP[ind + 1][true][false];
                    else
                        profit = max(+stock[ind] + DP[ind + 1][true][true], DP[ind + 1][false] [false]);
                    DP[ind][buy][cldwn] = profit;
                }
            }
        }

        return DP[0][true][false];
    }




    // Tabulation With Space Optimization. (used vector of size 2*2 = 4)
    int Tabulation2(vector<int>& stock) {
        int n = stock.size();
        vector<vector<int>> DP(2, vector<int>(2, 0));

        //Recurrence. (There are three loops because it is 3D DP state)
        for (int ind = n - 1; ind >= 0; ind--) {
            // 'curr' vector will become my previous vector.
            /*
                c = calculate
                a = b
                b = c

                If you know what I mean by this.
            */
            vector<vector<int>> curr(2, vector<int>(2, 0));

            for (int buy = 0; buy <= 1; buy++) {
                for (int cldwn = 0; cldwn <= 1; cldwn++) {

                    int profit = 0;
                    if (buy && !cldwn)
                        profit = max(-stock[ind] + DP[false][false], DP[true][false]);
                    else if (cldwn)
                        profit = 0 + DP[true][false];
                    else
                        profit = max(+stock[ind] + DP[true][true], DP[false][false]);
                    curr[buy][cldwn] = profit;
                }
            }
            // Copy 'curr' to the 'DP' beacuse DP is become previous for next 'ind'
            DP = curr;
        }

        return DP[true][false];
    }

public:
    int maxProfit(vector<int>& stock) {
        // vector<vector<vector<int>>> DP(stock.size(), vector<vector<int>>(2, vector<int>(2, -1)));
        // return fun(stock, 0, true, false, DP);

        return Tabulation2(stock);
    }
};