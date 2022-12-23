// Same as part III
// last one was we can only do at most 2 transactions.
// This one we can do at most K transaction and rest are same.

class Solution {
    int fun(vector<int>& stock, int ind, bool buy, vector<vector<vector<int>>> &DP, int trnctn) {
        // If all days are exhausted then return 0 cuz there will be no profit.
        if (ind == stock.size())
            return 0;

        // Initialize profit to 0
        int profit = 0;

        // Check if already have been calculated or not.
        if (DP[ind][buy][trnctn] != -1)
            return DP[ind][buy][trnctn];

        // If we used all k transactions.
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
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<vector<int>>> DP(prices.size(), vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return fun(prices, 0, true, DP, k);
    }
};