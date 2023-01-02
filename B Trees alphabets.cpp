#include<iostream>
using namespace std;


class BTreeNode
{
    char *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;
public:
    BTreeNode(int _t, bool _leaf);


    void insertNonFull(char k);



    void splitChild(int i, BTreeNode *y);


    void traverse();



friend class BTree;
};


class BTree
{
    BTreeNode *root;
    int t;
public:

    BTree(int _t)
    {  root = NULL;  t = _t; }


    void traverse()
    {  if (root != NULL) root->traverse(); }





    void insert(char k);
};


BTreeNode::BTreeNode(int t1, bool leaf1)
{

    t = t1;
    leaf = leaf1;


    keys = new char[2*t-1];
    C = new BTreeNode *[2*t];


    n = 0;
}

void BTreeNode::traverse()
{

    int i;
    for (i = 0; i < n; i++)
    {

        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }


    if (leaf == false)
        C[i]->traverse();
}





void BTree::insert(char k)
{

    if (root == NULL)
    {

        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {

        if (root->n == 2*t-1)
        {

            BTreeNode *s = new BTreeNode(t, false);


            s->C[0] = root;


            s->splitChild(0, root);


            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);


            root = s;
        }
        else
            root->insertNonFull(k);
    }
}


void BTreeNode::insertNonFull(char k)
{

    int i = n-1;


    if (leaf == true)
    {

        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }


        keys[i+1] = k;
        n = n+1;
    }
    else
    {

        while (i >= 0 && keys[i] > k)
            i--;


        if (C[i+1]->n == 2*t-1)
        {

            splitChild(i+1, C[i+1]);


            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}


void BTreeNode::splitChild(int i, BTreeNode *y)
{

    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;


    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];


    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }


    y->n = t - 1;


    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];


    C[i+1] = z;


    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];


    keys[i] = y->keys[t-1];


    n = n + 1;
}


int main()
{
    int degree; int n;char num;
    cout<<"Enter degree"<<endl;
    cin>>degree;
    BTree t(degree);
    cout<<"Enter no of elements"<<endl;
    cin>>n;
    cout<<"Enter elements"<<endl;
    for(int i=0;i<n;i++)
    {
      cin>>num;
    t.insert(num);
    }


    cout << "Traversal of the constucted tree is ";
    t.traverse();


    return 0;
}