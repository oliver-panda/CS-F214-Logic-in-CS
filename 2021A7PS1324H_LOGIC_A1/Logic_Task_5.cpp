#include <iostream>
using namespace std;

struct node{ //structure of each node of a tree
    char data;
    struct node *left, *right;
};


node* newNode(char* prefix){ //function to build a tree from prefix
    static int c=0; //initializing a counter
    if (prefix[c]=='\0'){
        return NULL;
    }
    node *n=(node*)malloc(sizeof(node)); //allocating a new node for every character
    n->data=prefix[c];
    c++;
    if (prefix[c-1]=='~' || prefix[c-1]=='*' || prefix[c-1]=='+' || prefix[c-1]=='>'){ //making subtrees
        if(prefix[c-1]=='~'){ //in case of negation, only right child will be assigned a value
            n->left=NULL;
            n->right=newNode(prefix);
        }
       else{
            n->left=newNode(prefix);
            n->right=newNode(prefix);
        }
    }
    return n;
}

struct TruthValue{
    char atom;
    bool Tp; //Truth of Proposition
};

bool TruthTable(node* n, TruthValue* t){ //Making the Truth Table
    if(n->data=='*'){ //Starting with all connectives
        return (TruthTable(n->left,t)&&TruthTable(n->right,t));
    }
    if(n->data=='+'){
        return (TruthTable(n->left,t)||TruthTable(n->right,t));
    }
    if(n->data=='~'){
        return(!TruthTable(n->right,t));
    }
    if(n->data=='>'){
        if (TruthTable(n->left,t)&&(!TruthTable(n->right,t))){
            return false;
        }
        else{
            return true;
        }
    }
    else{ //Truth Values for Atoms
        TruthValue* x=t;
        while(x->atom!=n->data){
            x++;
        }
        return x->Tp;
    }
}

int main()
{
    char s[]="~+~ab";
    node* n= newNode(s);
    TruthValue t[]={{'a',true},{'b',true}};
    cout<<(TruthTable(n,t)?"True":"False");
}