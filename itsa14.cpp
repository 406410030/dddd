//AC C_MM03
#include<stdio.h>
#include<string.h>
#include <iostream>
using namespace std;
int main()
{
    char line[100];
    char *toker;
    char *cut = " ";
    long long int a,b;
    while(cin.getline(line,99)){
        int i = 0;
    toker = strtok(line,cut);
    while(toker != NULL){
    i++;
    if(i == 1)
        a = atoi(toker);
    if(i == 2)
        b = atoi(toker);
        toker = strtok(NULL,cut);
    }
    cout<<a+b<<"\n";
    }
    return 0;
}
