#include <algorithm>
#include <cmath>
#include <iostream>

int solveMaxTrip(int n, int w[]) {
	std::sort(w, w + n);

	double requiredW = 50;
	int remaining = n;
	for (int j = n - 1;; j--) {
		if (remaining <= 0) {
			return n - j - 1;
		}

		int requiredK = ceil(requiredW / double(w[j]));
		if (requiredK > remaining) {
			// not enough left to make a trip with this item on top
			// the rest should be added on existing trips
			remaining = 0;
			j++;
			continue;
		}

		remaining -= requiredK;
	}
}

int main(int argc, const char * argv[]) {
	int t, n, maxTrip;

	std::cin >> t;
	for (int i = 0; i < t; i++) {
		std::cin >> n;
		
		int w[n];
		for (int j = 0; j < n; j++) {
			std::cin >> w[j];
		}

		maxTrip = solveMaxTrip(n, w);

		std::cout << "Case #" << (i + 1) << ": " << maxTrip << std::endl;
	}

	return 0;
}
