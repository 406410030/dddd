//AC C_MM09
#include<stdio.h>
#include<string.h>
#include <iostream>
#include<vector>
using namespace std;
int main()
{
    char in[10];
    int n;
    while(cin.getline(in,9)){
    unsigned long long int a = 1;
    n = atoi(in);
    if(n > 31)
        cout<<"Value of more than 31\n";
    else{
    while(n--)
        a = a<<1;
        cout<<a<<"\n";
    }
    }

    return 0;
}

