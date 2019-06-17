//AC C_AR025
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;
int main()
{
    int book[201] = {0};
    char line[101] = "";
    char tmp;
    cin.getline(line,101);
    int i;
    for(i = 0;i < strlen(line); i++){
        tmp = line[i];
        book[int(tmp)]++;
    }
    for(int j = 200; j > 0; j--)
        if(book[j] != 0)
        cout<<j<<" "<<book[j]<<"\n";
}

