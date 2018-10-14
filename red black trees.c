/*
 * To change this license rooter, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   red black trees.c
 * Author: VINAY CHELLWANI
 *
 * Created on January 10, 2018, 9:48 AM
 */
//task pending

// 1. black height
// 2. delete operation
//   2.1 colour wise cases
//   2.2 check for different sub cases in the above
// 3. complete the documentation of rotate functions
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* RBT is used when there are frequent additions and deletions which is not the 
 * case in an AVL tree. 
 * Actually O(1.44log2 n) is the search efficiency of the AVL tree 
 * whereas O(2log2 n) is eff of RBT. For frequent searches AVL is used. 
 * AVL allows an imbalance factor of 1 and RBT allows an imbalance factor of 2.
 * In RBT by mere colour changes imbalance can be dealt with.
 */


//structure declaration of rbt

struct rbt {
    int data;//to store the information
    struct rbt* left;//left subtree which contains values less than node
    struct rbt* right;//right subtree which contains values more than node
    struct rbt* parent;//link to the upper subtree
    char colour;//characteristic
};

typedef struct rbt RBT;
void inorderR(RBT* r);
/******************************************
//INSERTION OF A NODE IN THE RED BLACK TREE
//*****************************************/


// func to add a node in the tree called by insert()

RBT* add(RBT* root, int x) {
    RBT* ptr = root;
    RBT* newnode = (RBT*) malloc(sizeof (RBT));
    newnode->data = x;
    newnode->colour = 'r';
    newnode->left = newnode->right = NULL;

    while (root != NULL) {
        if (root->data > x) {
            ptr = root;
            root = root->left;
            continue;
        }
        if (root->data < x) {
            ptr = root;
            root = root->right;
            continue;
        }

    }
    if (newnode->data < ptr->data)
        ptr->left = newnode;
    else
        ptr->right = newnode;
    newnode->parent = ptr;
    return newnode;


}

//******************************************

// rotate functions for XXb imbalances

RBT* rotateRight(RBT* T, RBT* root) {
    /* Here we pass the address of the parent of the new node and rotate the tree
     * around it -- meaning parent becomes root, newnode becomes left child and 
     * grandparent becomes right child. 
     */

    // Keep a track of the parent's grandparent
    RBT* temp = T->parent->parent;

    // Right of parent becomes left of grandparent
    T->parent->left = T->right;

    //If parents right is a valid node change its parent field
    if (T->right != NULL)
        T->right->parent = T->parent;

    //Make grandparent as the right child of parent(ROTATION)
    T->right = T->parent;

    //Change grandparents parent field 
    T->parent->parent = T;


    //Change T's parent field to upper subtree
    T->parent = temp;

    // if parent of grandparent of new node is the root of the tree change the root
    if (temp == NULL) {
        root = T;

    } else {
        if (temp->left == T->right)
            temp->left = T;
        if (temp->right == T->left)
            temp->right = T;
    }
    //Change the colour of grandparent to red
    T->right->colour = 'r';

    //Parent becomes black
    T->colour = 'b';

    return root;
}


//widout colour change for RL imbalance

RBT* rotateRightNoColor(RBT* T, RBT* root) {
    /* Here we pass the address of the parent of the new node and rotate the tree
     * around it -- meaning parent becomes root, newnode becomes left child and 
     * grandparent becomes right child. Widout colour change this is used in  RL
     * function.
     */

    // Keep a track of the parent's grandparent
    RBT* temp = T->parent->parent;

    // Right of parent becomes left of grandparent
    T->parent->left = T->right;

    //If parents right is a valid node change its parent field
    if (T->right != NULL)
        T->right->parent = T->parent;

    //Make grandparent as the right child of parent(ROTATION)
    T->right = T->parent;

    //Change grandparents parent field 
    T->parent->parent = T;

    //Change T's parent field to upper subtree
    T->parent = temp;
    if (temp == NULL)
        root = T;
    else {
        if (temp->left == T->right)
            temp->left = T;
        if (temp->right == T->left)
            temp->right = T;
    }

    return root;
}

// left rotate functions

RBT* rotateLeft(RBT* T, RBT* root) {
    /* Here we pass the address of the parent of the new node and rotate the tree
     * around it -- meaning parent becomes root, newnode becomes right child and 
     * grandparent becomes left child. 
     */
    // Keep a track of the parent's grandparent
    RBT* temp = T->parent->parent;

    //Left of parent becomes right of grandparent
    T->parent->right = T->left;

    // if t's left is a valid node update it's parent field
    if (T->left != NULL)
        T->left->parent = T->parent;

    //Make grandparent as the left child of T(Rotate left)
    T->left = T->parent;

    //Change grandparents parent 
    T->parent->parent = T;

    //Change parents parent to upper subtree
    T->parent = temp;
    if (temp == NULL)
        root = T;
    else {
        if (temp->left == T->right)
            temp->left = T;
        if (temp->right == T->left)
            temp->right = T;
    }
    //Change colour of grandparent to red and T to black
    T->left->colour = 'r';
    T->colour = 'b';
    return root;
}

// widout colour change to use in LR imbalance

RBT* rotateLeftNoColor(RBT* T, RBT* root) {
    /* Here we pass the address of the parent of the new node and rotate the tree
     * around it -- meaning parent becomes root, newnode becomes right child and 
     * grandparent becomes left child. Widout colour change this is used in  LR
     * function.
     */
    // Keep a track of the parent's grandparent
    RBT* temp = T->parent->parent;

    //Left of parent becomes right of grandparent
    T->parent->right = T->left;

    // if t's left is a valid node update it's parent field
    if (T->left != NULL)
        T->left->parent = T->parent;

    //Make grandparent as the left child of T(Rotate left)
    T->left = T->parent;

    //Change grandparents parent 
    T->parent->parent = T;

    //Change parents parent to upper subtree
    T->parent = temp;
    if (temp == NULL)
        root = T;
    else {
        if (temp->left == T->right)
            temp->left = T;
        if (temp->right == T->left)
            temp->right = T;
    }

    return root;
}
//insert function 

RBT* insert(RBT* root, int key) {
    RBT* newnode = NULL;
    if (root == NULL) {
        root = (RBT*) malloc(sizeof (RBT));
        root->data = key;
        root->parent = NULL;
        root->colour = 'b';
        root->left = root->right = NULL;
        return root;
    }
    newnode = add(root, key);
    if (newnode == root)
        return root;
    while (newnode != root && newnode->parent->colour == 'r') {
        //now check for leftside cases LXX case
        if (newnode->parent == newnode->parent->parent->left) {
            //now check for uncle being red
            if (newnode->parent->parent->right != NULL) {//lXr
                //change colour of parent and uncle to black and grandparents 
                //colour to red if it's not the root node of the tree
                newnode->parent->colour = 'b';
                newnode->parent->parent->right->colour = 'b';
                if (newnode->parent->parent != root)
                    newnode->parent->parent->colour = 'r';
                else
                    break;
                //change new to grandparent and check for colour imbalance upwards \
                in the tree
                newnode = newnode->parent->parent;
                continue;
            }
            else {
                if (newnode == newnode->parent->left)
                    root = rotateRight(newnode->parent, root); //LLB
                else {
                    root = rotateLeftNoColor(newnode, root); //LrB
                    root = rotateRight(newnode, root);
                }

            }


        }            //checking for RXX cases
        else if (newnode->parent == newnode->parent->parent->right) {
            //now check for uncle being red
            if (newnode->parent->parent->left != NULL) {
                //change colour of parent and uncle to black and grandparents 
                //colour to red if it's not the root node of the tree
                newnode->parent->colour = 'b';
                newnode->parent->parent->left->colour = 'b';
                if (newnode->parent->parent != root)
                    newnode->parent->parent->colour = 'r';
                else
                    break;
                //change new to grandparent and check for colour imbalance upwards \
                in the tree
                newnode = newnode->parent->parent;
                continue;

            } else {
                if (newnode == newnode->parent->right)
                    root = rotateLeft(newnode->parent, root);
                else {
                    root = rotateRightNoColor(newnode, root);
                    root = rotateLeft(newnode, root);
                }

            }



        }
    }
    inorderR(root);
    return root;
}

//***********************************************

/*****************************************
 *DELETION OF A NODE FROM A RED BLACK TREE
 ******************************************/
RBT* delete(int data, RBT* root, RBT* t) {

        RBT *temp;
      
        
        if(t==NULL)   // node to be deleted is not given
      {
        t=root;
        
        while(t!= NULL && t->data!=data) 
        {
          if(t->data>data)
            t=t->left;
          else
            t=t->right;
        }
        
        if(t==NULL)
        {
         printf("key is not present");
          return root;
        }
        else if(t == root && t->left==NULL && t->right==NULL)   // node deleted is the root and its the only node
        {
         free(t) ;
          return NULL; 
        }
        
        }
      
       
      if( (t->left==NULL && t->right==NULL)  ) // leaf node
      {
        if( t->colour=='r' )// leaf node is red 
        {
          if(t->parent->left==t)
          {
            t->parent->left=NULL;
          }
          else
          {
            t->parent->right=NULL;
          }
         free(t) ;
        }
        else      // leaf node is black so both u,v is black
        {
          if(t->parent->left!=NULL && t->parent->left==t) // t(leaf node) is left child
          {
            if(t->parent->right!=NULL && ( (t->parent->right->left!=NULL \
                && t->parent->right->left->colour=='r') ||
                (t->parent->right->right!=NULL && t->parent->right->right->colour=='r') ) )
     // sibling is b and atleast one of its child is r
            {
                
              if(t->parent->right->right!=NULL)  // sibling has right  child so RRb
              {
                if(t->parent->colour=='b')
                  t->parent->right->right->colour='b';
                root=rotateLeftNoColor(t->parent->right,root);
              }
              else  //sibling has a left child so RLb 
              {
                if(t->parent->colour=='b')
                  t->parent->right->left->colour='b';
                else
                  t->parent->colour='b';
                root=rotateRightNoColor(t->parent->right->left,root);
                root=rotateLeftNoColor(t->parent->right,root);
              }
             
              t->parent->left=NULL;
             free(t) ;
              
            }
            else if(t->parent->right!=NULL && t->parent->right->colour=='r' && (t->parent->right->left==NULL || t->parent->right->left->colour=='b') 
                    && (t->parent->right->right == NULL || t->parent->right->right->colour=='b') ) // parent is b,sibling is r and has two b children
            {
              
              t->parent->right->colour='b'; // make colour changes and RRb
              if(t->parent->right->left!=NULL)
                t->parent->right->left->colour='r';
              
              if( t->parent->right->right!=NULL) //RRb 
                root=rotateLeftNoColor(t->parent->right,root);
              else  //RLb
              { 
                root=rotateRightNoColor(t->parent->right->left,root);
                root=rotateLeftNoColor(t->parent->right,root);
              }
              
              if( (t->parent->right->left!=NULL && t->parent->right->left->colour=='r') &&   // sibling's left child has 2 r childs
                  (t->parent->right->right!=NULL && t->parent->right->right->colour=='r') )
              {
                root=rotateLeft(t->parent->right,root);
                
                t->parent->colour='b';
                t->parent->parent->right->colour='b';
                if(t->parent->parent!=root)
                   t->parent->parent->colour='r';
                
                
              }
              else if( t->parent->right->right!=NULL && t->parent->right->right->colour=='r' ) // sibling's left child has only 1 r right child
              {
               
                root=rotateLeft(t->parent->right,root);  // LLb
                
              }
              else if( t->parent->right->left!=NULL && t->parent->right->left->colour=='r' ) // sibling's left child has only 1 r left child
              {
                root=rotateRightNoColor(t->parent->right->left,root);  //LRb  
                root=rotateLeft(t->parent->right,root); 
              }
             
              t->parent->left=NULL;
             free(t) ;
              
              
            }
            else if(t->parent->colour=='r' && t->parent->right!=NULL && t->parent->right->colour=='b' &&
                    (t->parent->right->left==NULL || t->parent->right->left->colour=='b') && (t->parent->right->right == NULL || 
                    t->parent->right->right->colour=='b') )   // parent is red and sibling and its childs are b
            {
              
              t->parent->right->colour='r';
              t->parent->colour='b';
    
                t->parent->left=NULL;
               free(t) ;
    
            }
            else if(t->parent->colour=='b' && t->parent->right!=NULL && t->parent->right->colour=='b' &&
                   (t->parent->right->left==NULL || t->parent->right->left->colour=='b') && (t->parent->right->right == NULL || 
                    t->parent->right->right->colour=='b') ) // parent is b and silbling and its childs are b
            {
               temp=t;
    
              while(t!=root)
              {
                if(t->parent->left == t) // t is left child
                  t->parent->right->colour='r';
                else
                  t->parent->left->colour='b';
                t=t->parent;
              }
    
              temp->parent->left=NULL;
             free(temp) ;
              
            }
          }
          else  // t(leaf node) is right child
          {
            if(t->parent->left!=NULL && ( (t->parent->left->left!=NULL && t->parent->left->left->colour=='r') ||
              (t->parent->left->right!=NULL && t->parent->left->right->colour=='r') ) ) // sibling is b and atleast one of its child is r
            {
                
              if(t->parent->left->left!=NULL)  // sibling has left  child so LLb
              {
                if(t->parent->colour=='b')
                  t->parent->left->left->colour='b';
                root=rotateRightNoColor(t->parent->left,root);
              }
              else  //sibling has a right child so LRb 
              {
                if(t->parent->colour=='b')
                  t->parent->left->right->colour='b';
                else 
                  t->parent->colour='b';
                root=rotateLeftNoColor(t->parent->left->right,root);
                root=rotateRightNoColor(t->parent->left,root);
              }
    
              t->parent->right=NULL;
             free(t) ;
              
    
            }
            else if(t->parent->left!=NULL && t->parent->left->colour=='r' && (t->parent->left->left==NULL || t->parent->left->left->colour=='b') 
                    && (t->parent->left->right == NULL || t->parent->left->right->colour=='b') ) // parent is b,sibling is r and has two b children
            {
              
              t->parent->left->colour='b'; // make colour changes 
              if(t->parent->left->right!=NULL)
                t->parent->left->right->colour='r';
              
              if( t->parent->left->left!=NULL) //LLb 
                root=rotateRightNoColor(t->parent->left,root);
              else  //LRb
              { 
                root=rotateLeftNoColor(t->parent->left->right,root);
                root=rotateRightNoColor(t->parent->left,root);
              }
              
              if( (t->parent->left->left!=NULL && t->parent->left->left->colour=='r') &&   // sibling's left child has 2 r childs
                  (t->parent->left->right!=NULL && t->parent->left->right->colour=='r') )
              {
                root=rotateRight(t->parent->left,root);
                
                t->parent->colour='b';
                t->parent->parent->left->colour='b';
                if(t->parent->parent!=root)
                   t->parent->parent->colour='r';
                
              }
              else if( t->parent->left->left!=NULL && t->parent->left->left->colour=='r' ) // sibling's left child has only 1 r left child
              {
                root=rotateRight(t->parent->left,root);
                
              }
              else if( t->parent->left->right!=NULL && t->parent->left->right->colour=='r' ) // sibling's left child has only 1 r right child
              {
                root=rotateLeftNoColor(t->parent->left->right,root);
                root=rotateRight(t->parent->left,root);
              }
     
              t->parent->right=NULL;
             free(t) ;
              
              
            }
            else if(t->parent->colour=='r' && t->parent->left!=NULL && t->parent->left->colour=='b' &&
                    (t->parent->left->left==NULL || t->parent->left->left->colour=='b') && (t->parent->left->right == NULL || 
                    t->parent->left->right->colour=='b') )   //parent is red and sibling and its childs are b
            {
              
              t->parent->left->colour='r';
              t->parent->colour='b';
    
              t->parent->right=NULL;
             free(t) ;
              
            }
            else if(t->parent->colour=='b' && t->parent->left!=NULL && t->parent->left->colour=='b' &&
                   (t->parent->left->left==NULL || t->parent->left->left->colour=='b') && (t->parent->left->right == NULL || 
                    t->parent->left->right->colour=='b') ) // parent is b and sibling and its childs are b
            {
               temp=t;
              
              while(t!=root)
              {
               if(t->parent->right==t)
                 t->parent->left->colour='r';
               else
                 t->parent->right->colour='r';
               t=t->parent;
              }
              
              temp->parent->right=NULL;
             free(temp) ;
               
            }
          }
        }
    
      }
      else if( t->left==NULL || t->right==NULL) // one child node
      {
        if(t->left==NULL) // it has a right child
        {
    
            temp=t->right;  //temp will be its successor
            
            while(temp->left!=NULL)
              temp=temp->left;
            
            t->data=temp->data;
            
            root=delete(0,root,temp);
            
        } 
        else  //it has a left child
        {
           temp=t->left;   //temp will be its predeccessor
            
            while(temp->right!=NULL)
              temp=temp->right;
            
            t->data=temp->data;
            
            root=delete(0,root,temp);
        }
      }
      else  // it has two childs
      {
        temp=t->right;  //temp will be its successor
            
            while(temp->left!=NULL)
              temp=temp->left;
            
            t->data=temp->data;   
            
            root=delete(0,root,temp);
      }
        
      return root;
//    /*i.e if*/
//    if (toDel == NULL) {
//        /*ie we are not given the node to be deleted*/
//        //initialise toDel to root and traverse the tree
//        toDel = root;
//        //traverse till node does not become null or data is found
//        while (toDel != NULL && toDel->data != data) {
//            if (toDel->data > data) 
//                toDel = toDel->left;
//            else
//                toDel=toDel->right;
//          }
//        if(toDel==NULL){
//            fprintf(stderr,"Key not present");
//            exit(EXIT_FAILURE);
//        }
//        else if(toDel==root && (toDel->left==NULL && toDel->right==NULL)){
//            free(toDel);
//            root=NULL;
//            return root;
//        }
//
//    }
//    
//     
}

//search function

bool search(RBT* root, int key) {
    RBT* ptr;
    if (root == NULL) {
        fprintf(stderr, "Tree doesn't exists");
    } else {
        ptr = root;
        while (ptr != NULL ) {
            if (ptr->data > key) {
                ptr = ptr->left;
                continue;
            }
            if (ptr->data < key) {
                ptr = ptr->right;
                continue;
            }
            if (ptr->data == key)
                return true;
        }

    }
    return false;
}

// menu function to display available options

int menu() {
    int ch;
    printf("\n1.Insert\n2.Delete\n3.Search\n4.In-Order Traversal\n5.Exit");
    printf("\nEnter your choice");
    do {
        scanf("%d", &ch);
    } while (ch < 0 && ch > 6);
    return ch;
}

//**********************************************
// in order display to see the contents of the tree and the colour of the node

void inorderR(RBT* r) {
    if (r != NULL) {
        inorderR(r->left);
        printf("%d\t%c\n", r->data, r->colour);
        inorderR(r->right);
    }
}
/*
 * 
 */

// MAIN 

int main(int argc, char** argv) {
    RBT* root = NULL;
    bool present = false;
    int choice, key;
    do {
        choice = menu();
        switch (choice) {
            case 1:printf("Enter the key to be inserted");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:printf("Enter the key to be deleted");
                scanf("%d", &key);
                root = delete(key, root, NULL);
                inorderR(root);
                break;
            case 3:printf("Enter the key to be searched");
                scanf("%d", &key);
                present = search(root, key);
                if (present)
                    printf("%d is present in the RBT", key);
                else
                    printf("%d is not present in the RBT", key);
                break;
            case 4:inorderR(root);
                break;
            case 5:exit(EXIT_SUCCESS);
            default:printf("INVALID SELECTION");
                //exit(EXIT_FAILURE);
        }
    } while (choice != 5);


    return (EXIT_SUCCESS);
}
//****************************************************


// end of program
