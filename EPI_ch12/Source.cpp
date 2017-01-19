#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#pragma region 12.1
int SearchFirstOfK(const vector<int>& v, int k) {
	int l = 0;
	int u = v.size() - 1;
	int m;
	bool found = false;

	while (l <= u) {
		m = l + (u - l) / 2;
		if (k == v[m]) {
			found = true;
			break;
		}
		else if (k < v[m]) {
			u = m-1;
		}
		else {
			l = m+1;
		}
	}

	if (found){
		while (m > 0 && v[m - 1] == k) {
			m--;
		}
		return m;
	}
	else return -1;
}

void SearchFirstOfKTest() {
	vector<int> v = { {-14,-10,2,108,108,243,285,285,285,401} };
	cout << "v = { ";
	for (int i : v) {
		cout << i << " ";
	}
	cout << "}" << endl;

	vector<int> keys = { {108,285,1,-14,-20,401,500} };
	for (int k : keys) {
		int idxK = SearchFirstOfK(v, k);
		if (idxK >= 0) {
			cout << "First occurrence of " << k << " at v[" << idxK << "]." << endl;
		}
		else {
			cout << k << " is not in vector v." << endl;
		}
	}
	return;
}
#pragma endregion

#pragma region 12.4 Integer Square Root
int IntegerSquareRoot(const int n) {
	int res = 1;
	int l = 1;
	int u = n-1;
	int m;
	while (l <= u) {
		m = l + (u - l) / 2;
		int square = m*m;
		if (square < n) {
			res = m;	// remember this
			l = m + 1;
		}
		else if (square == n) {
			res = m;
			break;
		}
		else {
			u = m - 1;
		}
	}
	return res;
}

void IntegerSquareRootTest() {
	vector<int> numbers = { { 1,2,4,16,21,25,300 } };
	for (int n : numbers) {
		cout << "IntSqrt(" << n << ") = " << IntegerSquareRoot(n) << endl;
	}
	return;
}
#pragma endregion

#pragma region 12.8 Kth largest element
int kLargestElem(const int k, vector<int>& v) {
	if (k <= 0 || k > v.size()) { throw new logic_error("kLargestElem: Invalid k value."); }

	int iPivot = 0, l = 0, u = v.size() - 1;
	while (l <= u) {
		iPivot = l;
		// partition around the pivot:
		for (int i = l+1; i <= u; i++) {
			if (v[i] > v[iPivot]) {
				std::swap(v[iPivot], v[i]);
				iPivot++;
				std::swap(v[iPivot], v[i]);
			}
		}
		if (iPivot == (k - 1)) break;
		else if (iPivot > (k-1) ) {
			// kth element is in the lower half.
			u = iPivot - 1;
		}
		else {
			// kth element is in the upper half.
			l = iPivot + 1;
		}
	}
	return v[iPivot];
}

void kLargestElemTest() {
	vector<int> v1 = { { 1,2,4,16,21,25,300 } };
	for (int k = 1; k <= v1.size(); k++ ) {
		cout << k << "th largest element: " << kLargestElem(k, v1) << endl;
	}
	vector<int> v2 = { { 3,2,1,5,4 } };
	for (int k = 1; k <= v2.size(); k++) {
		cout << k << "th largest element: " << kLargestElem(k, v2) << endl;
	}

	return;
}
#pragma endregion

void main() {
	/* 12.1 */
	//SearchFirstOfKTest();

	/* 12.4 */
	//IntegerSquareRootTest();

	/* 12.8 */
	kLargestElemTest();

	return;
}