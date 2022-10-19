
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <iostream>


#define MOD 1000000007

using namespace std;

// Count how many distinct chars
int cnt_distinct(string str) {
    unordered_set<char> s;

    for (uint i = 0; i < str.size(); i++) {
        s.insert(str[i]);
    }

    return s.size();
}

// Solve using dp
long long solve(string K, string S) {
	int no_marks = (int)count(K.begin(), K.end(), '?');
	int no_letters = cnt_distinct(S);
	long long D[S.length()][K.length()];
	long long result;

	for (uint i = 0; i < S.length(); i++) {
		for (uint j = 0; j < K.length(); j++) {
			// Partial sum with the previous value
			D[i][j] = (j == 0) ? 0 : D[i][j - 1];

			// Intantiate first row
			if (i == 0) {
				if (K[j] == S[i])
					D[i][j] += no_letters;
				if (K[j] == '?')
					D[i][j] += 1;

				continue;
			}

			// Cant form substrings of length i with only j chars
			if (j < i) {
				D[i][j] = 0;
				continue;
			}

			// If the letters are matching, get the previous sum
			// and multiply by numbers of distinct letters
			// because we can have ? in K
			if (K[j] == S[i]) {
				D[i][j] = (D[i][j] + D[i - 1][j - 1] * no_letters) % MOD;
			}

			// If the letter is ?, it means the only no_letters values
			// are our match, so dont perform furter multiplication
			if (K[j] == '?')
				D[i][j] = (D[i][j] + D[i - 1][j - 1]) % MOD;
		}
	}

	result = D[S.length() - 1][K.length() - 1];

	// Perform further multiplication or divisor
	if (no_marks - (int)S.length() > 0) {
		for (int i = 0; i < no_marks - (int)S.length(); i++)
			result = (result * no_letters) % MOD;
	} else {
		for (int i = 0; i < (int)S.length() - no_marks; i++)
			result = result / no_letters;
	}

	return result;
}

int main() {
	ifstream in("crypto.in");
	ofstream out("crypto.out");
	int N, L;
	string K, S;

	in >> N >> L;
	in >> K >> S;

	out << solve(K, S);

	return 0;
}
