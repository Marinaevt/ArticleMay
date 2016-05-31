#pragma once

#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;


class CPoint {
	
public:
	CPoint(){
		P=0;	S0=0;
		S=0;	H=0;
		t=0;	R0=0;
		Rho0 = 0;
	}

	double P;
	double S0;
	double S;
	double H;
	double t;
	double R0;
	double Rho0;
};
