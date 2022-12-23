// 3D DP that's all, rest part is same as part II .
// In this part we limiting the transaaction only two times, so carry one transaction variable
// that detones how many transatios are completed yet. If we used 2 transaction it means we
// cannot buy any stock further, so in this case we use a 3D DP for this.


class Solution {
    // Memoization
    int fun(vector<int>& stock, int ind, bool buy, vector<vector<vector<int>>> &DP, int trnctn) {
        // If all days are exhausted then return 0 cuz there will be no profit.
        if (ind == stock.size())
            return 0;

        // Initialize profit to 0
        int profit = 0;

        // Check if already have been calculated or not.
        if (DP[ind][buy][trnctn] != -1)
            return DP[ind][buy][trnctn];

        // If we used all 2 transactions.
        if (trnctn == 0)
            return DP[ind][buy][trnctn] = profit;

        if (buy)
            // profit = max(buy the current stock, not buy the  current stock)
            // If buyed then (sell - buy = profit) that's why there is -stock[ind], beacuse  you bought the stock and MONEY IS GONE, else don't buy so there is 0 .

            profit = max(-stock[ind] + fun(stock, ind + 1, false, DP, trnctn), 0 + fun(stock, ind + 1, true, DP, trnctn));
        else
            // To sell the stock we do +stock[ind] beacuse MONEY IS COMING.
            // ++one more thing, after a sell is completed it means we used 1 transaction,
            // so after sell when we call fun() we pass (trnctn - 1) cuz 1 transation is used.++

            profit = max(+stock[ind] + fun(stock, ind + 1, true, DP, trnctn - 1), 0 + fun(stock, ind + 1, false, DP, trnctn));

        // Memoization.
        return DP[ind][buy][trnctn] = profit;

    }




    // Tabulation Without Space Optimization.
    int Tabulation1(vector<int>& stock) {
        int n = stock.size();

        vector<vector<vector<int>>> DP(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        //Recurrence. (There are three loops because it is 3D DP state)
        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int transaction = 1; transaction <= 2; transaction++) {
                    int profit = 0;
                    if (buy)
                        profit = max(-stock[ind] + DP[ind + 1][buy][transaction], 0 + DP[ind + 1][buy][transaction]);
                    else
                        profit = max(+stock[ind] + DP[ind + 1][buy][transaction - 1], 0 + DP[ind + 1][buy][transaction]);

                    DP[ind][buy][transaction] = profit;
                }
            }
        }

        return DP[0][1][2];

    }




    // Tabulation With Space Optimization. (used vector of size 2*3 = 6)
    int Tabulation2(vector<int>& stock) {
        int n = stock.size();

        vector<vector<int>> DP(2, vector<int>(3, 0));

        //Recurrence. (There are three loops because it is 3D DP state)
        for (int ind = n - 1; ind >= 0; ind--) {
            // 'curr' vector will become my previous vector.
            /*
                c = calculate
                a = b
                b = c

                If you know what I mean by this.
            */
            vector<vector<int>> curr(2, vector<int>(3, 0));

            for (int buy = 0; buy <= 1; buy++) {

                for (int transaction = 1; transaction <= 2; transaction++) {

                    int profit = 0;
                    if (buy)
                        profit = max(-stock[ind] + DP[false][transaction], 0 + DP[true][transaction]);
                    else
                        profit = max(+stock[ind] + DP[true][transaction - 1], 0 + DP[false][transaction]);

                    curr[buy][transaction] = profit;
                }
            }
            // Copy 'curr' to the 'DP' beacuse DP is become previous for next 'ind'
            DP = curr;
        }

        return DP[1][2];

    }



public:
    int maxProfit(vector<int>& prices) {
        // vector<vector<vector<int>>> DP(prices.size(), vector<vector<int>>(2, vector<int>(3, -1)));
        // return fun(prices, 0, 1, DP, 2);

        return Tabulation2(prices);
    }
};