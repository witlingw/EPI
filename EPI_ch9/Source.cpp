#include <iostream>
#include <stack>

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


#pragma endregion

void main() {
	/* 9.1 */
	MaxTest();

	return;
}