#include <iostream>
#include <string.h>
using namespace std;

int prio(char x){ //making priority orders for connectives
    switch(x){
        case '(':
            return 5;
            break;
        case ')':
            return 5;
            break;
        case '~':
            return 4;
            break;
        case '*':
            return 3;
            break;
        case '+':
            return 2;
            break;
        case '>':
            return 1;
            break;
    }
}

string Infix2Prefix(string Infix){ //Function from Infix to Prefix
    reverse(Infix.begin(),Infix.end());
    int l=Infix.length();
    string Prefix="";
    string Store=""; //initializing a string and using it's back function to access Top of a Stack, instead of explicitly using a Stack
    for(int i=0; i<=l-1; i++){
        if(Infix[i]!='(' && Infix[i]!=')' && Infix[i]!='~' && Infix[i]!='*' && Infix[i]!='+' && Infix[i]!='>'){ //all atoms get added to Prefix
            Prefix+=Infix[i];
        }
        else if(Infix[i]==')'){
            Store+=Infix[i];
        }
        else if(Infix[i]=='('){ //closing brackets and adding the characters between them to Prefix
            while(Store.back()!=')'){
                Prefix+=Store.back();
                Store.pop_back();
            }
        }
        else if(Infix[i]=='~' || Infix[i]=='*' || Infix[i]=='+' || Infix[i]=='>'){ //adding connectives priority wise into Prefix or Store
            if(Store.empty()){
                Store+=Infix[i];
            }
            else{
                if(prio(Infix[i])<prio(Store.back())){
                    while(!Store.empty() && Store.back()!=')' && (prio(Infix[i])<prio(Store.back()))){
                        Prefix+=Store.back();
                        Store.pop_back();
                    }
                    Store+=Infix[i];
                }
                else{
                    Store+=Infix[i];
                }
            }
        }
    }
    while(!Store.empty()){ //adding all the leftovers into the Prefix
        if(Store.back()!=')'){
            Prefix+=Store.back();
        }
        Store.pop_back();
    }
    reverse(Prefix.begin(),Prefix.end());
    return Prefix;
}



int main(){
    string s;
    cin>>s;
    cout<<Infix2Prefix(s)<<endl;
}