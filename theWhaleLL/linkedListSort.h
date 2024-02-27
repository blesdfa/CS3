#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class T>
class linkedList
{
private:
    class node
    {
    public:
        T data;
        node *next;
        node *prev;

        node(T x)
        {
            next = nullptr;
            prev = nullptr;
            data = x;
        }
    };

public:
    node *head;
    node *tail;

    linkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void push_back(T x)
    {
        if (!head)
        {
            node *baby = new node(x);
            baby->next = nullptr;
            baby->prev = nullptr;
            head = baby;
            tail = baby;
        }
        else
        {
            node *baby = new node(x);
            baby->next = nullptr;
            baby->prev = tail;
            tail->next = baby;
            tail = baby;
        }
    }

    void print()
    {
        node *tracker = head;
        while (tracker)
        {
            cout << tracker->data << " ";
            tracker = tracker->next;
        }
        cout << "\n";
    }

    void split(linkedList &left, linkedList &right)
    {
        node *tracker = head;
        int count = 0;
        while (tracker)
        {
            count++;
            tracker = tracker->next;
        }

        int middle = count / 2;
        if (count % 2 != 0)
        {
            middle++;
        }

        tracker = head;
        for (int i = 0; i < middle - 1; i++)
        {
            tracker = tracker->next;
        }

        left.head = head;
        left.tail = tracker;

        right.head = tracker->next;
        right.tail = tail;
        right.head->prev = nullptr;

        left.tail->next = nullptr;
        head = nullptr;
        tail = nullptr;
    }
    void slowSort()
    {
        node *slow = head;
        while (slow)
        {
            node *fast = slow->next;
            while (fast)
            {
                if (slow->data > fast->data)
                {
                    swap(slow->data, fast->data);
                }
                fast = fast->next;
            }
            slow = slow->next;
        }
    }

    void merge(linkedList &left, linkedList &right)
    {
        node* tracker = nullptr;
        while (left.head && right.head) {
            if(!head) {
                if(left.head->data < right.head->data) {
                    head = left.head;
                    left.head = left.head->next;
                    if (left.head) left.head->prev = nullptr;
                } else {
                    head = right.head;
                    right.head = right.head->next;
                    if (right.head) right.head->prev = nullptr;
                }
                tracker = head;
            } else {
                if(left.head->data < right.head->data) {
                    tracker->next = left.head;
                    left.head->prev = tracker;
                    left.head = left.head->next;
                } else {
                    tracker->next = right.head;
                    right.head->prev = tracker;
                    right.head = right.head->next;
                }
                tracker = tracker->next;
            }
        }
        if(left.head) {
            tracker->next = left.head;
            left.head->prev = tracker;
            left.head = nullptr;
        }
        if(right.head) {
            tracker->next = right.head;
            right.head->prev = tracker;
            right.head = nullptr;
        }
    }

    void mergeSort() {
        if (head->next == nullptr) {
            return;
        }
        linkedList A;
        linkedList B;

        split(A,B);
        A.mergeSort();
        B.mergeSort();
        
        merge(A,B);
    }

    void loadFromFile(string fileName) {
        fstream file;
        string word;
        file.open(fileName);
        while(file >> word) {
            push_back(word);
        }
        file.close();
    }

    void writeToFile(string fileName) {
        ofstream myFile(fileName);
        node* tracker = head;
        int count;
        while(tracker) {
            myFile << tracker->data << " ";
            tracker = tracker->next;
        }
    }

};