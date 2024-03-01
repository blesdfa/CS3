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

        if (balance < -1 && x > p->right->data) {
            cout << "RR Unbalance" << endl;
            leftRotate(p);
        }

        int height(node* p) {
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
};