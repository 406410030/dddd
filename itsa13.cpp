//AC C_MM02
#include<stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    float w,h;
    cin>>w>>h;
    cout << fixed<<showpoint;
	cout <<setprecision(1)<<((w*h)/2)+0.01<<"\n";
	return 0;
}


