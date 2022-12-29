class Solution {
public:
	int LongestBitonicSequence(vector<int>nums)
	{
		int n = nums.size();
		vector<int> front(n, 1); // For storing the LIS from the begining.
		vector<int> back(n, 1); // For storing the LIS from the reverse.

		// Straight Forward LIS.
		for (int i = 0; i < n; i++) {

			for (int j = 0; j < i; j++) {

				// From 0 to i - 1
				if (nums[j] < nums[i] && front[j] + 1 > front[i])
					front[i] = front[j] + 1; // Update the DP[i] if we found greater length.

				// From n - 1 to (n - 1 - i) + 1
				// You can assume it as from last index to (i - 1)th index from reverse direction.
				if (nums[n - 1 - j] < nums[n - 1 - i] && back[n - 1 - j] + 1 > back[n - 1 - i])
					back[n - 1 - i] = back[n - 1 - j] + 1; // Update the DP[n - 1 - i] if we found greater length.

			}
		}

		// For storing longest bitonic sequence length.
		int maxlen = 0;

		for (int i = 0; i < n; i++) {
			// Add up front[i] + back[i] then -1 because we count current element double time.
			// Update the maxlen.
			maxlen = max(maxlen, front[i] + back[i] - 1);

		}


		return maxlen;
	}
};