#include <iostream>
#include<fstream>
#include<sstream>
#include <vector>
#include <queue>
#include <functional>
#include <tuple>

using namespace std;

#pragma region 11.1 Merge Sorted Files
using File = vector<int>;

struct FileIterator {
	bool operator>(const FileIterator& that) const {
		return *current > *(that.current);
	}

	File::const_iterator current;
	File::const_iterator end;
};

File MergeSortedFiles( vector<File>& files) {
	
	priority_queue<FileIterator, vector<FileIterator>, std::greater<>> min_heap;

	// Equivalent using lambda function
	/*auto GreaterByTime = [](const FileIterator& it1, const FileIterator& it2) -> bool {
		return *(it1.current) > *(it2.current);
	};
	priority_queue<FileIterator, vector<FileIterator>, std::function<bool(const FileIterator&, const FileIterator&)>> min_heap(GreaterByTime);*/

	// obtain the iterators and fill the priority queue
	for (int i = 0; i < files.size(); i++) {
		FileIterator it = { files[i].begin(), files[i].end() };
		min_heap.push(it);
	}

	File merged_file;
	while (!min_heap.empty()) {
		FileIterator it = min_heap.top();
		min_heap.pop();
		merged_file.push_back(*(it.current));
		it.current++;
		if (it.current != it.end) {
			min_heap.push(it);
		}
		
	}
	return std::move(merged_file);
}

void MergeSortedFilesTest() {
	vector<File> files = {{	{{3,5,7}},			// file1
									{{0,6}},			// file2
									{{0,6,28}}	}};		// file3

	File sorted_file_union = MergeSortedFiles(files);

	cout << "Sorted sequence: ";
	for (auto entry : sorted_file_union) {
		cout << entry << " ";
	}

	return;
}
#pragma endregion

#pragma region 11.4 k Closest Stars to Earth

struct Star {
	double x, y, z;

	double DistanceFromOrigin() const {
		return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
	}

	string ToString() const {
		ostringstream ostream;
		ostream << x << " " << y << " " << z;
		return ostream.str();
	}
	
};

vector<Star> kClosestStars(int k, string filename){
	ifstream ifile(filename);
	if (ifile.is_open()) {

		auto IsCloser = [] (const Star& star1, const Star& star2) -> bool {
				return star1.DistanceFromOrigin() < star2.DistanceFromOrigin();
		};
		priority_queue<Star, vector<Star>, function<bool(Star&, Star&)>> max_heap(IsCloser);

		while (!ifile.eof()) {
			Star star;
			ifile >> star.x >> star.y >> star.z;
			
			if (max_heap.size() < k) {
				max_heap.push(star);
			}
			else if (IsCloser(star, max_heap.top())) {
				max_heap.pop();
				max_heap.push(star);
			}
		}
		ifile.close();

		vector<Star> stars;
		while(!max_heap.empty()) {
			stars.push_back(max_heap.top());
			max_heap.pop();
		}
		reverse(stars.begin(), stars.end());
		return stars;
	}
	else throw new runtime_error("It was not possible to open the file:" + filename + "\n");
}

void kClosestStarsTest() {
	vector<Star> stars = {{ {1,1,1},{3,3,3},{50,60,70} }};

	ofstream ofile("stars.txt", ios::app);
	if (ofile.is_open()) {
		for (Star star : stars) {
			ofile << star.ToString() << endl;
		}
		ofile.close();
	}

	vector<Star> k_closest_stars = kClosestStars(1, "stars.txt");
	for (Star star : k_closest_stars) {
		cout << star.ToString() << endl;
	}

	return;
}

#pragma endregion

void main() {
	/* 11.1 */
	//MergeSortedFilesTest();

	/* 11.4 */
	kClosestStarsTest();

	return;
}