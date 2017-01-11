#include <iostream>
#include <memory>

using namespace std;

template <class T>
struct ListNode {
	T data;
	shared_ptr<ListNode<T>> next;

	ListNode(void) :
		data(0), next(nullptr) {}
	ListNode(T data) :
		data(data), next(nullptr) {}
};

template <class T>
class LinkedList {
	shared_ptr<ListNode<T>> dumb_head;
	shared_ptr<ListNode<T>> tail;

public:
	LinkedList() : dumb_head(make_shared<ListNode<T>>()), tail(dumb_head){}

	void Insert(T data) {
		tail->next = make_shared<ListNode<T>>(data);
		tail = tail->next;
	}

// friend functions
	friend void mergeLists(LinkedList<T>& L1, LinkedList<T>& L2) {
		shared_ptr<ListNode<T>> it1 = L1.dumb_head, it2 L2.dumb_head;
		while (it1->next || it2->next) {

		}
		return;
	}

	friend ostream& operator<<(ostream& output, const LinkedList& list) {
		output << "{ ";
		shared_ptr<ListNode<T>> it = list.dumb_head;
		while (it!= list.tail) {
			it = it->next;
			output << it->data << (it->next ? ", " : "}");
		}
		return output;
	} 
};



int main() {
	LinkedList<int> list_odd;
	for (int i = 0; i < 10; i += 2) {
		list_odd.Insert(i);
	}
	LinkedList<int> list_even;
	for (int i = 1; i < 10; i += 2) {
		list_even.Insert(i);
	}

	cout << list_even << endl;
	cout << list_odd << endl;

	return 0;
}