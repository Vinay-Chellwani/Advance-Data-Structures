/********************************************************************
C program for operations to be performed on red black trees
1)insert
2)delete
3)search
*********************************************************************/

#include<iostream>
#include<stdio.h>
#include<malloc.h>

using namespace std;

/******************************************************
Structure Red Black Trees which contains data,colour
of the node,left pointer,right pointer,and the parent
of the node
*******************************************************/

struct rbt
{
 int key;
 struct rbt* left;
 struct rbt* right;
 struct rbt* parent;
 char color;
};
struct rbt* T=NULL;

/*****************************************************
Driver Function to print the data in Inorder fashion
*****************************************************/
void inorder(struct rbt* T)
{
 struct rbt* temp=T;
 if(temp!=NULL)
  {
   inorder(temp->left);
   printf(" %d--%c",temp->key,temp->color);
   inorder(temp->right);

  }
}


/*******************************************************
Rotate left function function to rotate the tree in
left direction
*******************************************************/
void left_rotate(struct rbt *q)
{
  struct rbt *k;
  k=q->right;
  q->right=k->left;
  if(k->left!=NULL)
    k->left->parent=q;
  k->parent=q->parent;
  if(q->parent==NULL)
    T=k;
  else if((q->parent->left!=NULL)&&(q->key==q->parent->left->key))
    q->parent->left=k;
  else
    q->parent->right=k;

 k->left=q;
 q->parent=k;
}

/******************************************************
Rotate right function function to rotate the tree in
right direction
******************************************************/
void right_rotate(struct rbt *k)
{
 struct rbt *q;
 q=k->left;
 k->left=q->right;
 if(q->right!=NULL)
   q->right->parent=k;
 q->parent=k->parent;
 if(k->parent==NULL)
   T=q;
 else if((k->parent->left!=NULL)&&(k->key==k->parent->left->key))
   k->parent->left = q;
 else
  k->parent->right=q;

 q->right=k;
 k->parent=q;
}

/*******************************************
insert_1 function to insert the data
*******************************************/
void insert_1(struct rbt *p)
{
  struct rbt *k=NULL;

  while((p->parent!=NULL)&&(p->parent->color=='r'))
  {
   if((p->parent->parent->left!=NULL)&&(p->parent->key==p->parent->parent->left->key))
    {
     k=p->parent->parent->right;
     if((k!=NULL)&&(k->color=='r'))
      {                                            //LLr & LRr
       p->parent->color='b';
       k->color='b';
       p->parent->parent->color='r';
       p=p->parent->parent;
       cout<<"\nROTATION PERFORMED IS EITHER LLr OR LRr\n";
      }
     else
     {
      if((p->parent->right!=NULL)&&(p->key==p->parent->right->key))
      {
        p=p->parent;
       left_rotate(p);                //LRb
       cout<<"\nROTATION PERFORMED IS LRb\n";
      }
     p->parent->color='b';
     p->parent->parent->color='r';
     right_rotate(p->parent->parent);    //LLb
     cout<<"\nROTATION PERFORMED IS LLb\n";
     }
    }
   else
    {
     k=p->parent->parent->left;
     if((k!=NULL)&&(k->color=='r'))
      {                                          // RRr & RLr
        p->parent->color='b';
        k->color='b';
        p->parent->parent->color = 'r';
        p=p->parent->parent;
        cout<<"\nROTATION PERFORMED IS EITHER RRr AND RLr\n";
      }
     else
      {
      if ((p->parent->left!=NULL)&&(p->key == p->parent->left->key))
      {
       p=p->parent;
       right_rotate(p);
	   cout<<"\nROTATION PERFORMED IS RLb\n";            //RLb
      }
     p->parent->color='b';
     p->parent->parent->color='r';
     left_rotate(p->parent->parent);    //RRb
     cout<<"\nROTATION PERFORMED IS RRb\n";
     }
    }
  }
 T->color='b';

}

/*******************************************
Driver function used to insert a node
*******************************************/
void insertion(int n)
{
 struct rbt *q,*k;
 struct rbt* p=(struct rbt*)malloc(sizeof(struct rbt));
 p->key=n;
 p->left=NULL;
 p->right=NULL;
 p->color='r';
 q=T;
 if(T==NULL)
 {
  T=p;
  T->color='b';
  inorder(p);
  cout<<"\n\n";
  return;

 }
 while(q!=NULL)
 {
  k=q;
  if(p->key<q->key)                     //searching the node
   q=q->left;
  else
   q=q->right;
 }
 p->parent=k;
 if(p->key<k->key)
   k->left=p;                        // assigning the parent
 else
  k->right=p;

  insert_1(p);
  inorder(T);
  cout<<"\n\n";
}

/*********************************************************************
Function to find the successor of a node used in the deletion process
*********************************************************************/
struct rbt* successor(struct rbt *u)
{
  struct rbt *v;
  if (u->right)
   {
    v=u->right;
    while (v->left)
    {
     v = v->left;
    }
   return v;
   }
  v = u->parent;
  while (v && u == v->right)
  {
   u = v;
   v = v->parent;
  }
 return v;
}


/*******************************************************
delete1 function used in calculation to delete a node
*******************************************************/
void delete1(struct rbt *u)
{
 while (u !=T  && u->color == 'b')
  {
    struct rbt *s = NULL;
    if ((u->parent->left!=NULL) && (u == u->parent->left))
    {
     s=u->parent->right;
     if ((s!=NULL) && (s->color == 'r'))          //Left sibling is red.
      {
        s->color = 'b';
        u->parent->color = 'r';
        left_rotate(u->parent);
        s=u->parent->right;
      }
     if ((s!=NULL) && (s->right!=NULL) && (s->left!=NULL) && (s->left->color == 'b') && (s->right->color == 'b'))
     {
      s->color = 'r';                            //If both child are black.
      u = u->parent;
     }
     else if((s!=NULL) && (s->right->color == 'b'))
     {
     s->left->color = 'b';                     // Atleast one child is black
     s->color = 'r';
      right_rotate(s);                          //RL
      s = u->parent->right;
     }
     if(s!=NULL)
     {
      s->color = u->parent->color;
      u->parent->color = 'b';
      s->right->color = 'b';                   //RR
      left_rotate(u->parent);
      u = T;
     }
    }

  else
  {
   s = u->parent->left;
   if ((s!=NULL) && (s->color == 'r'))
   {
    s->color = 'b';
    u->parent->color = 'r';
    left_rotate(u->parent);
    if(u->parent!=NULL)
     s = u->parent->left;
   }
   if ((s!=NULL) && (s->right!=NULL) && (s->left!=NULL) && (s->right->color == 'b') && (s->left->color == 'b'))
    u = u->parent;                                       // Both child of sibling are black

   else if((s!=NULL) && (s->right!=NULL) && (s->left!=NULL) && (s->left->color == 'b'))
   {
    s->right->color = 'b';
    s->color = 'r';
    right_rotate(s);                                    // Atleast one child of sibling is red
    s = u->parent->left;
   }
  if(u->parent!=NULL)
  {
   s->color = u->parent->color;                       //LR
   u->parent->color = 'b';
  }
  if(s->left!=NULL)
   s->left->color = 'b';
  if(u->parent !=NULL)                                //RR
   left_rotate(u->parent);
  u = T;
  inorder(u);
  }
 }
 u->color = 'b';

}

/**************************************
Deletion function to delete a node
**************************************/
void deletion(int var)
{
 struct rbt *u = NULL, *v = NULL, *k;
 k=T;
 if((k->left ==NULL ) &&(k->right==NULL) && (k->key==var))  //To delete1 the only node.
 {
  k=NULL;
  printf("\nRBTREE is empty\n");
  free(k);
 }
 while(k->key !=var && k!=NULL)
 {                                                     //Searching the key to be delete1d
  if(var<k->key)
   k=k->left;
  else
   k=k->right;
 }
 if((k->left==NULL)||(k->right==NULL))
 {
  v = k;
 }
 else
 {
  v = successor(k);
 }
if(v->left!=NULL)                           // Assigning value to u(u is child to be replaced)
 {
  u = v->left;
 }
 else
 {
  if(v->right !=NULL)
   u = v->right;
 }
 if((u!=NULL) && (v->parent !=NULL))
  u->parent = v->parent;
 if ((v !=NULL) && (u!=NULL) && (v->parent==NULL))
  T=u;
 else if (v == v->parent->left)
  v->parent->left = u;
 else
  v->parent->right = u;
 if (v != k)
  k->key = v->key;
 if ((v!=NULL) && (u!=NULL) && (v->color == 'b'))
  delete1(u);                            //delete1 when u&v are black

 v=NULL;                                        //delete1 the node when u/v are red
 free(v);
 inorder(T);
 cout<<"\n\n";
}

/*********************************************
Search Function to search a particular data
*********************************************/
void searching(int data)
{
   struct rbt *p;
   p=T;
   while(p!=NULL)
   {
    if(p->key<data)
     p=p->right;
    else if(p->key>data)
     p=p->left;
    else if(p->key==data)
    {
     printf("Key Found");
     break;
    }
    else
    {
     printf("Invalid Input");
     break;
    }
   }
}


/**************************************************************
Main funtion from where the exectution of the functions begin
***************************************************************/
int main()
{
 int n,ch;
 do
  {
     printf("\nEnter: \n 1:Insert \n 2:Delete\n 3:Display\n 4:Search \n 5:Exit\n\n");
	 printf("Enter your choice:");
     scanf("%d",&ch);
   switch(ch)
  {
    case 1:
     printf("Enter the value to be added::");
     scanf("%d",&n);
     insertion(n);
     break;
    case 2:
     printf("Enter the value to be deleted::");
     scanf("%d",&n);
     deletion(n);
     break;
    case 3:
      printf("Tree Travasal is::\n");
      inorder(T);
       printf("\n\n");
     break;
    case 4:
     printf("Enter the number to be searched::");
     scanf("%d",&n);
     searching(n);
     break;
    }
  }while(ch!=5);
}



