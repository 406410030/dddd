//AC C_AR02
#include<stdio.h>
#include<string.h>
#include <iostream>
#include<vector>
using namespace std;
class A{
public:
    char num[30];
};
int main()
{
    A lis;
    vector<A> a;
    char tmp[100] = "";
    char *cut = " ";
    cin.getline(tmp,100);
    char *toker;
    int i = 0;
    toker = strtok(tmp,cut);
    while(toker != NULL){
    i++;
    strcpy(lis.num,toker);
    a.push_back(lis);
    toker = strtok(NULL,cut);
    }
    i--;
    for(;i > 0;i--)
        cout<<a[i].num<<" ";
    cout<<a[0].num<<"\n";
	return 0;
}

