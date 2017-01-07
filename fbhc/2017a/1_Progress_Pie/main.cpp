#include <cmath>
#include <iostream>

double pi = atan(1)*4;
double radianToDegree = 1 / pi * 180.0;

bool solveIsWhite(int percentage, int pointX, int pointY) {
	int centerX = 50;
	int centerY = 50;
	int radius = 50;

	double hypotenuse = sqrt(pow(pointX - centerX, 2) + pow(pointY - centerY, 2));
	if (hypotenuse > radius) {
		// too far from center point, must be white
		return true;
	}

	// leg = cosine * hypotenuse
	double cosine = abs(pointY - centerY) / hypotenuse;
	double rad = acos(cosine);
	double angle = 0;
	if (pointX > centerX && pointY > centerY) {
		// top right
		angle = 90 - rad * radianToDegree;
	} else if (pointX < centerX && pointY > centerY) {
		// bottom right
		angle = 90 + rad * radianToDegree;
	} else if (pointX < centerX && pointY < centerY) {
		// bottom left
		angle = 270 - rad * radianToDegree;
	} else {
		// top left
		angle = 270 + rad * radianToDegree;
	}

	// white if given percentage is less then point's
	return percentage < angle / 3.6;
}

int main(int argc, const char * argv[]) {
	int t, p, x, y;
	bool isWhite;

	std::cin >> t;
	for (int i = 0; i < t; i++) {
		std::cin >> p;
		std::cin >> x;
		std::cin >> y;
		isWhite = solveIsWhite(p, x, y);

		std::cout << "Case #" << (i + 1) << ": " << (isWhite ? "white" : "black") << std::endl;
	}

	return 0;
}
