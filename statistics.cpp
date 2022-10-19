#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Compute an array of how dominant a letter is
// in every word, also given the length of that word
void compute_dominance(vector<float> &domin,
					   vector<string> &words, char letter) {
	for (uint i = 0; i < words.size(); i++) {
		string word = words[i];
		int occurencies = (int)count(word.begin(), word.end(), letter);

		// Metric for dominance
		domin[i] = occurencies - (float)word.length() / 2;
	}
}

// Return the maximum number of words where letter
// is dominant if we concatenate them.
int solve_for_letter(vector<string> &words, char letter) {
	vector<float> domin(words.size());
	float sum = 0;

	// Get the dominance metric for every word
	compute_dominance(domin, words, letter);

	// Sort descending, to get most dominant ones
	sort(domin.begin(), domin.end(), greater<>());

	// Count the words until our dominance sum reaches almost 0
	for (uint i = 0; i < domin.size(); i++) {
		sum += domin[i];

		if (sum <= 0) {
			return (i == 0) ? -1 : i;
		}
	}

	return words.size();
}

int main() {
	ifstream in("statistics.in");
	ofstream out("statistics.out");
	vector<string> words;
	int N, max = -1;

	// Read input words
	in >> N;
	for (int i = 0; i < N; i++) {
		string word;

		in >> word;
		words.push_back(word);
	}

	// Get the maximum words for every possible letter
	for (char letter = 'a'; letter <= 'z'; letter++) {
		int result = solve_for_letter(words, letter);

		if (result > max)
			max = result;
	}

	out << max;

	return 0;
}
