#pragma once
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>    // std::max
using namespace std;

class CConstEquation{
public:
	virtual bool Init(vector<double> &x)=0;
	virtual double Inverse_F(double P, double S, double Rho, double S0) =0;
	virtual ~CConstEquation(){};
public:
	

};

//////////////////////////////////////////////////////////////
class CBackofen: public CConstEquation{
public:
	virtual bool Init(vector<double> &x){
		if (x.size()>=2){
			m_dK=exp(x.at(0));	m_dm=exp(x.at(1));
			return true;
		}
	};

	virtual double Inverse_F(double P, double S, double Rho, double S0){
		return pow(P*Rho/2/m_dK/S, 1/m_dm);
	}
public:
	double m_dK;
	double m_dm;

};

//////////////////////////////////////////////////////////////
class CBackofenEx: public CConstEquation{
public:
	virtual bool Init(vector<double> &x){
		if (x.size()>=3){
			int i=0;
			//m_dSg0 = 0;
			m_dSg0=exp(x.at(i++));	
			m_dK=exp(x.at(i++));
			m_dn=exp(x.at(i++));	
			m_dm=exp(x.at(i++));
			return true;
		}
	};

	virtual double Inverse_F(double P, double S, double Rho, double S0){
		return pow((P*Rho/2/S-m_dSg0)/(m_dK*pow(log(S0/S), m_dn)), 1/m_dm);
	}
public:
	double m_dSg0;
	double m_dK;
	double m_dn;
	double m_dm;
};


////////////////////////////////////////////////////////////
class CSmirnov: public CConstEquation{
public:
	CSmirnov()  {m_dDelta = 1E-13;}

	virtual bool Init(vector<double> &x){
		if (x.size()>=4){
			m_dSig0=exp(x.at(0));	m_dSigS=exp(x.at(1));
			m_dK = exp(x.at(2));	m_dm= exp(x.at(3));
			return true;
		}
	};

	virtual double Inverse_F(double P, double S, double Rho, double S0){
		return pow(m_dSigS*max(P*Rho-2*S*m_dSig0, 0.0)/m_dK/max(2*S*m_dSigS-P*Rho, m_dDelta), 1/m_dm);
	}
public:
	double m_dSigS;
	double m_dSig0;
	double m_dK;
	double m_dm;
	double m_dDelta;

};