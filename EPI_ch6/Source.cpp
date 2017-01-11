#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

void DutchPartitioning(vector<int>* A_ptr, int pivot_idx) {
	vector<int>& A = *A_ptr;
	int pivot = A[pivot_idx];

	pivot_idx = 0;
	int i = 0;
	int j = A.size() - 1;
	while (i < j && pivot_idx <= j) {
		if (A[pivot_idx] < pivot) {
			swap(A[pivot_idx], A[i]);
			i++;
 			pivot_idx++;
		}
		else if (A[pivot_idx] > pivot) {
			swap(A[pivot_idx], A[j]);
			j--;
		}
		else { // A[i] == pivot
			pivot_idx++;
		}
		copy(A.begin(), A.end(), ostream_iterator<int>(cout, ","));
		cout << endl;
	}
}

double BuyAndSellStockOnce(const vector<double>& prices, int& b_day, int& s_day) {
	/*b_day = 0;
	s_day = distance(prices.begin(), max_element(prices.begin() + 1, prices.end()));
	double max_profit = prices[s_day] - prices[b_day];

	for (int i = 0; i < prices.size()-1; i++) {
		if (prices[i] < prices[b_day]) {
			if (i < s_day) {
				b_day = i;
				max_profit = prices[s_day] - prices[b_day];
			}
			else {
				int j = distance(prices.begin(), max_element(prices.begin() + i + 1, prices.end()));
				double new_profit = prices[j] - prices[i];
				if (new_profit > max_profit) {
					b_day = i;
					s_day = j;
					max_profit = new_profit;
				}
			}
		}
	}*/

	s_day = prices.size() - 1;
	int max_price_idx = s_day;
	double max_profit = numeric_limits<double>::min();

	for (int i = s_day-1; i >= 0; i--) {
		if (prices[i] > prices[max_price_idx]) {
			max_price_idx = i;
		}
		else {
			double profit_if_bought_today = prices[max_price_idx] - prices[i];
			if (profit_if_bought_today > max_profit) {
				b_day = i;
				s_day = max_price_idx;
				max_profit = profit_if_bought_today;
			}
		}
	}

	return max_profit;
}

void subSpiralOrdering(const vector<vector<int>>& matrix, int start, int end, vector<int>& spiral_order) {
	//first row
	for (int j = start; j <= end; j++) {
		spiral_order.push_back(matrix[start][j]);
	}
	if ((end - start) > 0) { //at least 2x2 matrix
		//last column
		for (int i = start + 1; i <= end; i++) {
			spiral_order.push_back(matrix[i][end]);
		}
		//last row
		for (int j = end - 1; j >= start; j--) {
			spiral_order.push_back(matrix[end][j]);
		}
		//first column
		for (int i = end - 1; i > start; i--) {
			spiral_order.push_back(matrix[i][start]);
		}
		if ((end - start) > 1) { //at least 3x3 matrix
			subSpiralOrdering(matrix, start + 1, end - 1, spiral_order);
		}
	}
	return;
}

vector<int> SpiralOrdering(const vector<vector<int>>& matrix) {
	vector<int> spiral_order;
	size_t n = matrix.size();

	subSpiralOrdering(matrix, 0, n-1, spiral_order);
	return spiral_order;
}

int main() {
	///* 6.1 */
	//vector<int> A = {8,9,6,7,2,2,1,3,9,5,10,3};
	//DutchPartitioning(&A, 4);
	//
	//copy(A.begin(), A.end(), ostream_iterator<int>(cout, ","));
	//cout << endl;

	///* 6.6 */
	//vector<double> A = { 310,315,275,295,260,270,290,230,255,250 };
	//int b_day, s_day;
	//double profit = BuyAndSellStockOnce(A, b_day, s_day);
	//
	//cout << "Max profit: " << profit << " buying in day "<<b_day<<" and selling in day "<<s_day<<endl;
	
	/* 6.17 */
	vector<vector<int>> A = {	{	1,	2,	3	},
								{	4,	5,	6	},
								{	7,	8,	9	}	};

	vector<vector<int>> B = {	{	1,	2,	3,	4	},
								{	5,	6,	7,	8	},
								{	9,	10,	11,	12	},
								{	13,	14,	15,	16	}	};

	vector<vector<int>> C = {	{	1,	2,	3,	4,	5	},
								{	6,	7,	8,	9,	10	},
								{	11,	12,	13,	14,	15	},
								{	16,	17,	18,	19,	20	},
								{	21,	22,	23,	24,	25	}	};

	auto v_a = SpiralOrdering(A);
	auto v_b = SpiralOrdering(B);
	auto v_c = SpiralOrdering(C);

	std::cout << "Matrix A:" << endl;
	copy(v_a.begin(), v_a.end(), ostream_iterator<int>(std::cout, ","));
	std::cout << endl;

	cout << "Matrix B:" << endl;
	copy(v_b.begin(), v_b.end(), ostream_iterator<int>(std::cout, ","));
	std::cout << endl;

	cout << "Matrix C:" << endl;
	copy(v_c.begin(), v_c.end(), ostream_iterator<int>(std::cout, ","));
	std::cout << endl;

	return 0;
}