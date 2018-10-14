/***********************************************
A C program to the functions of k-d tree
1)Create().
2)Insert(point)
3)Search(point)
4)FindMin(dim)//for Given dimension
5)Delete(point)
6)Nearest Neighbour (point)

***********************************************/

#include<iostream>
#include<math.h>
using namespace std;


struct kd_tree
{
    int* data;
    int dim;
    struct kd_tree* left;
    struct kd_tree* right;
};
typedef struct kd_tree kd_tree;


kd_tree* initialise(int dim,int* arr)
{
    kd_tree* t=new kd_tree();
    t->data=new int[dim];
    
    for(int i=0;i<dim;i++)
        t->data[i]=arr[i];
    t->left=t->right=NULL;
}


kd_tree* insert(kd_tree* t,int* arr,int dim,int cut)
{
    if(t==NULL)
    {
        t=initialise(dim,arr);
        return t;
    }
    if(arr[cut]>=t->data[cut])
        t->right=insert(t->right,arr,dim,(cut+1)%dim);
    else
        t->left=insert(t->left,arr,dim,(cut+1)%dim);
    return t;
}

void print(kd_tree* t,int dim)
{
    if(t!=NULL)
    {
        print(t->left,dim);
        for(int i=0;i<dim;i++)
            cout<<t->data[i]<<" ";
        cout<<endl;
        print(t->right,dim);
    }
}

// A utility method to determine if two Points are same
// in K Dimensional space
bool compare(int* arr1,int* arr2,int dim)
{
    // Compare individual pointinate values
    int i;
    for( i=0;i<dim;i++)
    {
        if(arr1[i]!=arr2[i])
            break;
    }
    if(i==dim)
        return true;
    else
        return false;
}

// Searches a Point in the K D tree.
bool search(kd_tree* root,int* arr,int dim,int cut)
{
    static bool flag=false;
    
    if(root!=NULL)
    {
        if(compare(root->data,arr,dim))
            flag=true;
        else if(root->data[cut]>arr[cut])
            search(root->left,arr,dim,(cut+1)%dim);
        else
            search(root->right,arr,dim,(cut+1)%dim);
    }
    return flag;
}

// A utility function to find minimum of three integers
kd_tree* min(kd_tree* a1,kd_tree* a2,kd_tree* a3,int req_dim)
{
    kd_tree* min;
    if(a1==NULL && a2==NULL)
        return a3;
    else if(a2==NULL)
    {
        if(a1->data[req_dim]<a3->data[req_dim])
        {
          min=a1;  
        }
           
           
        else
        {
            min=a3; 
        }        
    }
        
    else if(a1==NULL)
    {
        if(a2->data[req_dim]<a3->data[req_dim])
        {
            min=a2;
        }
        else
        {
            min=a3;
        }
        
    }
            
    else
    {
        if(a1->data[req_dim]<a2->data[req_dim])
        {
            if(a1->data[req_dim]<a3->data[req_dim])
               {
                   min=a1;
                }
            else
                {
                    min=a3;
                 }
        }
        else
        {
            if(a2->data[req_dim]<a3->data[req_dim])
            {
               min=a2;   
            }
            else
            {
              min=a3;   
            }
        }
    }
        
    return min;
    
}

kd_tree* min_dim(kd_tree* t,int req_dim,int dim,int cut)
{
    if(t==NULL)
      return NULL;
    if(cut==req_dim)
    {
        if(t->left!=NULL)
            return min_dim(t->left,req_dim,dim,(cut+1)%dim);
        else
            return t;
    }
    else
    {
        return( min(min_dim(t->left,req_dim,dim,(cut+1)%dim),min_dim(t->right,req_dim,dim,(cut+1)%dim),t,req_dim));  
    }
}


int dist(int* a1,int* a2,int dim)
{
    int dis=0;
    for(int i=0;i<dim;i++)
        dis+=pow(a1[i]-a2[i],2);
    return ceil(sqrt(dis));
}

kd_tree* nearest_neighbour(kd_tree* n,int* q,int dim,int cut)
{
    static kd_tree* p=NULL;
    static int w=99999;
    if(n->left==NULL && n->right==NULL)
    {
        int w1=dist(n->data,q,dim);
        if(w1 < w)
        {
            p=n;
            w=w1;
        }
    }
    else
    {
        bool flag=false;
        if(n->data[cut]>q[cut])
            flag=true;
            
        if(flag)
        {
            if(n->left!=NULL && q[cut]-w<n->data[cut])
                nearest_neighbour(n->left,q,dim,(cut+1)%dim);
            int w1=dist(n->data,q,dim);
            if(w1 < w)
            {   
                w=w1;
                p=n;
            }
            if(n->right!=NULL && q[cut]+w>=n->data[cut])
                nearest_neighbour(n->right,q,dim,(cut+1)%dim);
        }
        else //right
        {
            if(n->right!=NULL && q[cut]+w>=n->data[cut])
                nearest_neighbour(n->right,q,dim,(cut+1)%dim);
            int w1=dist(n->data,q,dim);

            if(w1 < w)
            {

                
                w=w1;
                p=n;
            }
            if(n->left!=NULL && q[cut]-w<n->data[cut])
                nearest_neighbour(n->left,q,dim,(cut+1)%dim);
        }
    }
    
    return p;
}


kd_tree* delete_tree(kd_tree* root,int* a,int dim,int cut)
{
    kd_tree* t=root,*q=root;
    
    while(t!=NULL && !compare(t->data,a,dim))
    {
        q=t;
        if(t->data[cut]>a[cut])
            t=t->left;
        else
            t=t->right;
        cut=(cut+1)%dim;    
    }
    kd_tree* temp=t;
    if(t!=NULL)
    {
        if(t->left==NULL && t->right==NULL)
          
        {
            
           if(q->left==t)
               q->left=NULL;
           else
               q->right=NULL;
            if(t==root)
                root=NULL;
            delete t;   
            return root;
         }
         if(t->right!=NULL)
        {
            kd_tree* min=min_dim(t->right,cut,dim,(cut+1)%dim);
            
            for(int i=0;i<dim;i++)
            {
                t->data[i]=min->data[i];
            }
            t->right=delete_tree(t->right,min->data,dim,(cut+1)%dim);
        }
        else if(t->left!=NULL)
        {
            kd_tree* min=min_dim(t->left,cut,dim,(cut+1)%dim);
            
            for(int i=0;i<dim;i++)
            {
                t->data[i]=min->data[i];
            }
            
            t->right=t->left;
            t->left=NULL;
            t->right=delete_tree(t->right,min->data,dim,(cut+1)%dim);
        }
        
    }
    return root;
}


int main()
{

    int dim;
    cout<<"enter the dimension "<<endl;
    cin>>dim;
    cout<<endl<<endl;
    int arr[dim];
    cout<<"enter the number of elements" <<endl;
    int n;
    cin>>n;
    cout<<endl<<endl;
    kd_tree* root=NULL;
    
    cout<<"INSERTING\n";
    for(int i=0;i<n;i++)
    {
        cout<<"Enter the point"<<endl;
        for(int j=0;j<dim;j++)
        {
            cin>>arr[j];
        }
            
        
        root=insert(root,arr,dim,0);
      
    }
    cout<<"The Tree Structure Is \n";
    print(root,dim);
    cout<<endl;
    int x=10,y=20,z=30;
    
    
    cout<<"SEARCHING\n";
    for(int i=0;i<1;i++)
    {
        cout<<"Enter the point to be searched "<<endl;
        for(int j=0;j<dim;j++)
        {
            cin>>arr[j];
        }
      
    }
    
    bool flag;
    
    flag=search(root,arr,dim,0);
    if(flag)
    {
        cout<<"The point is present "<<endl;
    }
    else
    {
        cout<<"The point not present "<<endl;
    }
    cout<<endl<<endl;

    cout<<"DELETING\n";
    for(int i=0;i<1;i++)
    {
        cout<<"Enter the point to be deleted "<<endl;
        for(int j=0;j<dim;j++)
        {
            cin>>arr[j];
        }
      
    }
    delete_tree(root,arr,dim,0);
    cout<<"After Deleting\n";
    print(root,dim);
    cout<<endl<<endl;
    
    cout<<"MINIMUM\n";
    kd_tree* p=NULL;
    cout<<"Enter the dimension in which you want to find minimum ";
    int req_dim;
    cin>>req_dim;
    p=min_dim(root,req_dim,dim,0);
    cout<<"Min in dim "<< req_dim<<" is ";
    for(int k=0;k<dim;k++)
    {
        cout<<p->data[k]<<" ";
    }
    cout<<endl<<endl;;
    
    cout<<"NEAREST NEIGHBOUR\n";
    for(int i=0;i<1;i++)
    {
        cout<<"Enter the point whose nearest neighbour you want to find "<<endl;
        for(int j=0;j<dim;j++)
        {
            cin>>arr[j];
        }
      
    }
    int w=99999;
    p=nearest_neighbour(root,arr,dim,0);
    cout<<"Nearest Neighbour is ";
    for(int k=0;k<dim;k++)
    {
        cout<<p->data[k]<<" ";
    }
    cout<<endl;
    return 0;
}



