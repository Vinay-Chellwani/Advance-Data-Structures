#include<iostream>
#include<math.h>
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


int cluster(int k,int u)
{
  return (k>>(int)sqrt(sqrt(u)));
}

int index(int k,int u)
{
  return (k & ((int)sqrt(u)-1));
}

int number(int i,int j,int u)
{
  return (i*(int)sqrt(u)+j);
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
    head->cluster=new veb*[(int)sqrt(u)];
    head->min=head->max=NIL;
    
    head->summary=create(sqrt(u));
    
    for(int i=0;i<sqrt(u);i++)
    {
      head->cluster[i]=create(sqrt(u));
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
      for(int i=0;i<sqrt(t->u);i++)
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


int member(veb* v,int x)
{
  //if(x->u==2)
  {
    
  }
  if(x==v->min || x==v->max)
    return 1;
  else if (x<v->min || x>v->max)
    return 0;
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
      x=v->min=number(i,index(v->cluster[i]->min,v->u),v->u);
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
      v->max=number(i,index(v->cluster[i]->max,v->u),v->u);
    }
  }
}



int main()
{
  int x;
  veb*  head=create(16);
//  print(head);
  cout<<cluster(8,16);
  for(int i=0;i<16;i++)
  {
    cin>>x;
    if(x==-1)
      break;
    insert(head,x);
//    print(head);
    cout<<endl;
    
  }
/* if(member(head,6))
    cout<<"yes";
  else
    cout<<"no";
   if(member(head,3))
    cout<<"yes";
  else
    cout<<"no";
  if(member(head,5))
    cout<<"yes";
  else
    cout<<"no";
  if(member(head,1))
    cout<<"yes";
  else
    cout<<"no";
  if(member(head,0))
    cout<<"yes";
  else
    cout<<"no";
  cout<<endl;*/
 /* delete_veb(head,5);
   if(member(head,5))
    cout<<"yes";
  else
    cout<<"no";
  delete_veb(head,0);
   if(member(head,0))
    cout<<"yes";
  else
    cout<<"no";
  delete_veb(head,2);
  if(member(head,2))
    cout<<"yes";
  else
    cout<<"no";
  delete_veb(head,1);
  if(member(head,1))
    cout<<"yes";
  else
    cout<<"no";
  delete_veb(head,3);
  if(member(head,3))
    cout<<"yes";
  else
    cout<<"no";*/
//  print(head);
// delete_veb(head,3);
 cout<<successor(head,2);
  cout<<successor(head,0);
//  cout<<successor(head,3);
  //cout<<predecessor(head,3);
  //cout<<predecessor(head,2);
  //cout<<predecessor(head,5);
  //delete_veb(head,8);
  if(member(head,3))
    cout<<"yes";
  else
    cout<<"no";
  return 0;
} 
