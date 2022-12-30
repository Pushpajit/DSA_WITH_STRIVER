
/*
DP on partition rules:
    1. Start with the entire block/array
    2. Represent the funtion as "f(i, j)" <-- i is starting and j is ending point.
    3. Try all partition, run a for loop for this [ for(k = i to j - 1) ] .
    4. Return the best possible 2 partition.

● (i == j) return 0 (for single matrix cost is 0)
● curr_cost = arr[i - 1] * arr[k] * arr[j]
● call = f(i, k) + f(k+1, j)
● total_operation = curr_cost + call
● find minimum of all total_operation
● return minimum of them

*/



class Solution
{
public:

    int partition(vector<int> &arr, int i, int j, vector<vector<int>> &DP) {
        // If we have only one partition (The single array itself), so the operation is 0.
        if (i == j) return 0;

        //For storing the minimum cost.
        int mincost = 1e9;

        //Do not recalculate.
        if (DP[i][j] != -1) return DP[i][j];

        //ABCD --> (A)(BCD), (AB)(CD), (ABC)(D) This will be the partitions.
        //current cost for example (A)(BCD) = 10[20][30,40,50] => 10x20 X (20x30 X 30x40 X 40x50)
        // => 10x20 X (20x40 X 40x50) => 10x20(A) X (20x50)(BCD)
        // So the cost will be 10x20x50 => (arr[i - 1] * arr[k] * arr[j])
        for (int k = i; k < j; k++) {
            // Then call for both parts i.e partition(i, k) and partition(k+1, j)
            int cost = (arr[i - 1] * arr[k] * arr[j]) + partition(arr, i, k, DP) + partition(arr, k + 1, j, DP);

            // Find minimum of all costs.
            mincost = min(mincost, cost);
        }

        //Memoization and return.
        return DP[i][j] = mincost;
    }





    int Tabulation(vector<int> &arr, int N) {
        vector<vector<int>> DP(N, vector<int>(N));

        // Whatever we do in recusion, just do the opposite.
        // i(N-1 to 1) cuz in recurrsion we do i(1 to N-1)
        for (int i = N - 1; i >= 1; i--) {
            // j(i + 1 to N - 1) cuz in recurrsion we do j(N-1 to 1)
            // Because j is at the right of i, so it never gonna go left of i, so start j from i + 1
            for (int j = i + 1; j <= N - 1; j++) {

                int mincost = INT_MAX;
                // Copy down the recurrence simply, don't think.
                for (int k = i; k < j; k++) {

                    int cost = (arr[i - 1] * arr[k] * arr[j]) + DP[i][k] + DP[k + 1][j];

                    mincost = min(mincost, cost);
                }

                DP[i][j] = mincost;
            }
        }


        // The answer will store here, (remember when we call recursion f(arr, 1, N - 1))
        return DP[1][N - 1];
    }



    int matrixMultiplication(vector<int> &arr, int N) {

        //vector<vector<int>> DP(N, vector<int>(N, -1));
        //return partition(arr, 1, N - 1, DP);

        return Tabulation(arr, N);
    }

};

