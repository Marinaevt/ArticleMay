#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include "Optimizer.h"

using namespace std;
const double COptimizer:: alpha = 1;
const double COptimizer::beta = 0.5;
const double COptimizer::gamma = 2;
const double COptimizer::dx = 0.02;


COptimizer::COptimizer(int nMaxStep){
	m_nCondition = -1;
	m_nStep = 0;
	m_nMaxStep = nMaxStep;
	m_Fr = 0;
	m_nReduced = -1;
}

COptimizer::~COptimizer(){
}

/////////////////////////
bool COptimizer::NextStep(vector<double> &x, double &F){

	if(m_nCondition == 3){ // x = Xs, F = Fs
		if(F < GetFh()){
			Reflect(x, F);//Отразить многогранник, m_nCondition -> 0
		}else{
			m_nCondition = -2; //глобальное сжатие
		}
	}

	if(m_nCondition == 2){ // x = Xe, F = Fe
		if(F < GetFl()){
			Reflect(x, F);		//Отразить многогранник, m_nCondition -> 0
		}else{
			Reflect(m_Xr, m_Fr);//Отразить многогранник, m_nCondition -> 0
		}
	}

	if(m_nCondition == 1){  // x = Xr, F = Fr
		m_Xr = x;
		m_Fr = F;
		if(F<GetFl()){
			CalcXe(x);       // Теперь x - это Xe
			m_nCondition = 2;
		}else if(F<GetFg()){
					Reflect(x, F);		//Отразить многогранник, m_nCondition -> 0
				}else{
					if(F<GetFh()){
						Reflect(x, F);   // Меняем Xh на X(Xr) и Fh на F(Fr)
					}
					CalcXs(x);
					m_nCondition = 3;
		}
	}

	if(m_nCondition == -1){ // Многогранник не сформирован
		CreateSimplex(x, F);
	}

	if(m_nCondition == -2){ // Многогранник необходимо редуцировать
		Reduce(x, F); // Редуцируем
	}

	if(m_nCondition == 0){  // Многогранник сформирован
		CalculateNextX();	//Отсортировать многогранник и найти отраженную точку (m_Xr), m_nCondition -> 1
		x = m_Xr;
	}

	if(m_nStep >= m_nMaxStep) return true;
	m_nStep++; 
	return false;
}

void COptimizer::CreateSimplex(vector<double> &x, double &F){
	
	m_Simplex.push_back(x);
	int n = m_Simplex.size();
	m_Simplex[n-1].push_back(F);
	
	if (n-1 < x.size()){
		copy(m_Simplex[0].begin(), m_Simplex[0].end()-1, x.begin());
		x[n-1]*= dx+1;
	}else{
		m_nCondition = 0;
	}
}

///////////////////////////////////////////////////////

void COptimizer::Out_simplex(){
	cout << "m_nStep = " << m_nStep << ", m_nCondition = " << m_nCondition << endl;
	for (int i=0; i<m_Simplex.size(); i++){
		for (int j=0; j<m_Simplex[i].size(); j++){
			cout<< setprecision(6) << m_Simplex[i][j] << "\t";
		}
		cout << " | " << (i==I_h ? "I_h" : ( i==I_g ? "I_g" : (i==I_l ? "I_l" : "   "))) << endl;
	}
	cout <<'\n' << endl;
}

//////////////////////////////////////////////////////
// Сортирует многогранник, находит центр тяхести и считает отраженную точку.
void COptimizer::CalculateNextX(){
	
	int n = m_Simplex.size()-1;			//"сорт."
	I_h = I_l = 0;
	I_g = 1;
	for (int i = 1; i<m_Simplex.size(); i++){
		if (m_Simplex[I_h][n] < m_Simplex[i][n]){   //max
			if(m_Simplex[I_g][n]  < m_Simplex[I_h][n] || I_g == i) I_g = I_h;
			I_h = i;  
		}
		if (m_Simplex[I_l][n] > m_Simplex[i][n]) I_l = i;  //min
		if (m_Simplex[I_g][n] < m_Simplex[i][n] && I_h != i) I_g = i;  //max -1
	}

	m_Xc.assign(n,0);   // центр тяж.
	for(int j=0; j<n; j++){
		for (int i = 0; i<n+1; i++){
			if(i != I_h) m_Xc[j] += m_Simplex[i][j];
		}
		m_Xc[j] /= n;
	}
	// << "  m_Xc:  "; print(m_Xc);

	m_Xr.assign(n,0);  	//отраж. точка
	for (int i = 0; i<n; i++){
		m_Xr[i] = m_Xc[i]*(1 + alpha) - alpha * m_Simplex[I_h][i];
	}
	//cout << "  m_Xr:  "; print(m_Xr);
	m_nCondition = 1;
}

///////////////////////////////////////////
void COptimizer::CalcXe(vector<double> &x) {
	for (int i = 0; i<x.size(); i++){
		x[i] = m_Xc[i]*(1 - gamma) + gamma * m_Xr[i];
	}
	//cout << "  Xe:  "; print(x);
}

/////////////////////////////////////////////////
void COptimizer::CalcXs(vector<double> &x) {
	for (int i = 0; i<x.size(); i++){
		x[i] = m_Xc[i]*(1 - beta) + beta * m_Simplex[I_h][i];
	}
	//cout << "  Xs:  "; print(x);
}


////////////////////////////////////////////////////////
void COptimizer::Reflect(vector<double> &x, double &F){
	
	m_Simplex[I_h] = x;
	m_Simplex[I_h].push_back(F);
	m_nCondition = 0;
}

////////////////////////////////////////////////////////
void COptimizer::Reduce(vector<double> &x, double F){
	if(m_nReduced != -1) m_Simplex[m_nReduced][m_Simplex.size()-1] = F;
	if(++m_nReduced == I_l)m_nReduced++;
	if(m_nReduced >= m_Simplex.size()){
		m_nReduced = -1;
		m_nCondition = 0;
		//m_nStep = m_nMaxStep;
		return;
	}

	for(int i = 0; i < m_Simplex.size()-1; i++){
		x[i] = m_Simplex[m_nReduced][i] = m_Simplex[I_l][i] + 0.5*(m_Simplex[m_nReduced][i] - m_Simplex[I_l][i]);
	}
	//cout << " Reduced X:  "; print(x);
}

