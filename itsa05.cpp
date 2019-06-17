//AC C_AR48
#include<stdio.h>
#include <iostream>
#include<vector>
using namespace std;
int main()
{
    char tmp[5] = "";
    char newt[5] = "";
    int cha;
    cin.getline(tmp,5);
    int i;
    for(i = 0; i < 4; i++){
        cha = tmp[i] - '0';
        cha+=7;
        cha%=10;
        if(i == 0)
        newt[2] = cha + '0';
        if(i == 1)
        newt[3] = cha + '0';
        if(i == 2)
        newt[0] = cha + '0';
        if(i == 3)
        newt[1] = cha + '0';
    }
    cout<<newt<<"\n";
    return 0;
}
