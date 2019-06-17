//AC C_MM25
#include<stdio.h>
#include<string.h>
#include <iostream>
using namespace std;
int main()
{
    char in[10];
    int n;
    while(cin.getline(in,9)){
    n = atoi(in);
    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(i%3 == 0)ans += i;
        cout<<ans<<"\n";
    }
    return 0;
}

