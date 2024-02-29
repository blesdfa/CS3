#include <iostream>
#include <vector>
using namespace std;

int fastFind(vector<double> &A, double key) {
    int s = 0;
    int e = A.size() - 1;

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

                node(double x) {
                    left = nullptr;
                    right = nullptr;
                    data = x;
                    height = 0;
                }
        };

        node* root;
    public:
        BST() {
            root = nullptr;
        }

        void insert(node* &p, double x) {
            if (!p) {
                p = new node(x);
            }
            else {
                if (x < p->data) {
                    insert(p->left, x);
                }
                else {
                    insert(p->right, x);
                }
            }
        }

        node* buildTree(vector<double> &A, int start, int end) {
            if (!root) {
                insert(root, A[(start + end) / 2]);
            }

            if (start > end) {
                return nullptr;
            }

            int mid = (start + end) / 2;
            root->left = buildTree(A, start, mid - 1);
            root->right = buildTree(A, mid + 1, end);

            return root;
        }    
};

int main() {
    vector<double> nums;
    for (double i = 0; i < 40; i++) {
        nums.push_back(i);
    }

    cout << fastFind(nums, 4) << endl;

    BST tree;
    node* test = tree.buildTree(A, 0, A.size() - 1);
}
