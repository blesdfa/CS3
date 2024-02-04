template <class T>
class queueLL
{
private:
	//put what you need here...
	class node {
		public:

		T data;
		node* next;
		node* prev;

		node(T x) {
			next = nullptr;
			prev = nullptr;
			data = x;
		}
	};

	node* head;
	node* tail;

public:
	queueLL()
	{
		head = nullptr;
		tail = nullptr;
	}

	~queueLL()
	{

	}

	//add item to back of queue
	void enqueue(T x)
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

	//remove and return first item from queue
	T dequeue()
	{
		node* temp = head;
		T num = head->data;
		head = head->next;
		delete temp;
		return num;
	}

	//return true if empty, false otherwise.
	bool empty()
	{
		if (head == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	//For the final part of the test program, template this class
	//and add a decimate method.
	void decimate() {
		int count = 0;
		// int times = 1;
		node* tracker = head;
		while (tracker != nullptr) {
			count++;
			if (count % 10 == 0) {
				if (tracker->next == nullptr) {
					tail = tail->prev;
					tail->next = nullptr;
				}
				else {
					tracker->prev->next = tracker->next;
					tracker->next->prev = tracker->prev;
				}
			} 
			tracker = tracker->next;
		}
	}
};