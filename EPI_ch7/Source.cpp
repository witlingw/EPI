#include <iostream>
#include <string>
#include <locale>
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

#pragma region 7.5 Test Palindromicity

bool IsPalindromic(const string s) {
	int idx_start = 0;
	int idx_end = s.size()-1;

	while (idx_start < idx_end) {
		// advance to next letter from beginning 
		while (!isalnum(s[idx_start])) {
			idx_start++;
		}

		// advance to next letter from beginning
		while (!isalnum(s[idx_end])) {
			idx_end--;
		}

		if (idx_start < idx_end && tolower(s[idx_start]) != tolower(s[idx_end]))
			return false;
		else {
			idx_start++;
			idx_end--;
		}
	}
	return true;
}

void IsPalindromicTest() {
	string strings[] = {	"A man, a plan, a canal, Panama.",
							"Able was I, ere I saw Elba",
							"Ray a Ray" };

	for each(string s in strings) {
		cout << "\"" << s << "\"" << (IsPalindromic(s)? " is palindromic." : " isn't palindromic.") << endl;
	}
}

#pragma endregion

#pragma region 7.6 Reverse all the words in a sentence
void ReverseSentence(string* sentence) {
	// reverse all the chars
	auto it_begin = sentence->begin();
	auto it_end = sentence->end() - 1;
	while (it_begin < it_end) {
		std::swap(*it_begin, *it_end);
		it_begin++;
		it_end--;
	}

	// search word limits
	int i_start_word = 0;
	int i_end_word = 0;
	while(i_start_word < sentence->length()){
		//search first non-space char
		while (i_start_word < sentence->length()) {
			if (!isspace((*sentence)[i_start_word]))
				break; // first char found
			i_start_word++;
		}

		//search first space char
		i_end_word = i_start_word + 1;
		while (i_end_word < sentence->length()) {
			if (isspace((*sentence)[i_end_word]))
				break; // first space found
			i_end_word++;
		}

		// reverse word
		for (int i = i_start_word, j = i_end_word-1; i < j; i++, j--) {
			std::swap((*sentence)[i], (*sentence)[j]);
		}
		i_start_word = i_end_word + 1;
	}
}

void ReverseSentenceTest() {
	string sentences[] = {	"Alice likes Bob",
							"every kind of sugar!" };

	for each (string s in sentences) {
		cout << "\"" << s << "\" --> \"";
		ReverseSentence(&s);
		cout << s << "\"" << endl;
	}
}

#pragma endregion


int main() {
	///* 7.1 */
	//int i = -137;
	//string s = "-1996";

	//cout << IntToString(i) << endl;
	//cout << StringToInt(s) << endl;

	///* 7.2 */
	//string number_b1 = "615"; 
	//int b1 = 7, b2 = 13;
	//string number_b2 = ConvertBase(number_b1, b1, b2);

	//cout << number_b1 << " b_" << b1 << " --> " << number_b2 << " b_"<< b2 << endl;

	/* 7.5 */
	//IsPalindromicTest();

	/* 7.6 */
	ReverseSentenceTest();

	return 0;
}