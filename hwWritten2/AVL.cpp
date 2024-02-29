#include <iostream>
#include <vector>
using namespace std;

class AVL {
private:
    class node {
        public:
            node* left;
            node* right;
            int height;
            double data;

            node(double x) {
                data = x;
                height = 0;
                left = nullptr;
                right = nullptr;
            }
    };
    node* root;

    void leftRotate(node* &p) {
        // node* l = p->left;
        // node* r = p->right;

        // p->left = r;
        // l->right = p;
        // p = l;
        // p->right->height = height(p->right);
        // p->height = height(p);



        node* r = p->right;
        node* rLeft = r->left;

    // Perform rotation
        r->left = p;
        p->right = rLeft;

    // Update heights
        p->height = height(p);
        r->height = height(r);

    // Update root
        p = r;
    }

    void rightRotate(node* &p) {
        node* l = p->left;
        node* r = p->right;

        p->right = l;
        r->left = p;
        p = r;
        p->height = height(p);
        p->left->height = height(p->left);
    }

    void insert(double x, node* &p) {
        if (!p) {
            p = new node(x);
        }
        else {
            if (x < p->data) {
                insert(x, p->left);
            }
            else {
                insert(x, p->right);
            }
        }

        p->height = height(p);

        int balance = height(p->left) - height(p->right);

        // Left-Left Unbalance
        if (balance > 1 && x < p->left->data) {
            cout << "LL Unbalance" << endl;
            leftRotate(p);
        }

        // Left-Right Unbalance
        if (balance > 1 && x > p->left->data) {
            cout << "left right unbalance" << endl;
            rightRotate(p->left);
            leftRotate(p);
        }

        //RR Unbalance
        if (balance < -1 && x > p->right->data) {
            cout << "RR Unbalance" << endl;
            leftRotate(p);
        }

        //RL Unbalance
        if (balance < -1 && x < p->right->data) {
            cout << "RL Unbalance" << endl;
            leftRotate(p->right);
            rightRotate(p);
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

    void display(node* p) {
        if (!p) 
        {

        }
        else {
            cout << p->data << "|Height : " << p->height << endl;
            display(p->left);
            display(p->right);
        }
    }

    int isBalanced(node* root)
    {
        if (root == NULL)
            return 0;
        int lh = isBalanced(root->left);
        if (lh == -1)
            return -1;
        int rh = isBalanced(root->right);
        if (rh == -1)
            return -1;
    
        if (abs(lh - rh) > 1)
            return -1;
        else
            return max(lh, rh) + 1;
    }

public:

    AVL() {
        root = nullptr;
    }

    void display() {
        display(root);
    }

    void insert(double x) {
        insert(x, root);
    }

    int isBalanced() {
        return isBalanced(root);
    }

    node* buildTree(vector<double> &A, int start, int end) {
        
    }
    void height() {
        cout << height(root) << endl;
    }
};

int main() {
    AVL bst;

    for(double i = 1; i <= 100000; i++) {
        bst.insert(i);
    }

    if (bst.isBalanced() > 0)
        cout << "Balanced";
    else
        cout << "Not Balanced";
    
    bst.height();
    return 0;

}