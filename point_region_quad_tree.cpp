/*********************************************************************************
Write C/C++ program to implement PR-Quadtree to perform following operations.
1. Create()
2.Search()
3. RangeQuery()//this function will take the input as rectangular query region 
   and returns the set of points falling inside or on the boundaries of the 
   rectangular query region.
*********************************************************************************/
#include<iostream>

using namespace std;

struct point
{
    int x;
    int y;
};
typedef struct point point; 

struct quad_tree
{
    struct quad_tree* nw;
    struct quad_tree* ne;
    struct quad_tree* sw;
    struct quad_tree* se;
    point* data;
    point* bl;
    point* tr;
};
typedef struct quad_tree quad_tree;


quad_tree* initialise()
{
    quad_tree* t=new quad_tree();
    t->nw=NULL;
    t->ne=NULL;
    t->se=NULL;
    t->sw=NULL;
    t->data=NULL;
    t->bl=new point();
    t->tr=new point();
    return t;
}


void insert(quad_tree* root,point* p)
{

    quad_tree* t=NULL;
/* here we check two things
1)check whether that point is in that quad then go for split
2)check if the point lies in that quadrant or not    
*/
if(p->x >= root->bl->x && p->x <= root->tr->x && p->y >= root->bl->y && p->y <= root->tr->y)
    {	
        if(root->data==NULL && root->nw==NULL && root->ne==NULL && root->sw==NULL && root->se==NULL)
        {
            root->data=new point();
            root->data->x=p->x;
            root->data->y=p->y;
            return;
        }
        else
        {
            //left side
            if( (root->bl->x+root->tr->x)/2 >= p->x )
            {
                if( (root->bl->y+root->tr->y)/2 >= p->y )
                {
                    //left bottom
                    if(root->sw==NULL)
                    {
                    
                        t=initialise();
                        t->bl->x=root->bl->x;
                        t->bl->y=root->bl->y;
                        t->tr->x=(root->bl->x+root->tr->x)/2;
                        t->tr->y=(root->bl->y+root->tr->y)/2;
                        root->sw=t;
                    }                    
                    
                        insert(root->sw,p);
                    
                    if(root->data!=NULL)
                    {
                       point* e=root->data;
                        root->data=NULL;
                        insert(root,e);
                    }
/*means i inserted (100,25) but if insert (25,30) then i have to split it so i have to insert
(100,25) again so data is having the point (100,25) so i will connect it to app, quad and
make it NULL but if i make it NULL then if 3rd point comes then it will directly insert it
without checking bcoz of [if (root->data==NULL)] so we have written to check root->nw == NULL
root->ne == NULL,root->sw == NULL,root->se == NULL*/
                    
                }
                else
                {
                    //left top
                    if(root->nw==NULL)
                    {
                        t=initialise();
                        t->tr->x=(root->bl->x+root->tr->x)/2;
                        t->tr->y=root->tr->y;
                        t->bl->x=root->bl->x;
                        t->bl->y=(root->bl->y+root->tr->y)/2;
                        root->nw=t;
                    }
                    {
                        insert(root->nw,p);
                    }  
                    if(root->data!=NULL)
                    {
                        point* e=root->data;
                        root->data=NULL;
                        insert(root,e);


                    }
/*means i inserted (100,25) but if insert (25,30) then i have to split it so i have to insert
(100,25) again so data is having the point (100,25) so i will connect it to app, quad and
make it NULL but if i make it NULL then if 3rd point comes then it will directly insert it
without checking bcoz of [if (root->data==NULL)] so we have written to check root->nw == NULL
root->ne == NULL,root->sw == NULL,root->se == NULL*/  
                }
            }//if
            else
            {
                //right side
                if( (root->bl->y+root->tr->y)/2 >= p->y )
                {
                    //right bottom
                    if(root->se==NULL)
                    {
                        t=initialise();
                        t->bl->x=(root->bl->x+root->tr->x)/2;
                        t->bl->y=root->bl->y;
                        t->tr->x=root->tr->x;
                        t->tr->y=(root->bl->y+root->tr->y)/2;
                        root->se=t;
                    }
                    {
                        insert(root->se,p);
                    }
                    if(root->data!=NULL)
                    {
                        point* e=root->data;
                        root->data=NULL;
                        insert(root,e);
                        
                    }
/*means i inserted (100,25) but if insert (25,30) then i have to split it so i have to insert
(100,25) again so data is having the point (100,25) so i will connect it to app, quad and
make it NULL but if i make it NULL then if 3rd point comes then it will directly insert it
without checking bcoz of [if (root->data==NULL)] so we have written to check root->nw == NULL
root->ne == NULL,root->sw == NULL,root->se == NULL*/
                    
                }
                else
                {
                    //right top
                    
                    if(root->ne==NULL)
                    {
                        t=initialise();
                        t->bl->x=(root->bl->x+root->tr->x)/2;
                        t->bl->y=(root->bl->y+root->tr->y)/2;
                        t->tr->x=root->tr->x;
                        t->tr->y=root->tr->y;
                        root->ne=t;
                    }
                    {
                        insert(root->ne,p);
                    } 
                    if(root->data!=NULL)
                    {
                        point* e=root->data;
                        root->data=NULL;
                        insert(root,e);
                    }
/*means i inserted (100,25) but if insert (25,30) then i have to split it so i have to insert
(100,25) again so data is having the point (100,25) so i will connect it to app, quad and
make it NULL but if i make it NULL then if 3rd point comes then it will directly insert it
without checking bcoz of [if (root->data==NULL)] so we have written to check root->nw == NULL
root->ne == NULL,root->sw == NULL,root->se == NULL*/   
                }
            }
            
        }// if
      
    }
}


void print(quad_tree* t)
{
    if(t->data!=NULL)
    cout<<"data "<<t->data->x<<","<<t->data->y<<endl;
    if(t->sw!=NULL)
    print(t->sw);
    if(t->nw!=NULL)
    print(t->nw);
   if(t->ne!=NULL)
    print(t->ne);
    if(t->se!=NULL)
    print(t->se);
}

bool search(quad_tree* root,point* p)
{
    static bool flag=false;
    if(p->x >= root->bl->x && p->x <= root->tr->x && p->y >= root->bl->y && p->y <= root->tr->y)
    {
         if(root->data!=NULL && root->data->x==p->x && root->data->y==p->y)
         {
            flag=true;
            return flag;
         }
         if( (root->bl->x+root->tr->x)/2 >= p->x )
         {
             if( (root->bl->y+root->tr->y)/2 >= p->y )
             {
                if(root->sw!=NULL)
                    search(root->sw,p);
             }
             else
             {
                if(root->nw!=NULL)
                    search(root->nw,p);
             }
         }//if
         else
         {
             if( (root->bl->y+root->tr->y)/2 >= p->y )
             {
                if(root->se!=NULL)
                    search(root->se,p);
             }
             else
             {
                
                if(root->ne!=NULL)
                {
                    search(root->ne,p);}
             }   
         }
         return flag;
    }
}

point* range(quad_tree* root,point* bl,point* tr,int *n)
{
    static point p[100];
    if(p->x >= root->bl->x || p->x <= root->tr->x || p->y >= root->bl->y || p->y <= root->tr->y)
    {
         if(root->data!=NULL && root->data->x>=bl->x && root->data->x<=tr->x && root->data->y>=bl->y && root->data->y<=tr->y)
         {
            p[*n].x=root->data->x;
            p[*n].y=root->data->y;
            (*n)++;
            
         }
         if(root->sw!=NULL && !( (root->sw->bl->x>tr->x || root->sw->bl->y>tr->y) || (root->sw->tr->x<bl->x || root->sw->tr->y<bl->y)))
         {
            range(root->sw,bl,tr,n);//sw
         }
         if(root->se!=NULL && !( (root->se->bl->x>tr->x || root->se->bl->y>tr->y) || (root->se->tr->x<bl->x || root->se->tr->y<bl->y)))
         {
            range(root->se,bl,tr,n);//se
         }
         if(root->nw!=NULL && !( (root->nw->bl->x>tr->x || root->nw->bl->y>tr->y) || (root->nw->tr->x<bl->x || root->nw->tr->y<bl->y)))
         {
            range(root->nw,bl,tr,n);//nw
         }
         if(root->ne!=NULL && !( (root->ne->bl->x>tr->x || root->ne->bl->y>tr->y) || (root->ne->tr->x<bl->x || root->ne->tr->y<bl->y)))
         {
            range(root->ne,bl,tr,n);//ne
         }
         return p;
    }
    
}

int main()
{
    int n;
    cout<<"enter the number of points you want to insert\n";
    cin>>n;
    point* p=new point();
    quad_tree* root=initialise();
    root->bl->x=root->bl->y=-128;
    root->tr->y=root->tr->x=128;
    for(int i=0;i<n;i++)
    {
        cout<<"ENTER THE POINT";
        
        cin>>p->x>>p->y;
        insert(root,p);

    }
    cout<<"tree is\n";
    cout<<"*********\n";
    print(root);
    cout<<"*********\n";
    cout<<endl;
    cout<<"Enter the point you want to search";
    cin>>p->x>>p->y;
    cout<<endl<<endl;
    bool q;
    q=search(root,p);
    if(q)
    {
        cout<<"Point is present";
    }
    else
    {
        cout<<"Point is not present";
    }
    cout<<endl<<endl;
    
    cout<<"RANGE QUERY\n";
    point* m=new point();
    cout<<"ENTER THE STARTING POINT OF THE RANGE";
    cin>>m->x>>m->y;
    point* k=new point();
    cout<<"ENTER THE ENDING POINT OF THE RANGE";
    cin>>k->x>>k->y;
    int n1=0;
    p=range(root,m,k,&n1);
    cout<<"point in entered range is\n";
    for(int i=0;i<n1;i++)
        cout<<p[i].x<<","<<p[i].y<<endl;
    return 0;
}
