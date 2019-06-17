//AC C_MM15
#include<stdio.h>  
#include<string.h>  
#include <iostream>  
using namespace std;  
int main()  
{  
    char line[100];  
    char *toker;  
    char *cut = " ";  
    int x,y;  
    while(cin.getline(line,99)){  
        int i = 0;  
    toker = strtok(line,cut);  
    while(toker != NULL){  
    i++;  
    if(i == 1)  
        x = atoi(toker);  
    if(i == 2)  
        y = atoi(toker);  
        toker = strtok(NULL,cut);  
    }
	if(x <= 100 && y <= 100)
    		cout<<"inside\n";
	else
		cout<<"outside\n";  
    }
    return 0;  
}  