#include <iostream>
#include <unordered_map>
#include <list>
#include <unordered_set>

using namespace std;

#pragma region 13.1 Test for Palindromic permutation
bool CanFormPalindrome(string word) {
	unordered_set<char> counter;
	for (char c : word) {
		auto ret = counter.insert(c);
		if (!ret.second) {
			counter.erase(ret.first);
		}
	}
	return counter.size() <= 1;
}

void CanFormPalindromeTest() {
	vector<string> words = { "edified","hello" };

	for (string word : words) {
		if (CanFormPalindrome(word))
			cout << word.c_str() << " is palindromic." << endl;
		else
			cout << word.c_str() << " isn't palindromic." << endl;
	}
	return;
}
#pragma endregion

#pragma region 13.3 ISBN LRU cache

using ISBN = int;

template <size_t k>
class LRUcache {
	
	list<ISBN> LRUqueue_;
	unordered_map<ISBN, pair<list<ISBN>::iterator, double> > cache_;

public:
	bool LookUp(ISBN code, double& retPrice) {
		auto it = cache_.find(code);
		if (it != cache_.end()) {
			MoveToFront(it);
			retPrice = it->second.second;
			return true;
		}
		else {
			return false;
		}
	}

	void Insert(ISBN code, double price) {
		auto it = chache_.find(code);
		if (it != cache_.end()) {
			//already present
			MoveToFront(it);
		}
		else {
			if (LRUqueue_.size() == k) {
				// remove LRU entry
				cache_.erase(LRUqueue_.back());
				LRUqueue_.pop_back();
			}
			LRUqueue_.push_front(code);
			cache_[code] = { LRUqueue_.begin(), price };
		}
	}

	void Erase(ISBN code) {
		auto it = chache_.find(code);
		if (it != cache_.end()) {
			LRUqueue_.erase(it->second.first);
			cache_.erase(it);
		}
	}

	void MoveToFront(unordered_map<ISBN, pair<list<ISBN>::iterator, double>>::iterator& it) {
		LRUqueue_.erase(it->second.first);
		LRUqueue_.push_front(it->first);
		it->second.first = LRUqueue_.begin();
	}
};
#pragma endregion

#pragma region 13.6 Find the Nearest Repeated Entries in an array
int FindNearestRepetition(const vector<string>& sentence) {
	int min_dist = sentence.size() + 1;
	unordered_map<string, int> word_last_occurence;

	for (int i = 0; i < sentence.size(); i++) {
		string word = sentence[i];
		auto it = word_last_occurence.find(word);
		if (it == word_last_occurence.end()) {
			word_last_occurence[word] = i;
		}
		else {
			int dist = i - it->second;
			if (dist < min_dist) min_dist = dist;
			it->second = i;
		}
	}
	return min_dist;
}

void FindNearestRepetitionTest() {
	vector<string> sentence = {"All", "work", "and", "no", "play", "makes", "for", "no", "work", "no", "fun", "and", "no", "results"};
	cout << "Closest repetition distance: " << FindNearestRepetition(sentence) << endl;

	return;
}
#pragma endregion


void main() {
	/* 13.1 */
	//CanFormPalindromeTest();

	/* 13.6 */
	FindNearestRepetitionTest();

	return;
}