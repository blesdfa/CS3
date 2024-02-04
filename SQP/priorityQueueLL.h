#include <iostream>
using namespace std;

template <class T>
class priorityQueueLL
{
private:
	class node
	{
	public:
		//put what you need here..
		T data;
		node* prev;
		node* next;

		node(T x) {
			prev = nullptr;
			next = nullptr;
			data = x;
		}
	};

	//add what you wish here
	node* tail;
	node* head;

public:

	priorityQueueLL()
	{
		head = nullptr;
		tail = nullptr;
	}

	~priorityQueueLL()
	{

	}

	//return true if empty, false if not
	bool empty()
	{
		if (head) {
			return false;
		}
		else
		{
			return true;
		}
	}

	//add item
	void insert(T x)
	{
		node* baby = new node(x);
		if (!head) {
			tail = baby;
			head = baby;
		}
		else {
			
			tail->next = baby;
			baby->prev = tail;
			tail = baby;
		}
	}

	//remove and return smallest item
	T extractMin()
	{
		node* smallest = head;
		node* tracker = head->next;
		while (tracker != nullptr) {
			if (tracker->data < smallest->data) {
				smallest = tracker;
			}
			tracker = tracker->next;
		}
		T vals = smallest->data;

		if (smallest->next == nullptr) {  // case if tail is smallest
			if (tail->prev) {
				tail = tail->prev;
				tail->next = nullptr;
			}
			else {
				head = nullptr;
				tail = nullptr;
			}
		}
		else if (smallest->prev == nullptr) { // case if head is smallest
			head = smallest->next;
			if (head != nullptr) {
				head->prev = nullptr;
			}
			else {
				tail = nullptr;
			}
		}
		else // case if in the middle
		{
			smallest->prev->next = smallest->next;
			smallest->next->prev = smallest->prev;
		}
		delete smallest;
		return vals;
	}

	void display() {
		node* tracker = head;
		while (tracker->next != nullptr) {
			cout << tracker->data << endl;
			tracker = tracker->next;
		}
	}

};