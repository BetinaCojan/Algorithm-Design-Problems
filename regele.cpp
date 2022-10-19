#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

// Get required merchants for every X
void get_merchants(vector<int> &merchants, vector<int> &coords) {
	vector<int> distances;
	int saved_i;

	// Get the array of distances between cities
	for (uint i = 0; i < coords.size() - 1; i++) {
		distances.push_back(coords[i + 1] - coords[i]);
	}

	merchants.push_back(0);
	while (!distances.empty()) {
		int max = -1;

		// If only one left, push it
		if (distances.size() == 1) {
			merchants.push_back(merchants[merchants.size() - 1] + distances[0]);
			break;
		}

		// Get the pair with maximum sum
		for (uint i = 0; i < distances.size() - 1; i++) {
			if (distances[i] + distances[i + 1] > max) {
				max = distances[i] + distances[i + 1];
				saved_i = i;
			}
		}

		// Push the maximum sum into the merchants
		merchants.push_back(merchants[merchants.size() - 1] + max);

		// Remove the pair from the distances
		distances.erase(distances.begin() + saved_i);
		distances.erase(distances.begin() + saved_i);
	}
}

// Search for the proper interval
int get_max_cities(vector<int> &merchants, int m, int N) {
	for (uint i = 0; i < merchants.size(); i++) {
		if (merchants[i] > m) {
			return i - 1;
		}
	}

	return N;
}

int main() {
	ifstream in("regele.in");
	ofstream out("regele.out");
	int N, Q, val;
	vector<int> coords, merchants;

	// Read cities coordinates
	in >> N;
	for (int i = 0; i < N; i++) {
		in >> val;
		coords.push_back(val);
	}

	// Get the required merchants for all X
	get_merchants(merchants, coords);

	// Answer every question
	in >> Q;
	for (int i = 0; i < Q; i++) {
		in >> val;
		out << get_max_cities(merchants, val, N) << '\n';
	}


	return 0;
}
