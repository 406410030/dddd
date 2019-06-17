//AC C_MM21
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
    for(int i = 1; i <= n; i++)
        a *= i;
        cout<<a<<"\n";
    }
    return 0;
}


