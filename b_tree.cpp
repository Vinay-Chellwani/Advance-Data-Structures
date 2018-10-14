#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define m 5
void insertNonFull(int k,struct btree *t);
int splitchild(int i,struct btree *t,struct btree *s,int key);
struct btree
    {
        int *key;      //array of keys
        struct btree **child;
        struct btree *parent;
        int n;      //current number of keys in a node
        bool leaf;       //=1 if the node is a leaf node
    }*root=NULL;

struct btree* insert(int k)
    {
        printf("Entered insert\n");
        if(root==NULL)
            {
                printf("Entered first if\n");
                root=(struct btree*)malloc(sizeof(struct btree));
                printf(" \n\n%u ",root);
                root->n=0;
                root->leaf=1;
                root->key=(int*)malloc((m-1)*sizeof(int));
                root->child=(struct btree**)malloc(m*sizeof(struct btree*));
                root->parent=NULL;
                root->key[0]=k;
                root->n=root->n+1;
                printf("roott->key[0]=  %d  \n",root->key[0]);
            }
        else
            {
                printf("Entered else\n");
                struct btree *t;
                t=root;
                if(t->n==(m-1))          //if the node is full
                    {
                        printf("Entered if(t->n==m-1)\n");
                        struct btree *s=(struct btree*)malloc(sizeof(struct btree));        //new node is created
                        s->child[0]=t;
                        printf("s->child[0]=  %d \n",s->child[0]);
                        splitchild(0,root,s,k);
                        printf("After splitchild\n");
                    }
                else
                    {
                        insertNonFull(k,t);

                    }
            }
        return root;
    }
void insertNonFull(int k,struct btree *t)
    {
        printf("Entered insert non full\n");
        int i=t->n-1;       //i is the index of the rightmost element
        if(t->leaf==1)      //if it is a leaf node
            {
                printf("Entered if\n");
                printf("i= %d \n",i);
                printf("n= %d \n",t->n);
                while(i>=0 && t->key[i]>k)
                    {

                        t->key[i+1]=t->key[i];
                        i--;
                    }
                t->key[i+1]=k;
                t->n=t->n+1;
                printf("n= %d \n",t->n);
                printf("root->key[i]=  %d \n",root->key[i]);
            }
        else
            {
                while(i>=0 && t->key[i]>k)        //find child which is going to have new key
                    {
                        i--;
                    }
               /* if(t->child[i+1]==(m-1))
                    {
                        splitchild(i+1,t->child[i+1],k);
                        insertNonFull(k,t->child[i+1]);
                    }*/
            }

    }

int splitchild(int i,struct btree *t,struct btree *s,int key)
    {
        printf("Entered splitchild\n");
        int temp[m],j;
       struct btree *z;
       z=(struct btree*)malloc(sizeof(struct btree));
      //  z=new struct btree;
      if(z==NULL)
      printf("A\n");
       z->n=(m/2);
       printf("z->n %d",z->n);
       printf("After declaration  %d \n",z);
        z->key=(int*)malloc((m-1)*sizeof(int));
       printf("After declaration  %d \n",z);
        z->key=(int*)malloc((m-1)*sizeof(int));
        printf("After declaration  %d \n",z);
       z->child=(struct btree**)malloc(m*sizeof(struct btree*));
       printf("After declaration  %d \n",z);
       z->n=(m/2);
        printf("Before for\n");
        for(j=0;j<=(m-1);j++)
            {
                temp[j]=t->key[j];
            }
            for(j=0;j<(m-1);j++)
            {
                printf("Inside for ");
                printf("  %d  \n",temp[j]);
            }
        j=m-2;
        while(j>=0 && temp[j]>key)
            {
                temp[j+1]=temp[j];
                j--;
            }
        temp[j+1]=key;          //inserting the key inside temporary array
        for(j=0;j<=(m-1);j++)
            {
                printf("Inside for ");
                printf("  %d  \n",temp[j]);
            }
        s->key[i]=temp[m/2];            //first element of new root=middle element of temporary array
        printf("  s->key[i]  %d  m/2= %d \n",s->key[i],m/2);
        for(j=0;j<(m/2);j++,i++)
            {
                printf("Inside for\n");
                z->key[i]=temp[i+m/2];
                printf(" i= %d  z->key[i]= %d ",i,z->key[i]);          //copying last m/2 keys of temp to z
            }
        t->n=m/2;
        if(t->leaf==0)                      //if t is not a leaf node(children also have to be shifted)
            {
                for(j=0;j<(m/2);j++)                //copying last m/2 children of t to z
                    {
                        z->child[j]=t->child[j+m/2];
                    }
                s->child[i+1]=z;
                s->n=s->n+1;
            }
        return 0;
   }
int main()
    {
        /*printf("Enter the number of nodes\n");
        scanf("%d",&n);*/
        root=insert(5);
        root=insert(6);
        root=insert(7);
        root=insert(8);

        printf("\n\nAfter inserting 8\n\n");
        root=insert(3);
        printf("After inserting 3\n");
        return 0;
    }
