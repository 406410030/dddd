//AC C_MM27
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
    if(a > b)
        a ^= b ^= a ^= b;
    int ans = 0;
    for(i = a;i <= b; i++)
        ans += i;
        cout<<ans<<"\n";
    }
    return 0;
}


