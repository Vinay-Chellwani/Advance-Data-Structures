/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bsol.c
 * Author: VINAY CHELLWANI
 *
 * Created on February 6, 2018, 11:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define M 3	
#define MAX (M-1)	
#if M%2==0
#define CEIL_Mdiv2 (M/2)
#else
#define CEIL_Mdiv2 ((M+1)/2)
#endif
#define MIN (CEIL_Mdiv2-1)	

struct node
{
	int count;
	int key[MAX];
	struct node *child[MAX+1];
};

struct node* Search(int skey,struct node *p,int *pn);
int search_node(int skey,struct node *p,int *pn);
void display(struct node *ptr,int blanks);
void inorder(struct node *ptr);

//Functions used in insertion
struct node *Insert(int ikey,struct node *proot);
int rec_ins(int ikey,struct node *p,int *pk,struct node **pkrchild);
void insertByShift(int k,struct node *krchild,struct node *p,int n);
void split(int k,struct node *krchild,struct node *p,int n,int *upkey,struct node **newnode);


struct node *Search(int skey, struct node *p, int *pn)
{
	if( p == NULL )  
		return NULL;
	else if( search_node(skey, p, pn ) )	
		return p;
	else         
		return Search( skey, p->child[*pn], pn); 
}//End of Search()

int search_node(int skey, struct node *p, int *pn)
{
	if( skey < p->key[1] )
	{
		*pn = 0;
		return 0;
	}
	*pn = p->count;
	while( ( skey < p->key[*pn] ) && *pn>1 )
		(*pn)--;
	if( skey == p->key[*pn] )
		return 1;
	else
		return 0;
}//End of search_node()

struct node *Insert(int ikey, struct node *proot)
{
	int k, taller;
	struct node *krchild, *temp;
	
	taller = rec_ins(ikey, proot, &k, &krchild);
	
	if( taller )  
	{
		temp = (struct node *)malloc( sizeof(struct node) );
		temp->count = 1;
		temp->child[0] = proot;	
		temp->key[1] = k;
		temp->child[1] = krchild;
		proot = temp;
	}
	return proot;
}//End of Insert()

int rec_ins(int ikey, struct node *p, int *pk, struct node **pkrchild)
{
	int n;
	int flag;

	if( p == NULL )  
	{
		*pk = ikey;
		*pkrchild = NULL;
		return 1;   
	}
	
	if( search_node( ikey, p, &n) ) 
	{
		printf("Duplicate keys are not allowed\n");
		return 0;
	}

	flag = rec_ins( ikey, p->child[n], pk, pkrchild );
	if( flag )
	{
		if( p->count < MAX )
		{
			insertByShift(*pk, *pkrchild, p, n);
			return 0;
		}
		else
		{
			split(*pk, *pkrchild, p, n, pk, pkrchild );
			return 1;  
		}
	}
	return 0;
}//End of rec_ins()

void insertByShift( int k, struct node *krchild, struct node *p, int n)
{
	int i;
	
	for( i = p->count; i > n; i-- )
	{
		p->key[i+1] = p->key[i];
		p->child[i+1] = p->child[i];
	}
	p->key[n+1] = k;
	p->child[n+1] = krchild;
	p->count++;
}//End of insertByShift()

void split(int k, struct node *krchild, struct node *p, int n, int *upkey, struct node **newnode)
{
	int i,j;
	int lastkey;
	struct node *lastchild;
	int d = CEIL_Mdiv2;

	if( n == MAX )
	{
		lastkey = k;
		lastchild = krchild;
	}
	else
	{
		lastkey = p->key[MAX];
		lastchild = p->child[MAX];
		for( i = p->count-1; i > n; i-- )
		{
			p->key[i+1] = p->key[i];
			p->child[i+1] = p->child[i];
		}
		p->key[i+1] = k;
		p->child[i+1] = krchild;
	}
	*newnode = (struct node *)malloc(sizeof(struct node) );
	*upkey = p->key[d];
	
	for( i=1, j=d+1; j<=MAX; i++,j++ )
	{
		(*newnode)->key[i] = p->key[j];
		(*newnode)->child[i] = p->child[j];
	}
	
	(*newnode)->child[0] = p->child[d];
	p->count = d-1;/*Number of keys in the left splitted node*/
	(*newnode)->count = M - d;  
	(*newnode)->key[M-d] = lastkey;
	(*newnode)->child[M-d] = lastchild;
}//End of split()


void display(struct node *ptr, int blanks)
{
	if(ptr)
	{
		int i;
		for(i=1; i<=blanks; i++)
			printf(" ");
		for(i=1; i<=ptr->count; i++)
			printf("%d ",ptr->key[i]);
		printf("\n");
		for(i=0; i<=ptr->count; i++)
			display(ptr->child[i], blanks+10);
	}
}//End of display()

void inorder(struct node *ptr)
{
	int i;
	if(ptr!=NULL )
	{
		for(i=0; i<ptr->count; i++)
		{
			inorder(ptr->child[i]);
			printf("%d\t",ptr->key[i+1] );
		}
		inorder(ptr->child[i]);
	}
}//End of inorder()

/*
 * 
 */
int main(int argc, char** argv) {
    struct node *root = NULL, *ptr;
	int key,choice,n;
	while(1)
	{
		printf("1.Search\n2.Insert\n");
		printf("3.Display\n4.Inorder traversal\n5.Quit\n");
		printf("Enter your choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:printf("Enter the key to be searched : ");
				scanf("%d",&key);
				if( (ptr=Search(key, root, &n)) == NULL )
					printf("Key not present\n");
				else
					printf("Node %p, Position %d\n",ptr,n);
				break;
			case 2:	printf("Enter the key to be inserted : ");
				scanf("%d",&key);
				root = Insert(key, root);
				break;
			case 3:	printf("Btree is :\n\n");
				display( root, 0 );
				printf("\n\n");
				break;
			case 4:	inorder(root);
				printf("\n\n");
				break;
			case 5:	exit(EXIT_SUCCESS);
			default:printf("Wrong choice\n");
				break;
		}//End of switch
	}//End of while

    return (EXIT_SUCCESS);
}

