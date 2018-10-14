 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VEB.c
 * Author: VINAY CHELLWANI
 *
 * Created on February 17, 2018, 3:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define INIT -999

struct VEB {
    int min;
    int max;
    int universe;
    struct VEB** cluster;
    struct VEB* summary;
};
typedef struct VEB VEB;

//DECLARATIONS OF ALL THE FUNCTIONS
//create the skeleton of the veb
VEB* create(int universe);
//insert a value in range of the universe
void insert(VEB* root, int key);
//give the cluster number
int cluster(int key, int power);
//give the index number
int Index(int key, int power);
//swap the min value to insert it and return new key as it is a local variable 
int swap(int a, int b);

/*universe is the maximum number of integers to be stored/
 * function - to create the skeleton of the veb tree*/
VEB* create(int universe) {

    //root is the reference to the veb
    VEB* root = NULL;
    if (universe == 2) {
        //if the node is the lowest level node then it has only values 
        root = (VEB*) malloc(sizeof (VEB));
        root->max = INIT;
        root->min = INIT;
        root->universe = universe;
        //there will not be any summary and cluster of such a node
        root->summary = NULL;
        root->cluster = NULL;
    } else {
        //else it is just a description node
        root = (VEB*) malloc(sizeof (VEB));
        //it has min and max of that particular cluster
        root->max = INIT;
        root->min = INIT;
        //initialize the universe size for that node
        root->universe = universe;
        //initialize the node for summary
        root->summary = create(sqrt(universe));
        //create clusters for the nodes
        root->cluster = (VEB**) malloc(sizeof (VEB*) * sqrt(universe));
        for (int i = 0; i < sqrt(universe); i++) {
            root->cluster[i] = create(sqrt(universe));
        }
    }
    return root;
}

/*Insert function- Insert a given integer within the universe range in the VEB
 will return nothing just changes the status of the created nodes*/
void insert(VEB* root, int key) {
    int a;
    if (root->universe < key) {
        fprintf(stderr, "aukat k bahar");
        exit(1);
    }
    if (root->min == INIT) {
        root->min = root->max = key;
        return;
    } else if (key < root->min) {
        a = key;
        key = root->min;
        root->min = a;
    }
    if (root->universe > 2) {
        if (root->cluster[cluster(key, root->universe)]->min == INIT) {
            insert(root->summary, cluster(key, root->universe));
            insert(root->cluster[cluster(key, root->universe)], Index(key, root->universe));
        }

        else {
            insert(root->cluster[cluster(key, root->universe)], Index(key, root->universe));
        }
    }
    if (root->max < key)
        root->max = key;

}

/*cluster to give the cluster number to us*/
int cluster(int key, int uni) {
    return key / (sqrt(uni));
}

/*index to find the position in that cluster*/
int Index(int key, int uni) {
    return key % (int) (sqrt(uni));
}

/*minimum function to return the value of minimum in constant time*/
int minimum(VEB* root) {
    return root->min;
}

/*maximum function to return the value of maximum in constant time*/
int maximum(VEB* root) {
    return root->max;
}

int number(int i, int j, int u) {
    return (i * (int) sqrt(u) + j);
}

/*successor and predecessor functions to find the respective fields*/

int successor(VEB* v, int x) {
    int i, j;
    i = cluster(x, v->universe);
    if (v->universe == 2) {
        if (x == 0 && v->max == 1)
            return 1;
        else
            return INIT;
    } else if (x < v->min) {
        return v->min;
    }
    if (Index(x, v->universe) < v->cluster[i]->max) // successor in same cluster
    {
        j = successor(v->cluster[i], Index(x, v->universe));
    } else // find the next set cluster
    {
        i = successor(v->summary, cluster(x, v->universe));
        if (i == INIT)
            return INIT;
        else
            j = v->cluster[i]->min;

    }
    return number(i, j, v->universe);
}

/*
 * 
 */
int main(int argc, char** argv) {

    VEB* root = create(16);
    //    int power=log(root->universe)/log(2);
    int num, key;
    //    printf("%d",root->summary->universe);
    printf("veb created\n");
    printf("How many nums to insert:");
    scanf("%d", &num);
    while (num != 0) {
        printf("Enter number in range 0-%d", root->universe);
        scanf("%d", &key);
        insert(root, key);
        num--;
    }
    printf("%d\n", root->min);
    printf("%d\n", root->max);
    printf("%d\n", root->summary->min);
    printf("%d\n", root->summary->max);
    printf("%d\n", root->summary->cluster[0]->min);
    printf("%d\n", root->summary->cluster[0]->max);
    printf("%d\n", root->cluster[0]->min);
    printf("%d\n", root->cluster[0]->max);
    printf("%d\n", root->cluster[1]->min);
    printf("%d\n", root->cluster[1]->max);
    printf("%d\n", root->cluster[2]->min);
    printf("%d\n", root->cluster[2]->max);
    printf("%d\n", root->cluster[3]->min);
    printf("%d\n", root->cluster[3]->max);

    printf("\nMinimum function : %d", minimum(root));
    printf("\nMaximum function : %d", maximum(root));
    printf("%d", successor(root, 4));

    return (EXIT_SUCCESS);
}

