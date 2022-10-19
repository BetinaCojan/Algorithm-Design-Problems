
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Get all divisors for all numbers between 1 and N
// using a sieve
void get_n_divisors(vector<vector<int>> &divisor, int N) {
	for (int i = 1; i <= N; i++) {
		for (int j = i; j <= N; j += i) {
			divisor[j].push_back(i);
		}
	}
}

// BFS-like implementation for no of operations
// using a queue
void get_steps_array(vector<int> &steps,
					 vector<vector<int>> &divisor, int max_target) {
	queue<int> q;
	int front;

	q.push(1);
	while (!q.empty()) {
		front = q.front();
		q.pop();

		for (uint i = 0; i < divisor[front].size(); i++) {
			int next = front + divisor[front][i];

			if (next <= max_target && steps[next] == 0) {
				steps[next] = steps[front] + 1;
				q.push(next);
			}
		}
	}
}

// Hapsack implementation
int get_max_profit(vector<int> &weights, vector<int> &profits, int K) {
	int D[2][K + 1], l = 0;

	// Initialize dp matrix with 0
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j <= K; j++) {
			D[i][j] = 0;
		}
	}

	// DP[i][cw] = Max profit for i items with cw weight
	// DP[i][cw] = max(DP[i-1][cw], DP[i-1][cw-W[i]] + P[i])
	for(uint i = 1; i <= weights.size(); ++i, l = 1 - l) {
		for(int cw = 0; cw <= K; ++cw) {
			D[1 - l][cw] = D[l][cw];

			if(weights[i - 1] <= cw)
				D[1 - l][cw] = max(D[1 - l][cw],
								   D[l][cw - weights[i - 1]] + profits[i - 1]);
		}
	}

	return D[l][K];
}

int main() {
	ifstream in("prinel.in");
	ofstream out("prinel.out");
	int N, K, val, max_target;
	vector<int> targets, profits, weights;

	// Read targets and profits
	in >> N >> K;

	for (int i = 0; i < N; i++) {
		in >> val;
		targets.push_back(val);
	}
	for (int i = 0; i < N; i++) {
		in >> val;
		profits.push_back(val);
	}

	max_target = *max_element(targets.begin(), targets.end());

	vector<vector<int>>  divisor(max_target + 1, vector<int>());
	vector<int> steps(max_target + 1, 0);

	// Get all divisors for numbers from 1 to maximum target
	get_n_divisors(divisor, max_target);

	// Get no of operations for all numbers from 1 to max target
	get_steps_array(steps, divisor, max_target);

	// Create the weighth array based on these operations
	for (int i = 0; i < N; i++)
		weights.push_back(steps[targets[i]]);

	out << get_max_profit(weights, profits, K) << '\n';

	return 0;
}
