#pragma once

#include <math.h>
#include <iostream>
#include <algorithm>    // std::max
#include "ConstEquation.h"

using namespace std;

const double step = 0.001;

#define CRUTCH 0



class CFunction{
public:
	virtual double GetDF(double, double) = 0;
#if CRUTCH
	virtual double GetCurrentH() { return 0; };
#endif
public:
	double m_dH_dt;
};

double Euler(double t0, double H0, double t, CFunction *F, double dt = step, double dMaxdF = 0.5);

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
class CDomeThickness : public CFunction{
public:
	CDomeThickness(double R0, double Rho0, double A, double s0):m_dA(A), m_dR0(R0), m_dRho0(Rho0), m_ds0(s0) {}
	virtual double GetDF(double H, double s){
		return -(s+(2*m_dA-1)*m_ds0)/(GetRho(H)+m_dRho0);
		//return -(s+(2*m_dA-1)*m_ds0)/(GetRho(H));
	}

	virtual double GetF(double H){
		return m_ds0-m_dA*m_ds0*H/(GetRho(H)+m_dRho0);
		//return m_ds0-m_dA*m_ds0*H/(GetRho(H));
	}

	void Init(double R0, double Rho0, double s0, double s1 , double H1){
		m_dR0 = R0; m_dRho0 = Rho0; m_ds0 = s0;
		CalcA(H1, s1);
	}

	double CalcA(double H, double s){
		return m_dA = ((1-s)/m_ds0)*(GetRho(H)+m_dRho0)/H;
		//return m_dA = (1-s/m_ds0)*(GetRho(H))/H;
	}

	double GetRho(double H){
		return 0.5*((m_dR0+m_dRho0)*(m_dR0+m_dRho0) + H*H)/H - m_dRho0;
	}

public:
	double m_dA;
	double m_dRho0;
	double m_dR0;
	double m_ds0;
};
//////////////////////////////////////////////////////////////////////////////////////////

class CDomeHeight : public CFunction{
public:
	CDomeHeight(CConstEquation *inF, double R0=50., double Rho0=5, double A=0.5, double s0=1):m_S(R0, Rho0, A, s0){
		InvF=inF;
		m_dCurrentS = 1;
		m_dCurrentH = 2;
	}

	virtual double GetDF(double t, double H){
	//virtual double GetDF(double t, double H, CConstEquation *InF){
		if(H>=m_S.m_dR0+m_S.m_dRho0) return 0.5; // при больших высотах производная стремится к бесконечности, чтобы это ограничить ставим костыль
		
		if(H > m_dCurrentH){
			//m_dCurrentS = Euler(m_dCurrentH, m_dCurrentS, H, &m_S);
			m_dCurrentS = m_S.GetF(H);
			m_dCurrentH = H;
		}
		double dRho = m_S.GetRho(H);
		//double dHdT = min(10000000., -m_dCurrentS/m_S.GetDF(H,m_dCurrentS)*pow(m_dP*dRho/2/m_dK/m_dCurrentS, 1/m_dm));
		double dHdT = min(10000000., -m_dCurrentS/m_S.GetDF(H,m_dCurrentS)*InvF->Inverse_F(m_dP, m_dCurrentS, dRho, m_S.m_ds0));
		return dHdT;
	}
#if CRUTCH
	virtual double GetCurrentH() {
		return m_dCurrentH;
	}
#endif
public:
	double m_dCurrentS;
	double m_dCurrentH;
	double m_dP;
	CDomeThickness m_S;
	CConstEquation *InvF;

};
/////////////////////////////////////////////////////////////////////////////////
double Euler(double x0, double F0, double x, CFunction *F, double dx, double dMaxdF){

	/*&*/ofstream fout("out_P3.txt", ios::app);  // для АМг - 6
	//ofstream fout("out_P3.5.txt", ios::app);
	//ofstream fout("out_P4.txt", ios::app);
	//ofstream fout("out_P5.txt", ios::app);
	//ofstream fout("out_P6.txt", ios::app);

	//ofstream fout("out __OT_P3.txt", ios::app);  // для ОТ - 4
	//ofstream fout("out __OT_P8.txt", ios::app);
	//ofstream fout("out __OT_P12.txt", ios::app);
	//ofstream fout("out __OT_P16.txt", ios::app);

	double dx0 = dx;
	while(x0+dx<=x){
		double dF = F->GetDF(x0, F0);
		if(dF*dx0>dMaxdF){
			dx = dMaxdF/dF;
		}else{
			dx = dx0;
		}
		F0 += dF*dx;
		/*&*/fout << x0 << '\t' << F0 << '\t' << dF << endl;
		x0+=dx;
	}
	double dF = F->GetDF(x, F0);
	F0 += (x-x0)*dF;
	/*&*/fout << x0 << '\t' << F0 << '\t' << dF << endl;
	/*&*/fout.close();

	return F0;
}

/////////////////////////////////////////////////////////////////////////////////
double Euler1(double x0, double F0, double x1,  double F1, CFunction *F, double dx, double dMaxdF){

	/*&*/ofstream fout("out_P3.txt", ios::app);  // для АМг - 6
	//ofstream fout("out_P3.5.txt", ios::app);
	//ofstream fout("out_P4.txt", ios::app);
	//ofstream fout("out_P5.txt", ios::app);
	//ofstream fout("out_P6.txt", ios::app);

	//ofstream fout("out __OT_P3.txt", ios::app);  // для ОТ - 4
	//ofstream fout("out __OT_P8.txt", ios::app);
	//ofstream fout("out __OT_P12.txt", ios::app);
	//ofstream fout("out __OT_P16.txt", ios::app);

	double dx0 = dx;
	double dErr = (F0-F1)*(F0-F1)/F0/F0 + (x0-x1)*(x0-x1)/x0/x0, ddErr=-1;
	double dErrMin = dErr;
	bool bLeft=true;
	while(x0<x1 || ddErr<0){
		dx = dx0;
		if(x0>=x1 && bLeft){
			dx = x1-x0;
			bLeft = false;
		}
		double dF = F->GetDF(x0, F0);
		if(dF*dx0>dMaxdF){
			dx = dMaxdF/dF;
			dF = F->GetDF(x0, F0);
		}
		F0 += dF*dx;
		/*&*/fout << x0 << '\t' << F0 << '\t' << dF << endl;
		x0+=dx;
		double dErr0 = dErr;
		dErr = (F0-F1)*(F0-F1)/F0/F0 + (x0-x1)*(x0-x1)/x0/x0;
		ddErr = dErr-dErr0;
		if(dErr<dErrMin) dErrMin=dErr;
	}


	return dErrMin;
}

/////////////////////////////////////////////////////////////////////////////////
#if CRUTCH
	double Runge1(double x0, double F0, double x1,  double F1, CFunction *F, double dx, double dMaxdF, double maxH){
#else
	double Runge1(double x0, double F0, double x1, double F1, CFunction *F, double dx, double dMaxdF){
#endif

	/*&*/ofstream fout("out_P3.txt", ios::app);  // для АМг - 6
	//ofstream fout("out_P3.5.txt", ios::app);
	//ofstream fout("out_P4.txt", ios::app);
	//ofstream fout("out_P5.txt", ios::app);
	//ofstream fout("out_P6.txt", ios::app);

	//ofstream fout("out __OT_P3.txt", ios::app);  // для ОТ - 4
	//ofstream fout("out __OT_P8.txt", ios::app);
	//ofstream fout("out __OT_P12.txt", ios::app);
	//ofstream fout("out __OT_P16.txt", ios::app);

	double dx0 = dx;
	double dErr = (F0-F1)*(F0-F1)/F1/F1 + (x0-x1)*(x0-x1)/x1/x1, ddErr=-1;
	double dErrMin = dErr;
	bool bLeft1=true;
#if CRUTCH
	bool flag = 1;
#endif
	int nLeft=0;
#if CRUTCH
	double Hk = F->GetCurrentH();
	while ((x0 + 2 * dx0<x1 || ddErr<0) && (dx0>0) && flag) {
#else
	while ((x0 + 2 * dx0<x1 || ddErr<0) && dx0>0) {
#endif
		dx = dx0;
		if(x0+dx>=x1 && bLeft1){
			dx = x1-x0;
			bLeft1 = false;
		}
		double k1 = F->GetDF(x0, F0);
		if(k1*dx>dMaxdF){
			dx = dMaxdF/k1;
		}
		double k2 = F->GetDF(x0+dx*0.5,F0+dx*k1*0.5);
		double k3 = F->GetDF(x0+dx*0.5,F0+dx*k2*0.5);
		double k4 = F->GetDF(x0+dx,F0+dx*k3);
		double dF = dx*(k1+2*k2+2*k3+k4)/6;
		//ищем dErr
		double dErr0 = dErr;
		if(dx>0){
			double L = sqrt(dF*dF/F1/F1 + dx*dx/x1/x1);
			double e1 = dx/x1/L;
			double e2 = dF/F1/L;
			double u = e1*(x1-x0)/x1 + e2*(F1-F0)/F1;
			u = max(0., min(L,u));
			double u1 = e1*u;
			double u2 = e2*u;
			double d1 = (x1-x0)/x1 - u1;
			double d2 = (F1-F0)/F1 - u2;
			dErr = d1*d1+d2*d2;
		}
		F0 += dF;
		x0+=dx;

		ddErr = dErr-dErr0;
		if(dErr<dErrMin) dErrMin=dErr;
		/*&*/fout << x0 << '\t' << F0 << '\t' << dErr << endl;
		if(nLeft<7 && x0+2*dx>=x1 && ddErr<0){
			nLeft++;
			dx0*=0.5;
		}
#if CRUTCH
		if ((Hk != F->GetCurrentH() || (Hk < maxH)) && (dErr < pow(10, 28))) {
			Hk = F->GetCurrentH();
		}
		else {
			flag = 0;
		}
#endif
	}
	return dErrMin;
}