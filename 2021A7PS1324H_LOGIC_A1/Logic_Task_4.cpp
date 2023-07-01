#include <iostream>
using namespace std;

struct node //structure of each node of a tree
{
    char data;
    struct node *left, *right;
};


node* newNode(char* prefix) //function to build a tree from prefix
{
    static int c=0; //initializing a counter
    if (prefix[c]=='\0')
    {
        return NULL;
    }
    node *n=(node*)malloc(sizeof(node)); //allocating a new node for every character
    n->data=prefix[c];
    c++;
    if (prefix[c-1]=='~' || prefix[c-1]=='*' || prefix[c-1]=='+' || prefix[c-1]=='>') //making subtrees
    {
       if(prefix[c-1]=='~') //in case of negation, only right child will be assigned a value
       {
            n->left=NULL;
            n->right=newNode(prefix);
       }
       else
       {
            n->left=newNode(prefix);
            n->right=newNode(prefix);
       }
    }
    return n;
}



int height(node *n) //height of tree
{   
    if(n==NULL){
        return 0;
    }
    int LeftDepth=height(n->left);
    int RightDepth=height(n->right);
    if(LeftDepth>RightDepth){
        return LeftDepth+1;
    }
    else{
        return RightDepth+1;
    }
}

int main()
{
    char s[]="~+~ab";
    node* n= newNode(s);
    cout<<height(n)<<endl;;
}