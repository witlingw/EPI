#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#pragma region STACK

template <class T>
class Stack {
private:
	struct ElementWithCachedMax {
		T max, element;
	};

	stack<ElementWithCachedMax> _elements;

public:
	bool Empty() { return _elements.empty(); }
	size_t Size() { return _elements.size; }

	void Push(const T& val) {
		cout << "Push(" << val << ")" << endl;
		ElementWithCachedMax e;
		e.element = val;
		e.max = val;
		if (!Empty()) {
			e.max = (val > Max()) ? val : Max();
		}
		//ElementWithCachedMax e = { .max = max, .element = val };
		_elements.push(e);
	}

	T& Top() {
		if (Empty()) {
			throw length_error("Top(): empty stack.");
		}
		return _elements.top().element;
	}

	void Pop() {
		if (Empty()) {
			throw length_error("Pop(): empty stack.");
		}
		//cout << "Pop -> " << _elements.top().element << endl;
		_elements.pop();
	}

	T& Max() {
		if (Empty()) {
			throw length_error("Max(): empty stack.");
		}
		return _elements.top().max;
	}

};

/* 9.1 */
void MaxTest() {
	Stack<int> S;
	try {
		// test exception
		//cout << "Top value: " << S.Top() << endl;
		
		S.Push(5);
		cout << "Max value: " << S.Max() << endl;
		S.Push(2);
		cout << "Max value: " << S.Max() << endl;
		S.Push(16);
		cout << "Max value: " << S.Max() << endl;
		S.Push(3);
		cout << "Max value: " << S.Max() << endl;
		S.Push(6);
		cout << "Max value: " << S.Max() << endl;

		S.Pop();
		S.Pop();
		S.Pop();
		cout << "Max value: " << S.Max() << endl;
	}
	catch (const std::exception& ex){
		cout << "Exception: " << ex.what() << endl;
	}
}

#pragma endregion

#pragma region QUEUE

/* 9.8 Circular Queue */
template <typename T>
class CircularQueue {
public:
	CircularQueue(size_t max_size) {
		_maxSize = max_size;
		_data.resize(_maxSize);
		_currentSize = 0;
		_front = 0;
		_back = 0;
	}

	void Enqueue(T val) {
		_data[_back] = val;
		_back++;
		_currentSize++;

		if (_currentSize == _maxSize) {
			size_t new_size =_maxSize*2;
			_data.resize(new_size);

			if (_front == _back) {
				// copy all the elements at the front of the queue at the end of the vector
				for (int i = _maxSize - 1, j = new_size - 1; i >= _front; i--, j--) {
					_data[j] = _data[i];
					_data[i] = 0; // DEBUG
				}
				_front += _maxSize;
			}
			_maxSize = new_size;
		}		

		if (_back == _maxSize) {
			_back = 0;
		}
	}

	T Dequeue() {
		if (_currentSize <= 0) {
			throw length_error("Dequeue(): queue is empty.");
		}

		T val = _data[_front];
		_data[_front] = 0; // DEBUG
		_front++;
		if (_front == _maxSize) {
			_front = 0;
		}
		_currentSize--;
		return val;
	}

	size_t Size() {
		return _currentSize;
	}

private:
	int _front, _back;
	size_t _currentSize;
	size_t _maxSize;
	vector<T> _data;
};


/* 9.8 */
void CircularQueueTest() {
	CircularQueue<int> Q(3);
	for (int i = 1; i <= 4; i++) {
		Q.Enqueue(i);
	}
	// Q = 1 2 3 4 _ _ 
	Q.Dequeue();	// Q = _ 2 3 4 _ _
	cout << "Dequeue: " << Q.Dequeue() << endl; // Q = _ _ 3 4 _ _
	Q.Dequeue();	// Q = _ _ _ 4 _ _

	for (int i = 5; i <= 8; i++) {
		Q.Enqueue(i);
	}
	// Q = 7 8 _ 4 5 6 

	Q.Enqueue(9);
	// Q = 7 8 9 _ _ _ _ _ _ 4 5 6

	return;
}

#pragma endregion

void main() {
	/* 9.1 */
	//MaxTest();

	/* 9.8 */
	CircularQueueTest();

	return;
}