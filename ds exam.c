#include<stdio.h>
#include<stdlib.h>

struct node{
int data;
struct node* right;
struct node* down;
};
typedef struct node NODE;
void flatten(NODE* head);
void acceptlowerdata(NODE* ptr2)
{
	printf("\nEnter the data you want to store in the lower list:");
	scanf("%d",&ptr2->data);
	
	ptr2->right=NULL;
	ptr2->down=NULL;
}
// utility function to accept the data in both the lists 
void acceptdata(NODE* newnode)
{
	int num,i;
	NODE* downnode;
	NODE* ptr;
	NODE* temp=NULL;
	ptr=newnode;
	printf("\n\tEnter the data you want to store in the main list:");
	scanf("%d",&newnode->data);
	
	newnode->right=NULL;
	newnode->down=NULL;
	
	printf("\n\t\tEnter number of node to be entered in the lower list:");
	scanf("%d",&num);
	
	for(i=0;i<num;i++)
	{
		ptr=newnode;
		downnode=(NODE*)malloc(sizeof(NODE));
		if(downnode==NULL) // if malloc fails
		{
			fprintf(stderr,"MEMORY ALLOCATION FAILED");  
		}	//if
		else
		{
			acceptlowerdata(downnode);
			while(ptr!=NULL){
				temp=ptr;
				ptr=ptr->down;
			}//while
			temp->down=downnode;
			
		}//else
	}//for
	

}//acceptdata
//create list to create the main list
NODE* create(NODE* head)
{
	int num_nodes;
	NODE* newnode;
	int i;
	NODE* ptr;
	NODE* temp;
	printf("\n\tEnter the number of nodes you wish to enter:");
	scanf("%d",&num_nodes);
	for(i=0;i<num_nodes;i++)
	{
		newnode=(NODE*)malloc(sizeof(NODE));
		if(newnode==NULL) // if malloc fails
		{
			fprintf(stderr,"MEMORY ALLOCATION FAILED");  
		}	//if
		else
		{
			acceptdata(newnode);
			if(head==NULL)
			{
				head=newnode;
				
				continue;
			}
			ptr=head;
			while(ptr!=NULL){
				temp=ptr;
				ptr=ptr->right;
			}
			temp->right=newnode;
			//sort(head);
	
		}//else
	}//for
	
return head;
}//create

void display(NODE* head)
{
NODE* ptr=NULL;
NODE* ptr2=NULL;
	ptr=head;
	while(ptr!=NULL)
	{
		printf("%d ->",ptr->data);
		if(ptr->down!=NULL)
		{
			
			ptr2=ptr->down;
			
			while(ptr2!=NULL){
				
				printf("-> %d ->",ptr2->data);
				
				ptr2=ptr2->down;
				
			}//INNER WHILE
		}//if
		
		ptr=ptr->right;
	}//outer while
}
void main(){
	struct node* head=NULL;   //head pointer to the main list
	
	NODE* slist=NULL;
	int i;
	
	head = create(head);
	display(head);
	flatten(head);
	
}//main

void flatten(NODE* head)
{
	NODE* ptr=head;
	NODE* newh=NULL;
	NODE* t=NULL;
	int no=0;
	int cnt=0;
	ptr=head;
	while(ptr!=NULL)
	{
		no++;
		ptr=ptr->right;
	}//while
	ptr=head;
	while(ptr!=NULL)
	{
		if(ptr->right!=NULL && cnt<no)
		{
			t=ptr->right;
			ptr->right=NULL;
			cnt++;
		}
		while(ptr!=NULL)
		{
			if(ptr->down==NULL)
				{
				ptr->down=t;
				ptr=t;
				}
			while(ptr->down!=NULL)
			{
				ptr=ptr->down;
				continue;
			}
		}
	}
	ptr=head;
	while(ptr!=NULL)
	{
		printf("%d  ",ptr->data);
		ptr=ptr->down;
	}
//return head;
}//flatten


