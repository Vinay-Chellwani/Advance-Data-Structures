#include<iostream>
#include<math.h>
#include <iomanip>
#define NIL -1
using namespace std;


typedef struct veb
{
  int max;
  int min;
  int u;
  struct veb** cluster;
  struct veb* summary;
}veb;

int upper_sqrt(int no)
{
  return (pow(2,ceil( ( log(no)/log(2) ) / 2  )));
}

int lower_sqrt(int no)
{
  return (pow(2,floor( ( log(no)/log(2) ) / 2  )));
}

int cluster(int k,int u)
{
  return (k/(int)lower_sqrt(u));//l
}



int index(int k,int u)
{
    return (k % int(lower_sqrt(u))); // u
  //return (k & ((int)(pow(2,log(u)/log(2)))-1));
}

int number(int i,int j,int u)
{
  return (i*(lower_sqrt(u))+j);
}


veb* create(int u)
{
  if(u==2)
  {
    veb* head=new veb();
    head->u=u;
    head->min=head->max=NIL;
    head->cluster=NULL;
    head->summary=NULL;
    return head;
  }
  else
  {
    veb* head=new veb();
    head->u=u;
    head->cluster=new veb*[(int)upper_sqrt(u)];//u
    head->min=head->max=NIL;
    
    head->summary=create(upper_sqrt(u));//l
    
    for(int i=0;i<upper_sqrt(u);i++)//u
    {
      
      head->cluster[i]=create(lower_sqrt(u));//l
    }
    return head;
  }  
}

void print(veb*  t)
{
  if(t!=NULL)
  {
    print(t->summary);
    cout<<t->max<<" "<<t->min<<" "<<t->u<<"\n";
    if(t->u!=2)
    {
      for(int i=0;i<upper_sqrt(t->u);i++)//u
      {
        print(t->cluster[i]);
      }
    }
  }
}


void insert(veb* v,int x)
{
  if(v->min==NIL)
  {
    v->max=v->min=x;
    return;
  }
  else if(x<v->min)
  {
    int temp=x;
    x=v->min;
    v->min=temp;
  }
  if(v->u>2 )
  {
    if(v->cluster[cluster(x,v->u)]->min==NIL)
    {
      insert(v->summary,cluster(x,v->u));
      insert(v->cluster[cluster(x,v->u)],index(x,v->u));
    }
    else
    {
      insert(v->cluster[cluster(x,v->u)],index(x,v->u));
    }
  }
  if(v->max<x)
  {
    v->max=x;
  }
 
}


bool member(veb* v,int x)
{
  //if(x->u==2)
  {
    
  }
  if(x==v->min || x==v->max)
    return true;
  else if (x<v->min || x>v->max)
    return false;
  else
    return (member(v->cluster[cluster(x,v->u)],index(x,v->u))); 
}


int successor(veb* v,int x)
{
  int i,j;
  i=cluster(x,v->u);
  if(v->u==2)
  {
    if(x==0 && v->max==1)
      return 1;
    else
      return NIL;
  }
  else if (x<v->min)
  {
    return v->min;
  }
  if(index(x,v->u)< v->cluster[i]->max)        // successor in same cluster
  {
    j=successor(v->cluster[i],index(x,v->u));
  }
  else    // find the next set cluster
  {
    i=successor(v->summary,cluster(x,v->u));
    if(i==NIL)
      return NIL;
    else
      j=v->cluster[i]->min;
  
  }
  return number(i,j,v->u);
}


int predecessor(veb* v,int x)
{
  int i,j;
  if(v->u==2)
  {
    if(v->min==0 and x==1)
      return v->min;
    else
      return NIL;
  }
  else if(v->max<x)
    return v->max;
  i=cluster(x,v->u);
  if(index(x,v->u) > v->cluster[i]->min )
  {
    j=predecessor(v->cluster[i],index(x,v->u));
  }
  else
  {
    i=predecessor(v->summary,cluster(x,v->u));
    
    if(i==NIL)
    {
      if(v->min<x)
        return v->min;
      else 
        return NIL;
    }
    else
      j=v->cluster[i]->max;
  }
  return number(i,j,v->u);   
}

void delete_veb(veb* v,int x)
{
  int i,j;
  i=cluster(x,v->u);
  if(v->u==2)
  {
    if(v->min==v->max)
    {
      if(v->min==0 && x==0)
        v->max=v->min=NIL;
      else if(v->min==1 && x==1)
        v->max=v->min=NIL;
      return;
    }
    else
    {
      if(x==0)
       v->min=1;
      else
       v->max=0;
      return;
    }
  }
  if(x==v->min)
  {
    i=v->summary->min;
    if(i==NIL)
    {
      v->min=v->max=NIL;
      return;
    }
    else
      x=v->min=number(i,v->cluster[i]->min,v->u);
  }
  delete_veb(v->cluster[cluster(x,v->u)],index(x,v->u));
  if(v->cluster[i]->min==NIL)
  {
    delete_veb(v->summary,cluster(x,v->u));
  }
  if(x==v->max)
  {
    if(v->summary->max==NIL)
    {  
      v->max=v->min;
    }
   
    else
    {
      i=v->summary->max;
      v->max=number(i,v->cluster[i]->max,v->u);
    }
  }
}



int main()
{
    int i;
    veb* root=create(32);
    for(i=0;i<31;i++){
        insert(root,i);
    }
    int j;
    cout<<predecessor(root,65)<<endl;
    cout<<successor(root,31)<<endl;
    delete_veb(root,0);
    cout<<boolalpha <<member(root,5)<<endl;
    cout<<boolalpha <<member(root,255)<<endl;  
  return 0;
} 
