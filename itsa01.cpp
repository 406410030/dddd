//AC C_AR021
#include<stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	int student;
	float chinese, english, math, average = 0.0;
	float totalc = 0.0, totale = 0.0, totalm = 0.0;
	cin>>student;
	for(int i = 0; i < student; i++){
		cin>>chinese>>english>>math;
		totalc += chinese;
		totale += english;
		totalm += math;
		average = (totalc+totale)+totalm;
	}
	if(totalc != 0)
	totalc /= student;
	if(totale != 0)
	totale /= student;
	if(totalm != 0)
	totalm /= student;
	if(average != 0)
	average /= (3*student);
	cout << fixed<<showpoint;
	cout <<setprecision(1)<< average+0.01 <<" ";
	cout <<setprecision(1)<< totalc+0.01 <<" ";
	cout <<setprecision(1)<< totale+0.01 <<" ";
	cout <<setprecision(1)<< totalm+0.01 << "\n";
	return 0;
}
