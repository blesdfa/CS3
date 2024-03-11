#pragma once
#include <iostream>
#include <string>
using namespace std;

class trie
{
private:
	class node
	{
	public:
		bool marked;
		node* children[256];

		node()
		{
			marked = false;
			for (int i = 0; i < 256; i++)
				children[i] = nullptr;
		}
	};

    void print(node* p, string pref) {
		if (p == nullptr) //base case
		{
			//don't do anything, nothing to print
		}
		else //recursive case
		{
			if (p->marked)
				cout << pref << endl;
			for (int i = 0; i < 256; i++)
				print(p->children[i], pref + (char)i);
		}
    }

	node* root;

public:
	trie()
	{
		root = new node;
	}

	void insert(string s)
	{
		node* temp = root;

		for (int i = 0; i < s.size(); i++)
		{
			if (temp->children[s[i]] == nullptr)
				temp->children[s[i]] = new node;

			temp = temp->children[s[i]];
		}
		temp->marked = true;
	}

    void printAll() {
        print(root, "");
    }

};