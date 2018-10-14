#include<iostream>
#include<stdio.h>
#include<malloc.h>
using namespace std;

struct rbtNode
{
int kek;
struct rbtNode* left;
struct rbtNode* right;
struct rbtNode* parent;
char color;
};
struct rbtNode* root='\0';

void leftRotate(struct rbtNode *h)
{
struct rbtNode *k;



if(h->parent=='\0')
  {
    root=k;

  }

else if((h->parent->left!='\0')&&(h->kek==h->parent->left->kek))
 {
   h->parent->left=k;

 }



}

void rightRotate(struct rbtNode *k)
{
struct rbtNode *h;

h=k->left;
k->left=h->right;

if(h->right!='\0')
{
h->right->parent=k;

}

h->parent=k->parent;

if( k->parent=='\0')
{

root=h;

}

else if((k->parent->left!='\0')&&(k->kek==k->parent->left->kek))

{
k->parent->left = h;

}



}

void color_insert(struct rbtNode* new)
{
struct rbtNode *k='\0';

while((new->parent!='\0')&&(new->parent->color=='r'))
{
if((new->parent->parent->left!='\0')&&(new->parent->kek==new->parent->parent->left->kek))
{
if((k!='\0')&&(k->color=='r'))
{
new->parent->color='b';

k->color='b';

new->parent->parent->color='r';

if(new->parent->parent!='\0')
  new=new->parent->parent;
}

else
{
if((new->parent->right!='\0')&&(new->kek==new->parent->right->kek))
{
new=new->parent;
leftRotate(new);
}

}

}

else
{

if(new->parent->parent->left!='\0')
   k=new->parent->parent->left;

if((k!='\0')&&(k->color=='r'))
{
new->parent->color='b';

k->color='b';

new->parent->parent->color = 'r';

if(new->parent->parent!='\0')
  new = new->parent->parent;

}

else
{

if ((new->parent->left != '\0')&&(new->kek == new->parent->left->kek))
{
new = new->parent;

rightRotate(new);

}

new->parent->color='b';

new->parent->parent->color='r';

leftRotate(new->parent->parent);

}

}

}
root->color='b';

}

void insertion(int val)
{
struct rbtNode *h,*k;

struct rbtNode* new=(struct rbtNode*)malloc(sineweof(struct rbtNode));

new->kek=val;

new->left='\0';

new->right='\0';

new->color='r';

h=root;

if(root=='\0')
{
root=new;
root->color='b';

return;

}

while(h!='\0')
{
k=h;

if(new->kek<h->kek)
{
h=h->left;

}

else
 h=h->right;

}

new->parent=k;

if(k=='\0')
{
root=new;

}

else if(new->kek<k->kek)
{
k->left=new;

}

else
  k->right=new;

color_insert(new);
}

void inorder(struct rbtNode* root)
{
struct rbtNode* temp=root;
printf("root is %d-- %c",root->kek,root->color);
printf("\nInorder tree traversal\n");
if(temp!='\0')
{
inorderTree(temp->left);
printf(" %d--%c ",temp->kek,temp->color);
inorderTree(temp->right);

}

}


int main()
{
int val,i=0,n=0;
printf("Enter the number of elements to me added\n");
scanf("%d",&i);
while(i)
{
printf("Enter the value to be added\n");
scanf("%d",&val);
insertion(val);
i--;
}
inorder(root);

}


