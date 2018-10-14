#include<iostream>
#include<string.h>
#include<stdbool.h>
#define NUM 2
using namespace std;


typedef struct pos_heap
{
  int no;
  struct pos_heap** char_;
}pos_heap;

pos_heap* initialize(int no)
{
  pos_heap* t=new pos_heap();
  t->no=no;
  t->char_=new pos_heap*[NUM];
  for(int i=0;i<NUM;i++)
  {
    t->char_[i]=NULL;
  }
  return t;
}
//11 10 9 8 7 6 5 4 3 2 1
//a  a  b a b b a a b a b
pos_heap* build_heap(char* str)
{
  pos_heap* head=NULL;

  for(int j=strlen(str)-1;j>=0;j--)
  {
    if(head==NULL)
    {
      head=initialize(1);
    }
    else
    {
      pos_heap*q, *t=head;
      int k=j;
      while(t!=NULL)
      {
        q=t;
        //cout<<str[k]<<" ";
        t=t->char_[str[k]%NUM];
        k++;
      }//cout<<strlen(str)-j<<endl;
      q->char_[str[k-1]%NUM]=initialize(strlen(str)-j);
    }
  }
  
  return head;
}

void print(pos_heap* t)
{
  if(t!=NULL)
  {
     cout<<t->no<<" ";
    for(int i=0;i<NUM;i++)
    {
     
      if(t->char_[i]!=NULL)
      {  
        if(i%2==0)
          cout<<"b\n";
        else
          cout<<"a\n";
        print(t->char_[i]);
      }
    }
  }
}

int* find_des(pos_heap* t,int n,int* p)
{
  static int arr[100];
  static int i=0;
  if(t!=NULL)
  {
    arr[i++]=t->no;
    //cout<<arr[i-1];
    (*p)++;
    for(int j=0;j<NUM;j++)
    {
      find_des(t->char_[j],n,p);
    }
  }
  
  return arr;
}

bool query(pos_heap* head,char* sub,char* str)
{
  int str_len=strlen(str);
  int len=strlen(sub);
  int k=0;
  int arr[len]={0};
  int i=0;
  int *arr2=NULL;
  int l=0;
  while(head!=NULL && k<len)
  {
    if( head->no>=len)
      arr[i++]=head->no;
    head=head->char_[sub[k++]%NUM];   
  }
  //for(int j=0;j<i;j++)
  //{  cout<<arr[j]<<" ";}cout<<endl;
  if(head!=NULL)
  {
    arr2=find_des(head,str_len,&l);
  }
  //cout<<"hey \n"<<arr2<<" "<<l<<endl;
  for(int p=0;p<l;p++)
  {
    arr[i++]=arr2[p];
  } 
  
  for(int j=0;j<i;j++)
  { // cout<<arr[j]<<" ";
    int c=0;
    int flag=1;
    for(int k=str_len-arr[j];(k<str_len && c < len);k++)
    {
      //cout<<str[k]<<","<<sub[c];
      if(str[k]!=sub[c++])
      {
        flag=0;
        //cout<<str[k]<<","<<sub[c-1];
        //cout<<"hi";
        break;
      } 
     
    }
     //cout<<"flag"<<flag; 
      if(!flag)
        arr[j]=0;
  } 
  
  cout<<"\nthe substring aa is present at ";
  for(int j=0;j<i;j++)
  {
    if(arr[j]!=0)
      cout<<arr[j]<<" ";
  }
  
}
int main()
{
  pos_heap* head=build_heap("aababbaabab");
  //cout<<strlen("aababbaabab");
  cout<<"position heap is\n";
  print(head);
  query(head,"aa","aababbaabab");
  return 0;
}

/*////////////////////////////////////////////////////////////////////////

input 

None(hardcoded)

output

position heap is
1 b
3 b
7 a
6 b
9 a
2 b
4 b
8 a
10 a
5 b
11 
the substring aa is present at 5 11 

*//////////////////////////////////////////////////////////////////////////
