#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <vector>
#include <string>
using namespace std;

class Autocompleter
{
	// For the mandatory running times below:
	// n is the number of strings in the dictionary.
	// Assume that the length of every string is O(1).

public:
	// Creates a new Autocompleter with an empty dictionary.
	//
	// Must run in O(1) time.
	Autocompleter() {
		root = nullptr;
	}

	// Adds a string x to the dictionary.
	// If x is already in the dictionary, does nothing.
	//
	// Must run in O(log(n)) time.
	void insert(string x, int freq) {
		
        Entry e1;
        e1.freq = freq;
        e1.s = x;
        insert_recurse(e1, root);
    }

	// Returns the number of strings in the dictionary
	// of possible completions.
	//
	// Must run in O(n) time.
	int size() {
		return size_recurse(root);
	}

	// Fills the vector T with the three most-frequent completions of x.
	// If x has less than three completions, then
	// T is filled with all completions of x.
	// The completions appear in T from most to least frequent.
	//
	// Must run fast.  In particular, you should not search all nodes in the
	// tree for possible completions.
	// Instead, only search regions of the tree for which a completion could
	// be present, which will yield a run time bound of O(k log n ) time,
	// where k is the number of completions in the tree.
	void completions(string x, vector<string> &T) {
		completions_recurse(x, root, T);
		cout << T[0] << " " << T[1] << " " << T[2] << endl;
		// for (auto x : T) {
		// 	cout << x << endl;
		// }
	}

	//Reports height of the AVL tree, runs in O(1) time.
	int height()
	{
		return height(root);
	}

private:
	// A helper class that stores a string and a frequency.
	class Entry
	{
	public:
		string s;
		int freq;
	};

	// A helper class that implements a binary search tree node.
	class Node
	{
	public:
		Node()
		{
			height = 0;
			left = right = nullptr;
		}

		Node(Entry e)
		{
			this->e = e;
			height = 0;
			left = right = nullptr;
		}

		Entry e;
		int height;
		Node* left;
		Node* right;
	};

	// A convenience method for getting the height of a subtree.
	// Returns the height of the subtree rooted at p.
	// Useful for rebalance().
	static int height(Node* p)
	{
		if (p == nullptr)
			return -1;
		return p->height;
	}

	// Root of the binary-search-tree-based data structure
	Node* root;


	// Optional helper methods (you'll probably want them)

	// Returns the size of the binary tree rooted at p.
	//
	// Should run in O(n) time.
	int size_recurse(Node* p) {
		if (!p) {
			return 0;
		} else {
			return 1 + size_recurse(p->left) + size_recurse(p->right);
			
		}
	}

	// Fills C with the completions of x in the BST rooted at p.
	void completions_recurse(string x, Node* p, vector<string> &C) { //CHANGED ENTRY TO STRING
		int top = 0;
		int second = 0;
		int third = 0;
		C[0] = "";
		C[1] = "";
		C[2] = "";

		if (!p) {
			return;
		}
		else if (x < p->e.s) {
			if (p->e.s[0] == x[0]) {
				C.push_back(p->e.s);
				if (p->e.freq > top) {
					third = second;
					second = top;
					top = p->e.freq;
					C[2] = C[1];
					C[1] = C[0];
					C[0] = p->e.s;
				}
				else if (p->e.freq > second) {
					third = second;
					second = p->e.freq;
					C[2] = C[1];
					C[1] = p->e.s;
				}
			}
			completions_recurse(x, p->left, C);
		}
		else {
			if (p->e.s[0] == x[0]) {
				C.push_back(p->e.s);
			}
			completions_recurse(x, p->left, C);
		}
	}

	// Inserts an Entry into an AVL tree rooted at p.
	//
	// Should run in O(log(n)) time.
	void insert_recurse(Entry e, Node* &p) {
        if (!p) {
            p = new Node(e);
        }
        else {
            if (e.s < p->e.s) {
                insert_recurse(e, p->left);
            }
            else {
                insert_recurse(e, p->right);
            }
        }
        update_height(p);

        int bf = height(p->left) - height(p->right); // balance factor variable to not have to retype the whole calculation in the if statements 

        if (bf >= 2 && e.s < p->left->e.s) {
            // rebalance(p, "l");
            right_rotate(p);
        }
        else if (bf >= 2 && e.s > p->left->e.s) {
            // rebalance(p, "lr");
			left_rotate(p->left);
			right_rotate(p);
        }
        else if (bf <= -2 && e.s > p->right->e.s) {
            // rebalance(p, "r");
			left_rotate(p);
        }
        else if (bf <= -2 && e.s < p->right->e.s) {
            // rebalance(p, "rl");
			right_rotate(p->right);
			left_rotate(p);
        }

    }

	// Rebalances the AVL tree rooted at p.
	// Helpful for insert().
	// Should be called on every node visited during
	// the search in reverse search order.
	//
	// Should run in O(1) time.
	void rebalance(Node* &p, string type) {
		
    }

	// Perform left and right rotations
	// of an AVL tree rooted at p (helpful for implementing rebalance).
	//
	// Should run in O(1) time.
	void right_rotate(Node* &p) {
		Node* l = p->left;
		Node* lRight = l->right;
		l->right = p;
		p->left = lRight;
		update_height(p);
		update_height(l);
		p = l;
    }

	void left_rotate(Node* &p) {
        Node* r = p->right;
        Node* rLeft = r->left;
        r->left = p;
        p->right = rLeft;
		update_height(p);
		update_height(r);
		p = r;
    }


	//A useful method to update
	//the height of a node,
	//assuming subtrees already have
	//the correct height.
	void update_height(Node*& p)
	{
		if (p != nullptr)
			p->height = 1 + max(height(p->left), height(p->right));
	}
};

#endif