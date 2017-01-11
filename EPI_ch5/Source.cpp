#include <iostream>

using namespace std;

/* 5.8 Reverse Digit */
#pragma region

int ReverseDigit(int x) {
	int result = 0;

	while (x != 0) {
		result = result * 10 + x % 10;
		//x = (int)floor(x / 10);
		x /= 10;
	}

	return result;
}

void ReverseDigitTest() {
	int input[] = { 42,-314, 5,-13 };
	
	for each(int x in input) {
		int y = ReverseDigit(x);
		cout << x << " reverses in " << y << endl;
	}
}

#pragma endregion



void main() {
	// 5.8
	ReverseDigitTest();

	cout << "\nEND." << endl;
	return;
}