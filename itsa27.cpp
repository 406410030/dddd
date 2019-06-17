//AC C_MM10
#include<stdio.h>
#include<string.h>
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    char in[10];
    float n;
    while(cin.getline(in,9)){
    n = atof(in);
    cout << fixed<<showpoint;
	cout <<setprecision(1)<<(n*9)/5+32+0.01<<"\n";
    }
    return 0;
}
