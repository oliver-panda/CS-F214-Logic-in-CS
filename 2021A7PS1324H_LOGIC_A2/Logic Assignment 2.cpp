#include<iostream>
#include<string.h>
using namespace std;

#define LIMIT 20 //since number of rows in 2D array of Proof as well as Rule has to be given.

int Validity(char proof[LIMIT][LIMIT],char rule[LIMIT][LIMIT],int i){

    //Premise
    if(rule[i][0]=='P'){
        int control=1; // for checking whether formula is valid or not, 0 if invalid
        for (int j = 0; proof[i][j+1] !='\0'; j++){
            if((65<=proof[i][j] && proof[i][j]<=90) || (97<=proof[i][j] && proof[i][j]<=122) || (proof[i][j]=='>') || (proof[i][j]=='*') || (proof[i][j]=='+') || (proof[i][j]=='~') || (proof[i][j]=='(') || (proof[i][j]==')'))
                continue;
            else{
                control= 0;
                break;
            }              
        }
        return control;
    }

    //AND Introduction
    else if(rule[i][0]=='*'&&rule[i][1]=='i' && rule[i][2]=='/' && rule[i][4]=='/' && (rule[i][3]-49<i) && (rule[i][5]-49<i)){
        char str1[LIMIT] = {'\0'};
        strcat(str1,"(");
        strcat(str1,proof[rule[i][3]-49]);
        strcat(str1,"*");
        strcat(str1,proof[(int)rule[i][5]-49]);
        strcat(str1,")");
        if(strcmp(str1,proof[i])==0)
        return 1;
        else 
        return 0;
    }

    //AND Elmn 1
    else if(rule[i][0]=='*'&&rule[i][1]=='e' && rule[i][2]=='1' && rule[i][3]=='/' && (rule[i][4]-49<i)){
        char str2[LIMIT] = {'\0'};
        int t =1;
        for (int j = 1;  ; j++)
        {
            if(t==1){
                if(proof[rule[i][4]-49][j]=='*')
                break;
            }
            if(1){
            str2[j-1]=proof[rule[i][4]-49][j];
            }
            if(proof[rule[i][4]-49][j]=='(')
            t++;
            if(proof[rule[i][4]-49][j]==')')
            t--;
        }
        if(strcmp(str2,proof[i])==0)
        return 1;
        else 
        return 0;
    }

    //AND Elmn 2
    else if(rule[i][0]=='*'&&rule[i][1]=='e' && rule[i][2]=='2' && rule[i][3]=='/' && (rule[i][4]-49<i)){
        char str2[LIMIT] = {'\0'};
        int t =0,control=0,pos=0;
        for (int j = 0;  ; j++)
        {
            if(t==1){
                if(proof[rule[i][4]-49][j]=='*'){
                    control=1;

                }
            }
            if(t==1){
                if (proof[rule[i][4]-49][j+1]==')')
                break;
            }
            if(control){
                
                str2[pos]=proof[rule[i][4]-49][j+1];
                pos++;
            }
            if(proof[rule[i][4]-49][j]=='(')
            t++;
            if(proof[rule[i][4]-49][j+1]==')')
            t--;
        }   
        if(strcmp(str2,proof[i])==0)
        return 1;
        else 
        return 0;
    }

    //OR Introduction 1
    else if(rule[i][0]=='+'&&rule[i][1]=='i' && rule[i][2]=='1' && rule[i][3]=='/' && (rule[i][4]-49<i)){
        char str2[LIMIT] = {'\0'};
        strcat(str2,"(");
        strcat(str2,proof[rule[i][4]-49]);
        if(strncmp(str2,proof[i],strlen(str2))==0)
        return 1;
        else 
        return 0;;
    }

    //OR Introduction 2
    else if(rule[i][0]=='+'&&rule[i][1]=='i' && rule[i][2]=='2' && rule[i][3]=='/' && (rule[i][4]-49<i)){
        char str2[LIMIT] = {'\0'};
        int pos=strlen(proof[rule[i][4]-49]);
        int control=1;
        for (int j = strlen(proof[i]), k=strlen(proof[rule[i][4]-49]); k<pos ; j--,k--)
        {
            if(proof[i][j-2]!=proof[rule[i][4]-49][k])
            control=0;
        }
        return control;
    }

    //Implication Elimination
    else if(rule[i][0]=='>'&&rule[i][1]=='e' && rule[i][2]=='/' && rule[i][4]=='/' && (rule[i][3]-49<i) && (rule[i][5]-49<i)){
        int control=1,count=0;
        for (int j = 0; j <strlen(proof[rule[i][5]-49]) ; j++){
        {
            if(proof[rule[i][5]-49][j]!=proof[rule[i][3]-49][j+1]){
            control=0;
            }
        }
        for (int j = strlen(proof[rule[i][3]-49]),k=strlen(proof[i]); k >0 ; j--,k--)
        {
            if(proof[i][k-1]!=proof[rule[i][3]-49][j-2]){
            control=0;
            }
        }
        }
        return control;
    }

    //Modus Tollens
    else if(rule[i][0]=='M'&&rule[i][1]=='T' && rule[i][2]=='/' && rule[i][4]=='/' && (rule[i][3]-49<i) && (rule[i][5]-49<i) && (proof[rule[i][5]-49][0]=='~') ){  
        int control=1;
        for (int j = strlen(proof[rule[i][5]-49]),k=strlen(proof[rule[i][3]-49]); j > 1; j--,k--)
        {
            if(proof[rule[i][5]-49][j-1] != proof[rule[i][3]-49][k-2]){
                control=0;
            }
        }
        for (int j = 0; j < strlen(proof[i]); j++)
        {
            if(j==0){
                if(proof[i][j] != '~'){
                control=0;
            }
        }
        else if(proof[i][j] !=proof[rule[i][3]-49][j]){
        control=0;
        }
        }
      return control;
    }
    
    else
    return 0;
}


int main(){

    int n,t;
    cin>>n;

    char proof[n][LIMIT],rule[n][LIMIT];
    int control=1;
    if(n!=0){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0;  ; j++)
        {
            cin>>proof[i][j];
            if(proof[i][j]=='/'){
            proof[i][j]='\0';
            break;
            }
        }
        for (int j = 0; ; j++)
        {
            cin>>rule[i][j];
            if(std::cin.peek() == '\n'){
            rule[i][j+1]='\0';
            break;
            }
        }
        if ((Validity(proof,rule,i)==1) && (rule[i][0]!='\0'))
        continue;
        else{
            control= 0;
            }
        }
    }
    else
    control=0;

    if(control)
    cout<<"Valid"<<endl;
    else{
    cout<<"Invalid"<<endl;}
    return 0;
}