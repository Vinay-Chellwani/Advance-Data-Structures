/***********************************************************************************
Cpp program for operations for database indexing
1)insert the index displacements for all the records and the GR no as key
2)search for Gr no and get the index. Open the file jump to the record and get 
  details in O(1). Also reduce the search of GR no from O(n) to O(log n).
************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <Windows.h>
#include <fstream>
using namespace std;

// A BTree node

class BTreeNode 
{
    int* GR; //array of gr nos
    int* disp; //displacement of the record in the file
    int t; // Minimum degree (defines the range for number of keys)
    BTreeNode **child; // An array of child pointers
    int n; // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
public:
    BTreeNode(int _t, bool _leaf); // Constructor

    void insertNonFull(int gr, int disp);

    void splitChild(int i, BTreeNode *y);

    void traverse();

    int search(int gr); // returns NULL if gr is not present.

    friend class BTree;
};


class BTree
{
    BTreeNode *root; // Pointer to root node
    int t; // Minimum degree
public:


    BTree(int _t) 
	{
        root = NULL;
        t = _t;
    }

    // function to traverse the tree

    void traverse() 
	{
        if (root != NULL) root->traverse();
    }

    // function to search a key in this tree

    int search(int gr) {
        return (root == NULL) ? -1 : root->search(gr);
    }

    // The main function that inserts a new key in this B-Tree
    void insert(int gr, int disp);
};



BTreeNode::BTreeNode(int t1, bool leaf1) 
{

    t = t1;
    leaf = leaf1;

    this->GR = new int[2 * t - 1];
    this->disp = new int[2 * t - 1];
    child = new BTreeNode*[2 * t];

    n = 0;
}



void BTreeNode::traverse() 
{
    // Traversing through n key and first n children
    int i;
    for (i = 0; i < n; i++) 
	{
        //if not leaf traverse through through its children 
        if (leaf == false)
            child[i]->traverse();
        cout << " " << GR[i];
    }

    
    if (leaf == false)
        child[i]->traverse();
}


int BTreeNode::search(int gr) 
{
    // Find the first key greater than or equal to gr
    int i = 0;
    while (i < n && gr > GR[i])
        i++;

    // If the found key is equal to gr, return this node
    if (GR[i] == gr)
        return this->disp[i];

    // If key is not found here and this is a leaf node,retrurn null
    if (leaf == true)
        return -1;

    // Otherwise go to the appropriate child
    return child[i]->search(gr);
}



void BTree::insert(int gr, int disp)
{	
    // If tree is empty
    if (root == NULL) 
	{
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->GR[0] = gr; // Insert key
        root->disp[0] = disp;
        root->n = 1; // Update number of keys in root
    } 
	else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1) 
		{
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false);

            // Make old root as child of new root
            s->child[0] = root;

            // Split the old root 
            s->splitChild(0, root);

            int i = 0;
            if (s->GR[0] < gr)
                i++;
            s->child[i]->insertNonFull(gr, disp);

            // Change root
            root = s;
        } 
		else // If root is not full, call insertNonFull for root
            root->insertNonFull(gr, disp);
    }
}



void BTreeNode::insertNonFull(int gr, int disp)
{
    // Initialize index as index of rightmost element
    int i = n - 1;

   
    if (leaf == true) 
	{

        while (i >= 0 && GR[i] > gr) 
		{
            GR[i + 1] = GR[i];
            this->disp[i + 1] = this->disp[i];
            i--;
        }

        GR[i + 1] = gr;
        this->disp[i + 1] = disp;
        n = n + 1;
    }
	else 
    {

        while (i >= 0 && GR[i] > gr)
            i--;

        
        
        if (child[i + 1]->n == 2 * t - 1) 
		{
            
            
            splitChild(i + 1, child[i + 1]);


            if (GR[i + 1] < gr)
                i++;
        }
        child[i + 1]->insertNonFull(gr, disp);
    }
}



void BTreeNode::splitChild(int i, BTreeNode *y)
{

    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    
    for (int j = 0; j < t - 1; j++) 
	{
        z->GR[j] = y->GR[j + t];
        z->disp[j] = y->disp[j + t];
    }
    
    
    if (y->leaf == false) 
	{
        for (int j = 0; j < t; j++)
            z->child[j] = y->child[j + t];
    }

    
    y->n = t - 1;


    for (int j = n; j >= i + 1; j--)
        child[j + 1] = child[j];


    child[i + 1] = z;


    for (int j = n - 1; j >= i; j--) 
	{
        GR[j + 1] = GR[j];
        disp[j + 1] = disp[j];
    }


    GR[i] = y->GR[t - 1];
    disp[i] = y->disp[t - 1];


    n = n + 1;
}

int getChoice() {
    int ch;
    cout << "\n\n*********************\n*VIT STUDENT SECTION*\n*********************\n1.Search Student(by GR)\n2.Exit";
    do {
        cout<<"\nEnter choice:";
        cin>>ch;
    } while (ch < 1 && ch > 2);
    return ch;
}


int main() {
    BTree root(15);
    int choice;
    int i;
    int toSearch;
    
    ifstream in("Student_Database1.csv"); // input
    if (!in) {
        cerr << "Cannot open Student file" << endl;
        return EXIT_FAILURE;
    }
    char str[100];

    in.getline(str, 99, '\n');
    for (i = 0; str[i] != '\0'; i++)
        str[i] = '\0';

    //go to the next line
    in.getline(str, 100);
    //ignore the previous bits
    for (i = 0; str[i] != '\0'; i++)
        str[i] = '\0';

    while (in.peek() != EOF) 
	{
        //get the GR no
        in.getline(str, 8, ',');

        string x;
        for (int j = 0; str[j] != '\0'; j++)
            x[j] = str[j];
        int Gr = stoi(x, NULL, 10);
        root.insert(Gr, in.tellg());
        //go to the next line
        in.getline(str, 100);
        
        //ignore the previous bits
        for (i = 0; str[i] != '\0'; i++)
            str[i] = '\0';
    }
    in.close();
    cout << "\nBTREE created";
    do {
         choice = getChoice();
        int disp;
        switch (choice) {
            case 1:cout << "Enter the GR no to be searched";
                cin>>toSearch;
                disp = root.search(toSearch);
                if (disp == -1)
                    cerr << "Not present";
                else {
                    in.open("Student_Database1.csv");
                    if (!in) 
					{

                        cerr << "Cannot open Student file" << endl;
                        return EXIT_FAILURE;
                    } 
					else 
					{
                        in.seekg(disp);
                        in.getline(str, 100);
                        cout << "GR No:" << toSearch;
                        cout << str;
                        in.close();

                    }
                }
                break;
            case 2:cout<<"Logging you off..."<<endl;
            Sleep(5000);
            cout<<"Shutting the system down"<<endl;
            Sleep(5000);
            cout<<"...";
                exit(EXIT_SUCCESS);
                break;
        }
    } while (choice != 2);
    return 0;
}
