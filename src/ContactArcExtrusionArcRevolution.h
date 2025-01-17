#pragma once
#include "ContactBodyBody.h"
class ContactArcExtrusionArcRevolution :
	public ContactBodyBody
{
public:
	ContactArcExtrusionArcRevolution();
	~ContactArcExtrusionArcRevolution();

	void Alloc();
	void Free();
	void MountLocalContributions();
	void SetVariables();					//Sets variables for AceGen codes interfaces
	void Report();
	void CompactReport();
	void InitialGuess();

	double ObjectivePhase1(Matrix& mc);								//Calcula a fun��o objetivo para um conjunto de coordenadas convectivas - Phase 1
	void GradientPhase1(Matrix& mc, Matrix& mGra);					//Calcula o Gradiente da fun��o objetivo - Phase 1
	void HessianPhase1(Matrix& mc, Matrix& mHes);					//Calcula a Hessiana da fun��o objetivo - Phase 1
	double Gap(Matrix& mc, bool fixed_normals, Matrix& nA, Matrix& nB);											//Calcula e rotorna o gap (com sinal)
	void GradientGap(Matrix& mc, Matrix& mGra, bool fixed_normals, Matrix& nA, Matrix& nB);						//Calcula o Gradiente do gap
	void HessianGap(Matrix& mc, Matrix& mHes, bool fixed_normals, Matrix& nA, Matrix& nB);						//Calcula a Hessiana do gap
	int VerifyConvectiveRange(Matrix& mc);							//Verifica range de coordenadas convectivas
	void InitializeConvectiveRange();								//Initialize range of validity of convective coordinates

	void PrintAceGenPointers();

	double* cAp;
	double* cBp;
	double* cAi;
	double* cBi;

	//AceGen Pointers - specific
	double* radA;                                             //Raio de curvatura do arco
	double* cpointA;											//Centro de curvatura do arco
	double* radB;                                             //Raio de curvatura do arco
	double* cpointB;											//Centro de curvatura do arco

	bool* normalintA;
	bool* normalintB;
	double* xAAi;
	double* xBAi;
	double* xABi;
	double** QAAi;
	double** QBAi;
	double** QABi;

	double* gti;
	double* gtpupdated;
	bool *stick;
	bool *stickupdated;
	double** invH;
	bool *interfacelaw0;
};

