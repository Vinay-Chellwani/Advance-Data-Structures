/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   binomial_heap.cpp
 * Author: VINAY CHELLWANI
 * Created on February 28, 2018, 11:13 AM
 */
#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <climits>
using namespace std;

struct Binomial {
    struct Binomial* parent; //parent of the structure
    int key; //number to be stored
    int degree; //degree of the binomial tree
    struct Binomial* leftChild; //leftmost child of the node
    struct Binomial* sibling; //adjacent node in the heap on the same level
};

typedef struct Binomial Binomial;

//unites/melds two heaps
Binomial* unionFunc(Binomial* h1, Binomial* h2);

//merges two heaps in accordance to their order
Binomial* merge(Binomial* h1, Binomial* h2);

//link the nodes
Binomial* link(Binomial* first, Binomial* second);

//utility function to allocate memory and establish the state of the node
Binomial* makenode(int key);

//insert a key in the heap calls the union method to join the heap
Binomial* insert(Binomial* h1, int key);

//Menu for available functions
int menu();

//extract min function
Binomial* extractmin(Binomial* mainlist, bool flag);

Binomial* reverse(Binomial* kid);

Binomial* searchKey(Binomial* root, int key);

Binomial* decreaseKey(Binomial* h1, int key, int newKey);

Binomial* deleteKey(Binomial* h1, int keyToDel);

int findmin(Binomial* root);
/*
 * 
 */
int main(int argc, char** argv) {
    int ch, key, newKey;
    Binomial* Root = NULL;
    Binomial* ptr = NULL;
    do {
        ch = menu();
        switch (ch) {
            case 1:cout << "\nENTER KEY TO BE ENTERED" << endl;
                cin>>key;
                Root = insert(Root, key);
                break;
            case 2:cout << "Calling extract min" << endl;
                Root = extractmin(Root, true);
                break;
            case 3:key = findmin(Root);
                cout << "Minimum key is " << key << endl;
                break;
            case 4:
                cout << "Enter the key to be decreased" << endl;
                cin>>key;
                cout << "Enter the new decreased value" << endl;
                cin>>newKey;
                Root = decreaseKey(Root, key, newKey);
                break;
            case 5:cout << "Enter the key to delete" << endl;
                cin>>key;
                Root = deleteKey(Root, key);
                break;
            case 6:exit(0);
        }
    } while (ch != 6);


    return 0;
}

Binomial* unionFunc(Binomial* h1, Binomial* h2) {
    //merge two heaps in order of the degree of the trees
    Binomial* h = merge(h1, h2);
    //if both heaps are empty merge returns null
    if (h == NULL)
        return NULL;
    //else traverse the list and keep combining the trees with same degree
    Binomial* x = h;
    Binomial* prevX = NULL;
    Binomial* nextX = x->sibling;

    //traverse logic
    while (nextX != NULL) {
        //if degree is not same or next ke next ka degree is same as that of x
        if (x->degree != nextX->degree || \
                (nextX->sibling != NULL && nextX->sibling->degree == x->degree)) {
            prevX = x;
            x = nextX;
            //nextX = nextX->sibling;
            // continue;
        } 
        else if (x->key <= nextX->key) {
            x->sibling = nextX->sibling;
            x = link(nextX, x);
        } 
        else {
            if (prevX == NULL)
                h = nextX;
            else {
                prevX->sibling = nextX;
            }
            //first arg added as leftmost child of sec argument
            nextX = link(x, nextX);
            x = nextX;
        }
        nextX = nextX->sibling;
    }

    return h;

}

Binomial* merge(Binomial* h1, Binomial* h2) {
    //first heap assigned to p
    Binomial* p = h1;
    //second heap assigned to q
    Binomial* q = h2;
    //a new head node for combined heap
    Binomial* head = NULL;
    //trailing ptr to head
    Binomial* r = head;
    if (h1 == NULL && h2 != NULL)
        return h2;
    else if (h1 != NULL && h2 == NULL)
        return h1;
    else {

        if (q->degree < p->degree) {
            head = q;
            r = head;
            q = q->sibling;
        } else {
            head = p;
            r = head;
            p = p->sibling;
        }

        while (p != NULL && q != NULL) {
            if (p->degree < q->degree) {
                r->sibling = p;
                r = r->sibling;
                p = p->sibling;
            } else {
                r->sibling = q;
                r = r->sibling;
                q = q->sibling;
            }
        }
        while (p != NULL) {
            r->sibling = p;
            r = r->sibling;
            p = p->sibling;
        }
        while (q != NULL) {
            r->sibling = q;
            r = q;
            q = q->sibling;
        }
        return head;
    }
}
//first arg added as leftmost child of sec argument

Binomial* link(Binomial* first, Binomial* second) {

    first->parent = second;
    first->sibling = second->leftChild;
    second->leftChild = first;
    second->degree = second->degree + 1;
    return second;
}

Binomial* makenode(int key) {
    Binomial* node = new Binomial;
    if (node == NULL) {
        cerr << "Insufficient memory";
        exit(1);
    } else {
        node->degree = 0;
        node->key = key;
        node->leftChild = node->parent = node->sibling = NULL;
        return node;
    }
}

Binomial* insert(Binomial* h1, int key) {
    if (h1 == NULL) {
        h1 = makenode(key);
        h1 = unionFunc(h1, NULL);
        cout << "Insert successful" << endl;
    } else {
        Binomial* h2 = makenode(key);
        h1 = unionFunc(h1, h2);
        cout << "Insert successful" << endl;
    }
    return h1;
}

int menu() {
    int choice;
    do {
        cout << "\n1.Insert element\n2.Extract Minimum\n3.Find minimum\n4.Decrease Key\n5.Delete Key\n6.exit\n";
        cout << "Please enter your choice:";
        cin>>choice;
    } while (choice < 0 || choice > 7);
    return choice;
}

Binomial* extractmin(Binomial* root, bool flag) {
    int minimum = INT_MAX;
    if (root == NULL) {
        cout << "Heap is useless just like you" << endl;
        return NULL;
    }
    Binomial* mainlist = root;
    Binomial* ptr = NULL;
    Binomial* prev = NULL;
    while (mainlist != NULL) {
        if (mainlist->key < minimum) {
            minimum = mainlist->key;
            prev = ptr;
            ptr = mainlist;
        }
        mainlist = mainlist->sibling;
    }
    if (prev != NULL && prev->sibling != NULL)
        prev->sibling = ptr->sibling;

    if (prev == NULL) {
        if (ptr->sibling == NULL)
            root = prev;
        else
            root = ptr->sibling;
    }

    Binomial* kid = ptr->leftChild;
    if (flag)
        cout << "Minimum key:" << ptr->key << endl;
    else
        cout << "Deleted Key" << endl;
    ptr->leftChild = NULL;
    ptr->sibling = NULL;
    delete (ptr);
    ptr = kid;
    while (ptr != NULL) {
        ptr->parent = NULL;
        ptr = ptr->sibling;
    }
    if (kid != NULL) {
        kid = reverse(kid);
        (root) = unionFunc(root, kid);
    }
    return root;


}

Binomial* reverse(Binomial* kid) {
    Binomial* looker = kid;
    Binomial* ptr = kid;
    Binomial* prev = NULL;

    while (ptr != NULL) {
        looker = looker->sibling;
        ptr->sibling = prev;
        prev = ptr;
        ptr = looker;
    }

    return prev;


}

Binomial* searchKey(Binomial* root, int key) {

     Binomial* ptr = NULL;
    while (root != NULL) {

        if (root->leftChild != NULL) {
            ptr = searchKey(root->leftChild, key);
        }
        if (root->key == key) {
            ptr = root;
            break;

        }
        root = root->sibling;
    }
    return ptr;
}

Binomial* decreaseKey(Binomial* h1, int key, int newKey) {
    if (newKey > key) {
        cerr << "Nice joke" << endl;
        return h1;
    }
    Binomial* node = searchKey(h1, key);
    if (node == NULL) {
        cerr << "Invisible key... Go get a life" << endl;
        return h1;
    } else {
        node->key = newKey;

        Binomial* parnode = node->parent;

        while (parnode != NULL && parnode->key > node->key) {
            if (parnode->key > node->key) {
                int ind = node->key;
                node->key = parnode->key;
                parnode->key = ind;
                node = parnode;
                parnode = parnode->parent;
            }
        }

    }
    return h1;
}

Binomial* deleteKey(Binomial* h1, int keyToDel) {
    h1 = decreaseKey(h1, keyToDel, INT_MIN);
    h1 = extractmin(h1, false);
    return h1;
}

int findmin(Binomial* root) {
    int minimum = INT_MAX;
    if(root==NULL){
        cerr<<"Heap is useless just like you";
        exit(1);
    }
    while (root != NULL) {
        if (root->key < minimum)
            minimum = root->key;
        else
            root = root->sibling;
    }
    return minimum;
}