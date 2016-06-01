// Optimizer.cpp: определяет точку входа для консольного приложения.
//


#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include "Point.h"
#include "Read.h"
#include "Function.h"
#include "Optimizer.h"
#include "ConstEquation.h"
using namespace std;

double f(vector<CPoint> &, CDomeHeight &, double A);
void print(vector<double> &);

	// вывод данных в текстовые файлы
	//ofstream fout("out_F.txt");
	//ofstream fout("out_P3.txt");   // для АМг - 6
	//ofstream fout("out_P3.5.txt");
	//ofstream fout("out_P4.txt");
	//ofstream fout("out_P5.txt");
	//ofstream fout("out_P6.txt");
	//ofstream fout("out_AMg6.txt");

	//ofstream fout("out __OT_P3.txt");  // для ОТ - 4
	//ofstream fout("out __OT_P8.txt");
	//ofstream fout("out __OT_P12.txt");
	//ofstream fout("out __OT_P16.txt");
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

CConstEquation *InitBackofen(vector<double> &x){
	/////// Backofen //////////////////////////////////
	CConstEquation *eq = new CBackofen();
	//x.push_back(log(128.209));		//K=155.7, m=0.265 AMg6
	//x.push_back(log(0.458));		//K=1746.24, m=0.496986 OT4 
	x.push_back(log(50));
	x.push_back(log(0.05));
	if(!eq->Init(x)){
		delete eq;
		eq = 0;
	}
	return eq;
}

CConstEquation *InitBackofenEx(vector<double> &x){
	/////// Backofen //////////////////////////////////
	CConstEquation *eq = new CBackofenEx();
	x.push_back(log(0.000001));		//K=155.7, m=0.275 AMg6
	x.push_back(log(165));		//K=155.7, m=0.275 AMg6
	x.push_back(log(0.01));		//K=1746.24, m=0.496986 OT4 
	x.push_back(log(0.272));		//K=1746.24, m=0.496986 OT4 
	if(!eq->Init(x)){
		delete eq;
		eq = 0;
	}
	return eq;
}

CConstEquation *InitSmirnov(vector<double> &x){
	/////// Backofen //////////////////////////////////
	CConstEquation *eq = new CSmirnov();
	x.push_back(log(2.864));		//s0
	x.push_back(log(25.476));		//s1
	x.push_back(log(3054.04));		//Kv
	x.push_back(log(0.996));		//mv

	if(!eq->Init(x)){
		delete eq;
		eq = 0;
	}
	return eq;
}


int main(){
	vector<CPoint> data;        // считывание данных из текстового файла
	if (ReadFile (data)){
		cout << "File opened" <<'\n' << endl;
		//Out_points(data);
	}else{
		cout << "File not found" <<'\n'<< endl;
		return 1;
	}

	vector<double> x;
	CConstEquation *equation = InitBackofen(x);
	//CConstEquation *equation = InitBackofenEx(x);
	//CConstEquation *equation = InitSmirnov(x);

	if(!equation) return 1;

	CDomeHeight H(equation);
	COptimizer opt(100000);		// оптимизация: м.деформ. многогранника
	double F;					//

	
/*////////// AMg_6, OT4- Smirnov //////////////////////////////
	x.push_back(log(20));   //Sig0 = 12.07;  8.990106935		
	x.push_back(log(200));   //SigS = 45.74;  47.94650399
	x.push_back(2000);	  //K = 18196;  4185.699174
	x.push_back(0.9);   //M = 0.929;   0.690254601	
/////////// OT_4, Smirnov /////////////////////////////
	x.push_back(log(20));   //Sig0 = 2.9176
	x.push_back(log(200));   //SigS = 163.744
	x.push_back(20000);	  //K = 14059.9
	x.push_back(0.5);   //M = 0.7412
*/
	//x.push_back(log(0.5));
	//x.push_back(log(0.7739));
	F = f(data, H, exp(x[x.size()-1]));
		//cout << "  x:  "; print(x);
		//cout << " F= "<< F <<'\n';

	/*&*/ 	
	//ofstream foutK("mapkM.csv", ios_base::out | ios_base::trunc);
	ofstream foutF("mapF.csv", ios_base::out | ios_base::trunc);
	//foutK << exp(x.at(0)) << "," << exp(x.at(1)) << endl;
	foutF << F;
	cout << exp(x.at(0)) << "," << exp(x.at(1)) << "," << F <<endl;
	double dm = 0.1, dk = 100;
	for (double i = dm; i <= 0.9; i += dm/10) {
		for (double j = dk; j <= 1000; j += dk/10) {
			x[0] = log(j);
			x[1] = log(i);
			equation->Init(x);
			F = f(data, H, exp(x[x.size() - 1]));
			//foutK << j << "," << i << endl;
			foutF << "," << F;
			cout << j << "," << i << "," << F << endl;
		}
		foutF << endl;
	}
	//foutK.close();
	foutF.close();
	/*
	while (!opt.NextStep(x, F)){
		equation->Init(x);
		F = f(data, H, exp(x[x.size()-1]));
		//ofstream fout("out_F.txt", ios::app);
		//fout << opt.m_nStep<< "   " << F << '\n';
		//opt.Out_simplex();
		cout << "  x:  "; print (x);
		cout << setprecision(10) << " F= "<< F <<'\n';
	}//
//	fout.close();
*/
	delete equation;
	return 0;
}


/////////////////////////
double f(vector<CPoint> &data, CDomeHeight &H, double A){

	double val = 0;

	/*&*/ofstream fout("out_P3.txt");  // для АМг - 6
	/*&*/fout.close();

	for(int i=0; i<data.size();i++){
		H.m_dP = data[i].P;
		H.m_S.Init(data[i].R0, data[i].Rho0, data[i].S0, data[i].S, data[i].H);
		//H.m_S.m_dA = A;

		H.m_dCurrentS = data[i].S0;
		H.m_dCurrentH = data[i].S0;//data[i].S0;

		//*&*/ofstream fout("out_P3.txt", ios::app);  // для АМг - 6
		//*&*/fout << "\t\t\t" << data[i].P << "\t" << data[i].t << "\t" << data[i].H << endl;
		//*&*/fout.close();
		
		//double dHErr = Euler(0, data[i].S0, data[i].t, &H, 0.5, 0.5);
		//double dHErr = (data[i].H - ddH)/data[i].H;
		//double dHErr = Euler1(0, data[i].S0, data[i].t, data[i].H, &H, data[i].t*0.001, data[i].H*0.01);
#if CRUTCH
		double dHErr = Runge1(0, data[i].S0, data[i].t, data[i].H, &H, data[i].t*0.01, data[i].H*0.1, data[i].H + data[i].Rho0);
#else
		double dHErr = Runge1(0, data[i].S0, data[i].t, data[i].H, &H, data[i].t*0.01, data[i].H*0.1);
#endif
		//double dHErr = Euler1(0, data[i].S0, data[i].t, data[i].H, &H, 0.5, 0.5);
		double dS = (data[i].S - H.m_dCurrentS)/data[i].S;
		//val+= dHErr+dS*dS;
		//val+= sqrt(dHErr);
		val+= pow(dHErr,0.5);
		//val+= abs(dH);
	}	
 	return val;
};


//////////////////////////////
void print(vector<double> &x){
	//cout.precision(6);
	for (int i=0; i< x.size(); i++){
		cout << exp(x[i]) << "  ";
	}
	cout << endl;
} 

