#include <iostream>
#include <memory>

using namespace std;

template <class T>
struct ListNode {
	T data;
	shared_ptr<ListNode<T>> next;

	ListNode(void) :
		data(), next(nullptr) {}
	ListNode(T data) :
		data(data), next(nullptr) {}
};

template <class T>
class LinkedList {

	shared_ptr<ListNode<T>> dumb_head;
	shared_ptr<ListNode<T>> tail;

public:

	LinkedList() : dumb_head(make_shared<ListNode<T>>()), tail(dumb_head){}

	bool IsEmpty() {
		return (dumb_head == tail);
	}

	void Insert(T data) {
		tail->next = make_shared<ListNode<T>>(data);
		tail = tail->next;
	}

	void InsertAfter(const shared_ptr<ListNode<T>> it, const shared_ptr<ListNode<T>> new_node) {
		if (it == tail) {
			tail = new_node;
		}
		new_node->next = it->next;
		it->next = new_node;
	}

	void Append(const shared_ptr<ListNode<T>> new_node) {
		InsertAfter(tail, new_node);
	}

	void DeleteAfter(const shared_ptr<ListNode<T>> it) {
		if (it != tail) {
			if (it->next != tail) {
				it->next = it->next->next;
			}
			else {
				it->next = nullptr;
				tail = it;
			}
		}
	}

	void Clear() {
		dumb_head->next = nullptr;
		tail = dumb_head;
	}


	/*** friend functions ***/
	
	friend ostream& operator<<(ostream& output, const LinkedList<T>& list) {
		//if (list.IsEmpty()) {
		//	output << "{}";
		//	return output;
		//} // NOT COMPILING!! don't know why
		if (list.dumb_head == list.tail) {
			output << "{}";
			return output;
		}
		
		output << "{ ";
		shared_ptr<ListNode<T>> it = list.dumb_head;
		while (it != list.tail) {
			it = it->next;
			output << it->data << (it != list.tail ? ", " : "}");
		}
		return output;
	} 

	/* 8.1 Merge sorted lists (ascending) */ 
	static friend LinkedList<T> mergeLists(LinkedList<T>& L1, LinkedList<T>& L2) {
		LinkedList<T> L3;

		if (!L1.IsEmpty() && !L2.IsEmpty()) {
			shared_ptr<ListNode<T>> it1 = L1.dumb_head->next;
			shared_ptr<ListNode<T>>	it2 = L2.dumb_head->next;

			while (it1 != L1.tail || it2 != L2.tail) {
				if (it1->data <= it2->data) {
					L1.dumb_head->next = it1->next;
					L3.Append(it1);
					if (it1 != L1.tail) {
						it1 = L1.dumb_head->next;
					}
				}
				else {
					L2.dumb_head->next = it2->next;
					L3.Append(it2);
					if (it2 != L2.tail) {
						it2 = L2.dumb_head->next;
					}
				}
 			}
			if (it1->data <= it2->data) {
				L3.Append(it1);
				L3.Append(it2);
			}
			else {
				L3.Append(it2);
				L3.Append(it1);
			}
		}
		else if (L1.IsEmpty()) {
			L3 = L2;
		}
		else if (L2.IsEmpty()) {
			L3 = L1;
		}

		L1.Clear();
		L2.Clear();

		return L3;
	}
};



int main() {
	/* 8.1 */
	LinkedList<int> list_odd;
	for (int i = 1; i < 10; i += 2) {
		list_odd.Insert(i);
	}
	LinkedList<int> list_even;
	for (int i = 0; i < 10; i += 2) {
		list_even.Insert(i);
	}
	
	list_even.Append(make_shared<ListNode<int>>(12));
	list_odd.Append(make_shared<ListNode<int>>(11));
	list_odd.Append(make_shared<ListNode<int>>(13));

	cout << "list_even = " << list_even << endl;
	cout << "list_odd = " << list_odd << endl;

	LinkedList<int> list_merged = mergeLists(list_odd, list_even);

	cout << "list_even = " << list_even << endl;
	cout << "list_odd = " << list_odd << endl;
	cout << "list_merged = " << list_merged << endl;

	return 0;
}