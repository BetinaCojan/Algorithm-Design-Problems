#include <fstream>

using namespace std;

// Check value on (x,y) position in walsh matrix
bool check_walsh(int N, int x, int y) {
	bool result = false;

	while (N != 1) {
		// If the coords are in the 4-th submatrix
		// negate the result
		if (x > N / 2 && y > N / 2)
			result = !result;

		// Translate the coords to the 1-st submatrix
		if (x > N / 2)
			x -= N / 2;

		if (y > N / 2)
			y -= N / 2;

		N /= 2;
	}

	return result;
}

int main() {
	ifstream in("walsh.in");
	ofstream out("walsh.out");
	int N, K, x, y;

	in >> N >> K;

	// Check the value for every coord in the input file
	for (int i = 0; i < K; i++) {
		in >> x >> y;
		out << check_walsh(N, x, y) << '\n';
	}

	return 0;
}
