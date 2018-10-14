/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BTree.c
 * Author: VINAY CHELLWANI
 *
 * Created on January 22, 2018, 10:49 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
 * Whenever we use need to store data on secondary storage we use BTree.
 * A BTREE is of order m is a m-way search tree.
 */

struct Btree {
    int m; //order of the Btree
    int* key; //array of keys
    struct Btree** child; //array of child pointers
    struct Btree* parent; //parent of the node
    int n; //no of keys currently available in the node
    int leaf; //is it a leaf node or not   
};

typedef struct Btree Btree;

/*
 * utility function to initialize the variables fields.
 * 
 */
Btree* makenode(Btree* node) {
    int i;
    node->m = 5;
    node->n = 0;
    
    node->key = (int*) malloc(((node->m) - 1) * sizeof (int));

    node->child = (Btree**) malloc(node->m * sizeof (Btree*));

    for (i = 0; i < node->m; i++) {
        node->child[i] = NULL;
    }
    node->parent = NULL;
    //node->key[0]=key;
    //    node->n=node->n+1;
    return node;
}

/*
 * Split child function to actually split the full node in to three.
 * 
 
 */
void splitchild(int i, Btree* ptr, Btree* new, int key) {
    //temp array is used for finding the median
    int temp[ptr->m + 1];
    int j;

    Btree* newnode = (Btree*) malloc(sizeof (Btree));
    newnode = makenode(newnode, 1);

    newnode->n = (int) ceil(((double) ptr->m) / 2);
    //copy the data in the temporary nodes
    for (j = 0; j < ptr->m - 1; j++) {
        temp[j] = ptr->key[j];
    }
    //initialize the counter to second half of the node
    j = (ptr->m / 2) + 1;

    //shift the nodes in temp array to insert next node
    while (j >= 0 && temp[j] > key) {
        temp[j + 1] = temp[j];
        j--;
    }
    temp[j + 1] = key;
    new->key[i] = temp[(int) (ceil(((double) ceil(ptr->m)) / 2))];
    for (j = 0; j < (ptr->m / 2) + 1; j++) {
        ptr->key[i] = temp[j + ptr->m / 2 + 1];
    }
    ptr->n = ptr->m / 2;

    if (ptr->leaf == 1) {
        for (j = 0; j < ((ptr->m / 2) + 1); j++) {
            newnode->child[j] = ptr->child[j + ((ptr->m / 2) + 1)];
            ptr->child[i + 1] = newnode;
            newnode->parent = ptr;
            ptr->n = ptr->n + 1;
        }
    }
}//split child()

void insertNotFull(int key, Btree* root) {
    //initialize an index to the rightmost element 
    int i = root->n - 1;
    // used to search the node where the key is to be placed
    Btree* ptr = root;
    //if root is the leaf node
    if (root->leaf == 1) {
        //search for the place of the key in the node and shift greater keys to right
        while (i >= 0 && root->key[i] > key) {
            root->key[i + 1] = root->key[i];
            i--;
        }

        //insert the key at it's valid place
        root->key[i + 1] = key;
        //increment the number of keys in root by 1
        root->n = root->n + 1;
    }
    else {
        //search for the node where you have to enter the key


    }
}//insertNotFull()

Btree* insert(Btree* root, int key) {
    int i; // used to initialize the child nodes in root as NULL
    Btree* ptr = NULL;
    Btree* new = NULL;
    /* If the tree doesn't exist make a new node and enter the key.
     * for the first insertion
     */
    if (root == NULL) {
        root = (Btree*) malloc(sizeof (Btree));
        if (root == NULL) {
            fprintf(stderr, "Insufficient memory");
            exit(EXIT_FAILURE);
        } 
        else {
            //initialise the node
            root = makenode(root);
            //make the first key as the data entered
            root->key[0] = key;
            //make the node as leaf node
            root->leaf=1;
            //increase the number of elements of the node by 1
            root->n = root->n + 1;
            return root;
        }
    }//null condition

    else {
        //condition for split
        ptr = root;
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
        //node full
        if (ptr->n == ptr->m - 1)
            //ie if the info field is full we need to split the node in two
        {
//            new = (Btree*) malloc(sizeof (Btree));
//            new = makenode(new, 0);
//            new->child[0] = ptr;
//            ptr->parent = new;
//            splitchild(0, ptr, new, key);
//            root = new;
        }// split condition

            //not full condition
        else {
            insertNotFull(key, ptr);
        }
    }//else part of insert
    return root;
}//insert

int getmenu() {
    int choice;
    printf("\n1.INSERT\n2.SEARCH\n3.IN-ORDER TRAVERSAL\n4.EXIT\n");
    printf("\nPlease enter your choice:");
    do {
        scanf("%d", &choice);
    } while (choice < 1 && choice > 4);
    return choice;
}

void display(Btree* x) {
    int i, j;
    Btree* p;
    for (i = 0; i <= x->n; i++)
        printf("%d ", x->key[i]);
    p = x;
    for (i = 0; i < x->m - 1; i++) {
        if (x->child[i] != NULL) {

            for (i = 0; i < x->m - 1;) {
                if (p != NULL) {
                    for (j = 0; j < p->n; j++)
                        printf("%d ", p->key);
                }
                p = x->child[++i];

            }
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    Btree* root = NULL;
    //    Btree* x;
    //    int k;
    int choice, key;
    do {
        choice = getmenu();
        switch (choice) {
            case 1:printf("Please enter the key");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:printf("boom");
                break;
            case 3:display(root);
                break;
            case 4:printf("done with the BTree operations");
                exit(EXIT_SUCCESS);
            default:fprintf(stderr, "Invalid selection");
                exit(EXIT_FAILURE);
        }
    } while (choice != 4);
    return (EXIT_SUCCESS);
}

