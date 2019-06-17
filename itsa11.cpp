//AC C_AR20
#include<stdio.h>
#include <iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int> a(130);
    int input, i, tmp, ans = 1;
    cin>>input;
    for(i = 1; i < 129; i++)
        a[i] = 0;
    for(i = 0; i < input; i++){
        cin>>tmp;
        a[tmp]++;
    }
    for(i = 1; i < 129; i++)
        if(a[i] > 1){
            ans = 0;
            break;
        }
    cout<<ans<<"\n";
}
