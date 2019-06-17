//AC C_MM16
#include<stdio.h>  
#include<string.h>
#include<math.h>
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
	if(sqrt((x*x)+(y*y)) <= 100)
    		cout<<"inside\n";
	else
		cout<<"outside\n";  
    }
    return 0;  
}  