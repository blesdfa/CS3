#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int fastFind(vector<double> &A, double key) {
    int s = 0;
    int e = 1;

    while (A[e] < key && e < A.size()) {
        s = e;
        e *= 2;
    }

    e = min(e, int(A.size() - 1));

    while (s <= e) {
        int mid = (s + e) / 2;

        if (A[mid] == key) {
            return mid;
        }
        else if (key < A[mid]) {
            e = mid - 1;
        }
        else {
            s = mid + 1;
        }
    }
    return -1;
}

class BST {
private:
    class node {
    public:
        node* left;
        node* right;
        double data;
        int height;
        int bf;

        node(double x) {
            data = x;
            left = nullptr;
            right = nullptr;
            height = 0;
            bf = 0;
        }
    };

    node* root;

    node* buildTree(vector<double> &A, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        node* baby = new node(A[mid]);
        baby->left = buildTree(A, start, mid - 1);
        baby->right = buildTree(A, mid + 1, end);

        // baby->height = height(baby);
        // baby->bf = abs(height(baby->left) - height(baby->right)); testing for balance 
        return baby;
    }

    void display(node* p) {
        if (!p) {
    
        }
        else {
            display(p->left);
            cout << p->data << " ";
            display(p->right);
        }
    }

    int height(node* &p) {
        if (!p) {
            return -1;
        }
        else {
            return 1 + max(height(p->left), height(p->right));
        }
    }

    void levelOrderTraversal(node* r) {
        if (!r) {
            return;
        }

        queue<node*> q;

        q.push(root);

        while(q.empty() == false) {
            node* baby = q.front();
            cout << baby->data << " ";
            q.pop();

            if (baby->left != nullptr) {
                q.push(baby->left);
            }

            if (baby->right != nullptr) {
                q.push(baby->right);
            }
        }
    }

public:
    BST() {
        root = nullptr;
    }

    void buildTree(vector<double> &A) {
        root = buildTree(A, 0, A.size()- 1);
    }

    void display() {
        display(root);
    }

    void levelOrderTraversal() {
        levelOrderTraversal(root);
    }
};


int main() {
    vector<double> nums;
    nums.push_back(3);
    nums.push_back(4);
    nums.push_back(7);
    nums.push_back(10);
    nums.push_back(15);
    nums.push_back(22);
    nums.push_back(40);

    cout << "Fast finding index of 7 || Index: " << fastFind(nums, 7) << endl;

    BST tree;
    tree.buildTree(nums);
    cout << "In order traversal: ";
    tree.display();
    cout << "\n";
    cout << "Level Order Traversal: ";
    tree.levelOrderTraversal();
}