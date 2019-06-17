//AC C_MM01
#include<stdio.h>
#include<string.h>
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    char line[100];
    char *toker;
    char *cut = " ";
    float upper, lower, h;
    while(cin.getline(line,99)){
        int i = 0;
    toker = strtok(line,cut);
    while(toker != NULL){
    i++;
    if(i == 1)
        upper = atof(toker);
    if(i == 2)
        lower = atof(toker);
    if(i == 3)
        h = atof(toker);
        toker = strtok(NULL,cut);
    }
	cout << fixed<<showpoint;
	cout <<"Trapezoid area:"<<setprecision(1)<< (((upper+lower)*h)/2)+0.01<<"\n";
    }
    return 0;
}
