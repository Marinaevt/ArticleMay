#pragma once
#include <iostream>
#include <vector>

using namespace std;

class COptimizer{
	
	friend void print(vector<double> &);

public:
	COptimizer(int nMaxStep);
	bool NextStep(vector<double> &, double &);
	void CreateSimplex (vector<double> &, double &);
	~COptimizer();
	void Reflect(vector<double> &, double &);
	void Reduce(vector<double> &x, double F);
	void CalculateNextX();
	void Out_simplex();
	
	double GetFl(){return m_Simplex[I_l][m_Simplex[I_l].size()-1];}
	double GetFg(){return m_Simplex[I_g][m_Simplex[I_g].size()-1];}
	double GetFh(){return m_Simplex[I_h][m_Simplex[I_h].size()-1];}

	void CalcXe(vector<double> &x);
	void CalcXs(vector<double> &x);

	int m_nStep;
	
private:

	int m_nCondition;
	int m_nReduced;
	vector<vector<double>> m_Simplex;
	const static double alpha, beta, gamma, dx;
	int m_nMaxStep;
	//int m_nStep;
	int I_h, I_g, I_l;
	vector <double> m_Xr;
	double m_Fr;
	vector <double> m_Xc;
	vector <double> m_Xe;
	vector <double> m_Xs;
	
};

