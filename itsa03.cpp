//AC C_AR03
#include<stdio.h>
#include <iostream>
#include<vector>
using namespace std;
int main()
{
    int a[6], i;
    long long int ans = 0;
    for(i = 0;i < 6; i++)
        cin>>a[i];
    for(i = 0; i < 6; i++)
        ans += a[i]*(a[i]*a[i]);
    cout<<ans<<"\n";
}
