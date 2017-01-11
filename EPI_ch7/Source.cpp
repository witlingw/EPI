#include <iostream>
#include <string>
#include <map>

using namespace std;

/* 7.1 */
string IntToString(int i) {
	int n = 1; // for \0
	if (i < 0) {
		n++;
		n += ceil(log10(abs(i)));
	}
	
	char* s = new char[n];
	snprintf(s,n, "%d", i);
	string str(s);
	delete[n] s;
	return str;
}

int StringToInt(const string& s) {
	int integer = 0, w=1;

	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[i] >= '0' && s[i] <= '9') {
			integer += (s[i] - '0')*w;
			w *= 10;
		}
		else if (s[i] == '-') integer *= -1;
	}

	return integer;
}

/* 7.2 */
int DigitToInt(char c) {
	if (c >= '0' && c <= '9') { //isdigit(c)
		return c - '0';
	}
	else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	}
	else return -1; //error
}

string ConvertBase(const string& number_b1, int b1, int b2) {
	static char digit[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	
	//from b1 to 10
	unsigned int n = 0;
	for (int i = number_b1.size()-1, w = 1; i >=0 ; i--, w*=b1) {
		n += DigitToInt(number_b1[i])*w;
	}

	//from 10 to b2
	string s;
	do {
		int i = n%b2;
		s += digit[i];
		n /= b2;
	} while (n > 0);

	reverse(s.begin(), s.end());
	return s;
}

int main() {
	///* 7.1 */
	//int i = -137;
	//string s = "-1996";

	//cout << IntToString(i) << endl;
	//cout << StringToInt(s) << endl;

	/* 7.2 */
	string number_b1 = "615"; 
	int b1 = 7, b2 = 13;
	string number_b2 = ConvertBase(number_b1, b1, b2);

	cout << number_b1 << " b_" << b1 << " --> " << number_b2 << " b_"<< b2 << endl;

	return 0;
}