//AC C_MM39
#include<stdio.h>
#include<string.h>
#include <iostream>
using namespace std;
int main()
{
    char line[100];
    char *toker;
    char *cut = " ";
    int a,b,c;
    int in1 = 0,in2 = 0,in3 = 0;
    while(cin.getline(line,99)){
    int i = 0;
    toker = strtok(line,cut);
    while(toker != NULL){
    i++;
    if(i == 1)
        in1 = atoi(toker);
    if(i == 2)
        in2 = atoi(toker);
    if(i == 3)
        in3 = atoi(toker);
    toker = strtok(NULL,cut);
    }
    if(in1>in2&&in1>in3){
        c = in1;
        a = in2, b = in3;
    }
    else if(in2>in1&&in2>in3){
        c = in2;
        a = in1, b = in3;
    }
    else{
        c = in3;
        a = in2, b = in1;
    }
    if(a+b == c)
        cout<<"Not Triangle\n";
    else{
        if((a*a)+(b*b) == c*c)
            cout<<"Right Triangle\n";
        else if((a*a)+(b*b) < c*c)
            cout<<"Obtuse Triangle\n";
        else
            cout<<"Acute Triangle\n";
    }
    }
    return 0;
}
