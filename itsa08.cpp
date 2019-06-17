//AC C_AR022
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
#include<vector>
using namespace std;
int main()
{
    int book[26] = {0};
    char line[1001];
    char tmp;
    cin.getline(line,1000);
    int i;
    for(i = 0;i < strlen(line); i++){
        if(line[i] >= 'A' && line[i] <= 'Z')
            book[line[i] - 'A']++;
        if(line[i] >= 'a' && line[i] <= 'z')
            book[line[i] - 'a']++;
    }
    for(i = 0; i < 25; i++)
    cout<<book[i]<<" ";
    cout<<book[i]<<"\n";
}

