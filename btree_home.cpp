/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   btree_home.cpp
 * Author: VINAY CHELLWANI
 *
 * Created on April 5, 2018, 7:31 PM
 */
#include <iostream>
#include <cstdlib>
#define NO_NUM 999
using namespace std;

/*Structure declaration of BTREE*/
struct Btree {
    int m; //order of tree
    int* key; //array of keys
    int n; //number of keys in each node
    struct Btree* parent; //pointer to parent
    struct Btree** child; //array of pointers to child nodes
    bool leaf; //is a leaf node true 
};
typedef struct Btree Btree;

/*Initialize the newly created node*/
Btree* makenode(bool leaf) {
    Btree* node = new Btree;
    node->m =5; //degree
    node->key = new int[node->m - 1]; //m-1 integer keys
    node->child = new Btree*[node->m]; //m childs
    for (int i = 0; i < node->m; i++){
        node->child[i] = NULL;
        node->key[i]=NO_NUM;
    }
    node->parent = NULL; //parent 
    node->leaf = leaf; //is leaf 
    node->n = 0; //no of elements

}



/*to fill the key in already existing node*/
void insertNotFull(Btree* root, int key) {
    int i = root->n - 1; //Point to secon last element for inertion sort
    //insertion sort to find place for new key
    while (i >= 0 && root->key[i] > key) {
        root->key[i + 1] = root->key[i];
        root->child[i + 2] = root->child[i + 1];
        i--;
    }

    //insert the key at it's valid place
    root->key[i + 1] = key;
    //make the link null for next value
    root->child[i + 2] = NULL;
    //increment the number of keys in root by 1
    root->n = root->n + 1;
}

/*if the pointed node is full either make new node or check for upper node*/
Btree* splitchild(Btree* ptr, int key,Btree* root) {
    int j, i;
    Btree* lower = makenode(true);
    int* temp = new int[ptr->m];
    if (ptr->parent != NULL) {

        if (ptr->parent->n < ptr->m) {//if ptr->parent is a node and not full
            int i = 0;
            //copying in temp
            for (i = 0; i < ptr->n; i++) {
                temp[i] = ptr->key[i];
            }
            //finding place for new key in temp
            i = ptr->n - 1;
            while (i >= 0 && temp[i] > key) {
                temp[i + 1] = temp[i];
                i--;
            }
            //key inserted
            temp[i+1] = key;
            //finding the median
            int median = (ptr->m / 2);
            int median_key = temp[median];
            //uplifting the median in the root
            insertNotFull(ptr->parent, median_key);
            ptr->key[median]=NO_NUM;
            Btree* lower = makenode(true);
            for (j = median+1, i = 0; j < ptr->m - 1; j++, i++) {
                lower->key[i] = ptr->key[j];
                lower->n++;
                ptr->n--;
                ptr->key[j] = NO_NUM;
                lower->child[i] = ptr->child[j];
            }
            Btree* traverse = ptr->parent->child[0];
            i = 1;
            while (traverse != NULL) {
                traverse = ptr->parent->child[i];
                ++i;
            }
            ptr->parent->child[i - 1] = lower;
            
           
        }//parent not full
        else {
            int i = 0;
            //copying in temp
            for (i = 0; i < ptr->n; i++) {
                temp[i] = ptr->key[i];
            }
            //finding place for new key in temp
            i = ptr->n - 1;
            while (i >= 0 && temp[i] > key) {
                temp[i + 1] = temp[i];
                i--;
            }
            //key inserted
            temp[i+1] = key;
            //finding the median
            int median = (ptr->m / 2);
            int median_key = temp[median];
            //uplifting the median in the root
            splitchild(ptr->parent, median_key,root);
        }
         return root;
    }//ptr->parent!=NULL;
    else {   
        Btree* upper = makenode(false);
        int i = 0;
        //copying in temp
        for (i = 0; i < ptr->n; i++) {
            temp[i] = ptr->key[i];
        }
        //finding place for new key in temp
        i = ptr->n -1;
        while (i >= 0 && temp[i] > key) {
            temp[i + 1] = temp[i];
            i--;
        }
        //key inserted
        temp[i+1] = key;
        //finding the median
        int median = (ptr->m / 2);
        int median_key = temp[median];
        upper->key[0] = median_key;
        upper->n=upper->n+1;
        for (j = median, i = 0; j < ptr->m - 1; j++, i++) {
            lower->key[i] = ptr->key[j];
            lower->n++;
            ptr->n--;
            ptr->key[j] = NO_NUM;
            lower->child[i] = ptr->child[j];
        }
        upper->child[0] = ptr;
        upper->child[1] = lower;
        lower->parent = ptr->parent = upper;
        return upper;
    }
}

Btree * insert(Btree* root, int key) {
    if (root == NULL) {//tree is empty
        root = makenode(true);
        root->key[0] = key;
        root->n = root->n + 1;
    } else {
        int i;
        Btree* ptr = root;
        //search for the node of key
        while (1) // find the node where key is to be inserted
        {

            for (i = 0; i < ptr->n; i++) {
                if (key <= ptr->key[i])
                    break;
            }
            //if the node isn't the leaf node move to the child
            if (ptr->leaf == 0)
                ptr = ptr->child[i];
                //if it is a leaf node then break and exit
            else
                break;
        }

        if (ptr->n == (ptr->m - 1)) {
            root = splitchild(ptr, key,root);
        } else {
            insertNotFull(ptr, key);
        }
    }
    return root;
}

void inordertraverse( Btree *head) {
    int i;
    cout << "KEYS: " << endl;
    for (i = 0; i < (head->n); i++) {
        if (head->leaf == 0)
            inordertraverse(head->child[i]);
        cout << head->key[i] << endl;
    }
    if (head->leaf == 0)
        inordertraverse(head->child[i]);
}


/*
 * 
 */
int main(int argc, char** argv) {
    Btree* root = NULL;
    root = insert(root, 20);
    Btree* ptr=root;
    for (int i = 0; i < 4; i++)
        cout << ptr->key[i] << " " ;
    cout<<endl;
    root = insert(root, 1);
     ptr=root;
    for (int i = 0; i < 4; i++)
        cout << ptr->key[i] << " ";
    cout<<endl;
    root = insert(root, 15);
     ptr=root;
    for (int i = 0; i < 4; i++)
        cout << ptr->key[i] << " ";
    cout<<endl;
    root = insert(root, 5);
     ptr=root;
    for (int i = 0; i < 4; i++)
        cout << ptr->key[i] << " ";
    cout<<endl;
    root = insert(root, 7);
    for (int i = 0; i < 4; i++)
        cout << root->key[i] << " ";
    cout<<endl;
     ptr=root->child[0];
    for (int i = 0; i < 4; i++)
        cout << ptr->key[i] << " ";
     cout<<endl;
     ptr=root->child[1];
    for (int i = 0; i < 4; i++)
        cout << ptr->key[i] << " ";
     cout<<endl;
     cout<<"roots num"<<root->n;
     root=insert(root,12);
     root=insert(root,18);
     root=insert(root,35);
     root=insert(root,2);
     root=insert(root,27);
     root=insert(root,54);
     root=insert(root,28);
     root=insert(root,14);
     root=insert(root,19);
//     root=insert(root,9);
     cout<<"after 12"<<endl;
     for (int i = 0; i < 4; i++)
        cout << root->key[i] << " ";
    cout<<endl;
     ptr=root->child[0];
    for (int i = 0; i < 4; i++)
        cout << ptr->key[i] << " ";
     cout<<endl;
     ptr=root->child[1];
    for (int i = 0; i < 4; i++)
        cout << ptr->key[i] << " ";
     cout<<endl;
//    ptr=root->child[2];
//    for (int i = 0; i < 4; i++)
//        cout << ptr->key[i] << " ";
     cout<<endl;
//    for(int j=0;j<1000;j++){
//        root=insert(root,j);
//    }
    inordertraverse(root);
    return 0;
}

