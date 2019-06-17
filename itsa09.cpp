//AC C_AR50
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include<vector>
#include<queue>
using namespace std;
int main()
{
    int start, i, t, book[100000] = {0};
    priority_queue<int,vector<int>,greater<int>> mem;
    vector<int> lis;
    cin>>start;
    lis.push_back(1);
    for(i = 0; i < 1000; i++){
        t = lis[i];
        lis.push_back((2*t)+1);
        lis.push_back((3*t)+1);
    }
    for(i = 0; i < lis.size(); i++){
        book[lis[i]] = 1;
    }
    for(i = 0; i < 100000; i++)
        if(book[i])
        mem.push(i);
    int counter = 0;
    while(!mem.empty()){
        if(counter == start)break;
        counter++;
        i = mem.top();
        cout<<i<<"\n";
        mem.pop();
    }
    return 0;
}


