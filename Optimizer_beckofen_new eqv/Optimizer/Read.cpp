#include "Point.h"
#include "Read.h"


////////////////////////////////////////////////
bool ReadFile(vector<CPoint> &dst){

	FILE *fp;
	//fopen_s (&fp,"experiment_AMg_6.txt", "r");   // для АМг - 6
	//fopen_s(&fp, "input_sorgente_mod_all.txt", "r");
	fopen_s(&fp, "dot_plot_4.txt", "r");
	//fopen_s (&fp,"experiment_P3.txt", "r");
	//fopen_s (&fp,"experiment_P3.5.txt", "r");
	//fopen_s (&fp,"experiment_P4.txt", "r");
	//fopen_s (&fp,"experiment_P5.txt", "r");
	//fopen_s (&fp,"experiment_P6.txt", "r");

	//fopen_s (&fp,"experiment_OT_4.txt", "r");  // для ОТ - 4
	//fopen_s (&fp,"input.txt", "r");  // для всех
	//fopen_s (&fp,"OT__P3.txt", "r");
	//fopen_s (&fp,"OT__P8.txt", "r");
	//fopen_s (&fp,"OT__P12.txt", "r");
	//fopen_s (&fp,"OT__P16.txt", "r");
		
	if (!fp) return false;

	char ch;
	int count = 0;
	while (count<4){
		if (!fread (&ch, sizeof(char), 1, fp)) return false;
		if (ch == '\n') count++;
	}

	CPoint point;
	bool bEOF = false;

	double P0 = -1;
	double A=0;
	int i0=0;
	while (!bEOF){
		point.P = ReadDouble(fp, bEOF)*0.101325;
		point.S0 = ReadDouble(fp, bEOF);
		point.S = ReadDouble (fp, bEOF);
		point.H = ReadDouble (fp, bEOF);
		point.t = ReadDouble(fp, bEOF);
		point.R0 = ReadDouble(fp, bEOF);
		if (!bEOF){
			point.Rho0 = ReadDouble (fp, bEOF);
			dst.push_back(point);
			
			/*if(P0 != point.P){
				if(dst.size()>1){
					A/=(dst.size()-1-i0);
					for(int i=i0; i<dst.size()-1; i++){
						dst[i].S = dst[i].S0-A*dst[i].S0*dst[i].H*dst[i].H*2/(dst[i].H*dst[i].H+dst[i].R0*dst[i].R0);
					}
				}
				i0 = dst.size()-1;
				A=0;
				P0 = point.P;
			}
			A += (1-point.S/point.S0)*(point.H*point.H+point.R0*point.R0)/(2*point.H*point.H);
			*/
		}
	}
	return true;
}
////////
bool isFigure (char ch){
	if (ch>= '0' && ch<='9' || ch == '.' || ch=='-') return true;
	return false;
}

//////
double ReadDouble(FILE *fp, bool &bEOF){
	bEOF = false;
	char str[100] = " ", ch;
	int i = 0;
	bool bFirstSpace = true;
	
	do{
		if (!fread (&ch, sizeof (char), 1, fp)){
			bEOF=true;
			break;
		}
		if (isFigure(ch)){
			str [i++] = ch;
			bFirstSpace = false;
		}
		if (i>=99) break;
	}while (isFigure (ch) ||bFirstSpace);
	str[i] = 0;

	return atof(str);
}
////
void  Out_points(vector <CPoint> &data){
	for (int i=0; i<data.size(); i++){
		//cout <<" P \t S0 \t S/S0 \t S \t H \tt \tR0 " << '\n';
			cout << data[i].P << '\t'<<
			data[i].S0 << '\t'<<
			data[i].Rho0 << '\t'<<
			data[i].S << '\t'<<
			data[i].H << '\t'<<
			data[i].t << '\t'<<
			data[i].R0 << '\n';
	}
	cout << '\n' << "................" << endl;
};

