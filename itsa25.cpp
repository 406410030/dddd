//AC C_MM07
#include<stdio.h>
#include<string.h>
#include <iostream>
using namespace std;
int main()
{
    char in[10];
    int a;
    while(cin.getline(in,9)){
        a = atoi(in);
    cout<<a<<" "<<a*a<<" "<<a*(a*a)<<"\n";
    }
    return 0;
}

