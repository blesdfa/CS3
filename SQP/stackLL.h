
using namespace std;
class stackLL
{
private:
	class node
	{
	public:
		//put what you need in here
        node* next;
        node* prev;
        int data;

        node(int x) {
            data = x;
            next = nullptr;
            prev = nullptr;
        }
	};

	node* top;
    node* head;

public:

	stackLL()
	{
        top = nullptr;
        head = nullptr;
    }

	//Take care of memory leaks...
	// ~stackLL()
	// {
    //     while (top) {
    //         pop();
    //     }
    // }

	//return true if empty, false if not
	bool empty()
	{
        if (top) {
            return false;
        }
        else
        {
            return true;
        }
    }

	//add item to top of stack
	void push(int x)
	{
        node* baby = new node(x);
        if (!head) {
            head = baby;
            top = baby;
        }
        else
        {
            top->next = baby;
            baby->prev = top;
            top = baby;
        }
    }

	//remove and return top item from stack
	int pop()
	{
        int num = top->data;
        node* temp = top;
        top = top->prev;
        delete temp;
        return num;
    }

	//add item x to stack, but insert it
	//right after the current ith item from the top
	//(and before the i+1 item).
    // output order: -300,30,25,20,-100,15,10,5,-200
	void insertAt(int x, int i)
	{
        // Edge case to just push if wanted at the top of the stack
        if (i == 0) {
            push(x);
            return;
        }
        node* tracker = top;
        for (int c = 0; c < i; c++) {
            // Edge case for inserting at the head of the stack;
            if (tracker->prev == nullptr) {
                node* baby = new node(x);
                tracker->prev = baby;
                baby->next = tracker;
                head = baby;
                return;
            }
            tracker = tracker->prev;
        }
        node* baby = new node(x);
        baby->next = tracker->next;
        baby->prev = tracker;
        tracker->next->prev = baby;
        tracker->next = baby;
    }

    void display() {
        node* tracker = top;
        while (tracker != nullptr) {
            cout << tracker->data << " ";
            tracker = tracker->prev;
        }
        cout << endl;
    }

};