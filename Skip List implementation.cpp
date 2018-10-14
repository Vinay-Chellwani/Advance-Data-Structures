/************************************************************************
C program for operations to be performed on skip list
1.)insert()
2.)search()
3.)delete()
4.)find_nth_smallest()
5.)find_records_within_range()//E.g. from roll_no 20 to roll_no 35 etc
***************************************************************************/
 
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include<iostream>
#include<string.h>
 
#define SKIPLIST_MAX_LEVEL 10

using namespace std;
 
struct snode 
{
    int roll_no;
    char name[30];
    int marks;
    int phone_no;
    
    struct snode **forward;// Array to hold pointers to node of different level
} ;
typedef struct snode snode;
 
struct skiplist 
{
    int level;
    int size;
    struct snode *header;
} ;
typedef struct skiplist skiplist;
 
skiplist *skiplist_init(skiplist *list) 
{
    int i;
    snode *header = (snode *) malloc(sizeof(struct snode));
    list->header = header;
    header->roll_no = INT_MAX;
    header->marks=INT_MAX;
    header->phone_no=INT_MAX;
    strcpy(header->name,"");
    header->forward = (snode **) malloc(sizeof(snode*) * (SKIPLIST_MAX_LEVEL + 1));
    for (i = 0; i <= SKIPLIST_MAX_LEVEL; i++) 
	{
        header->forward[i] = list->header;
    }
 
    list->level = 1;
    list->size = 0;
 
    return list;
}
 
static int rand_level() 
{
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL)
        level++;
    return level;
}
 
int skiplist_insert(skiplist *list, int roll_no, int marks) 
{
	// create update array and initialize it
    snode *update[SKIPLIST_MAX_LEVEL + 1];
    snode *x = list->header;
    char name[30];
    int phone;
    cout<<"enter name\n";
    cin>>name;
    cout<<"enter phone number\n";
    cin>>phone;
    cout<<endl<<endl;
    
    int i, level;
    
    /*   start from highest level of skip list
        move the current pointer forward while key 
        is greater than key of node next to current
        Otherwise inserted current in update and 
        move one level down and continue search
    */
    for (i = list->level; i >= 1; i--) 
	{
        while (x->forward[i]->roll_no < roll_no)
            x = x->forward[i];
        update[i] = x;
    }
    
    /* reached level 1 and forward pointer to 
       right, which is desired position to 
       insert key. 
    */
    x = x->forward[1];
    
    /* if current is NULL that means we have reached
       to end of the level or current's key is not equal
       to key to insert that means we have to insert
       node between update[0] and current node */
       

    if (roll_no == x->roll_no) 
	{
        x->marks = marks;
        x->phone_no=phone;
       strcpy(x->name,name);
        return 0;
    } 
	else 
	{
		// Generate a random level for node
        level = rand_level();
        
         
        // If random level is greater than list's current
        // level (node with highest level inserted in 
        // list so far), initialize update value with pointer
        // to header for further use
        if (level > list->level) 
		{
            for (i = list->level + 1; i <= level; i++) 
			{
                update[i] = list->header;
            }
            // Update the list current level
            list->level = level;
        }
 
        // create new node with random level generated
        x = (snode *) malloc(sizeof(snode));
        x->roll_no = roll_no;
        x->marks = marks;
        x->phone_no=phone;
        strcpy(x->name,name);
        x->forward = (snode **) malloc(sizeof(snode*) * (level + 1));
        // insert node by rearranging pointers 
        for (i = 1; i <= level; i++) 
		{
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
    return 0;
}


void skiplist_search(skiplist *list, int roll_no) 
{
    snode *x = list->header;

for(int i = list->level; i >= 1; i--)
{
	while(x->forward[i]!=NULL && x->forward[i]->roll_no<roll_no)
		x=x->forward[i];
}
x=x->forward[1];
if(x!=NULL && x->roll_no==roll_no)
{	printf("\n\nRecord present \n");
    printf("-----------------------------------------------\n");
    printf("Name\tRoll\tMarks\tPhone\n");
    printf("-----------------------------------------------\n");
    printf("%s\t%d\t%d\t%d\n->",x->name,x->roll_no,x->marks,x->phone_no);
    printf("-----------------------------------------------\n");
}
else
{
    printf("\n\nRecord not present \n");
    
}


}

void skiplist_node_free(snode *x)
 {
    if (x) 
	{
        free(x->forward);
        free(x);
    }
}
 

void delt(skiplist *list,int roll_no)
{
	int i;
	
    // create update array and initialize it
    snode *update[SKIPLIST_MAX_LEVEL + 1];
    snode *x = list->header;
    
    /*   start from highest level of skip list
        move the current pointer forward while key 
        is greater than key of node next to current
        Otherwise inserted current in update and 
        move one level down and continue search
    */

	for(i = list->level; i >= 1; i--)
	{
		while(x->forward[i]!=NULL && x->forward[i]->roll_no<roll_no)
			x=x->forward[i];
		update[i]=x;
	}
     /* reached level 1 and forward pointer to 
       right, which is possibly our desired node.*/

	x=x->forward[1];  
	
	// If current node is target node
	if(x!=NULL && x->roll_no==roll_no)
	{
		/* start from lowest level and rearrange
           pointers just like we do in singly linked list
           to remove target node */
           
		for(i = 1; i <= list->level; i++)
		{
			if(update[i]->forward[i]!=x)
                break;
            update[i]->forward[i]=x->forward[i];
		}
		
		skiplist_node_free(x);
		
        // Remove levels having no elements
        while (list->level > 1 && list->header->forward[list->level]== list->header)
            list->level--;
            
        cout<<"Successfully deleted roll number "<<roll_no<<"\n";
	}
}

void find(skiplist *list)
{
  snode* head=list->header;
  int n=0,cnt=0;
  snode *q;
  printf("Enter the nth number : ");
  scanf("%d",&n);
  q=head;
  while(cnt<n)
  {
     q=q->forward[1];
     cnt++;
  }
  if(q->forward[1]==NULL)
  {
    printf("\nRecord not present\n\n");
  }
  else
  {
     printf("\n\nRecord present \n");
     printf("-----------------------------------------------\n");
     printf("Name\tRoll\tMarks\tPhone\n");
     printf("-----------------------------------------------\n");
     printf("%s\t%d\t%d\t%d\n",q->name,q->roll_no,q->marks,q->phone_no);
     printf("-----------------------------------------------\n");
  }
}


void range(skiplist *list)
{
    snode* head=list->header;
     int from,to;
     snode *q;
     printf("\nFrom roll no : ");
     scanf("%d",&from);
     printf("\nTo roll no : ");
     scanf("%d",&to);
     q=head;
     printf("-----------------------------------------------\n");
     printf("Name\tRoll\tMarks\tPhone\n");
     printf("-----------------------------------------------\n");
     while(q->roll_no!=from && q!=NULL)
     {
      q=q->forward[1];
     }
     if(q==NULL)
     {
	 printf("Invalid range\n");
     }
     else
     {
      while(q->roll_no!=to)
      {
	printf("%s\t%d\t%d\t%d\n",q->name,q->roll_no,q->marks,q->phone_no);
	q=q->forward[1];
      }
      printf("%s\t%d\t%d\t%d\n",q->name,q->roll_no,q->marks,q->phone_no);
     printf("-----------------------------------------------\n");
     }
}
 
void skiplist_print(skiplist *list) 
{
    snode *x = list->header;
    while (x && x->forward[1] != list->header) 
	{
     printf("-----------------------------------------------\n");
     printf("Name\tRoll\tMarks\tPhone\n");
     printf("-----------------------------------------------\n");
     printf("%s\t%d\t%d\t%d\n->",x->forward[1]->name,x->forward[1]->roll_no,x->forward[1]->marks,x->forward[1]->phone_no);
     printf("-----------------------------------------------\n");
        x = x->forward[1];
    }
}

 
int main() 
{
    int choice;
    skiplist list;
    skiplist_init(&list);
    
    do 
    {

printf("\t1) Insert\n");
printf("\t2) SEARCH\n");
printf("\t3) DELETE\n");
printf("\t4) FIND SMALLEST\n");
printf("\t5) RANGE QUERY\n");
printf("\t6) PRINT\n");
printf("\t7) Exit\n");
printf("\n\tPlease enter your choice(1/2/3/4/5/6):");
scanf("%i", &choice);
cout<<endl;

  switch (choice)
{
   case 1:
           printf("Insert:--------------------\n");
           int n;
           cout<<"Enter no of records\n";
           cin>>n;
           for(int i=0;i<n;i++)
            {
                cout<<"Enter the record number "<<i+1<<"\n";
                  int roll_no,marks;
                 cout<<"Enter roll no\n";
                 cin>>roll_no;
                 cout<<"Enter marks\n";
                 cin>>marks;
                 skiplist_insert(&list, roll_no, marks);
             }
               skiplist_print(&list); 
                break;
 
    case 2: 
            printf("Search:--------------------\n");
            cout<<"enter the roll no to be searched";
            int ser;
            cin>>ser;
            skiplist_search(&list, ser);
            break;

    case 3: 
            printf("Delete:--------------------\n");
            cout<<"enter the roll no to be deleted";
            int del,res;
            cin>>del;
            delt(&list, del);
            skiplist_print(&list);
            break;
            
    case 4 :
        find(&list);
        break;
		     
    case 5 :
        range(&list);
        break;
        
    case 6:
        skiplist_print(&list);

    default:
            printf("\tIncorrect choice\n");
}
} while (choice != 7);
 
    return 0;
}
