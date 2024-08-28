#pragma once
#include <stdio.h>

class Geometry;
class SSContactData;
class Interface_0;
class Interface_1;
class Particle;
class Matrix;

using namespace std;

class ContactParticleBody
{
public:
	ContactParticleBody();
	virtual ~ContactParticleBody();

	int nDOF;
	bool previous_evaluation;			//Flag to evaluate previous contact condition
	Particle* pA;
	Geometry* sB;

	int index1;				//Particle 1 - index
	int index2;				//Body 2 - index
	int sub_index1;			//Particle 1 - sub_index
	int sub_index2;			//Body 2 - sub_index
	
	bool cur_active;		//Flag active/unnactive - current status
	bool prev_active;		//Flag active/unnactive - previous status (of current time-step)

	virtual void PreCalc() = 0;
	void ProcessSurfacePair();
	//Explicit
	void FinalProcessSurfacePairsExplicit(double t);
	void EvaluateNormalGap();
	virtual bool HaveErrors() = 0;
	void SolveLCP();
	virtual void SurfacePoints() = 0;					//Sets GammaA and GammaB with contact positions on both surfaces
	virtual void SolvePreviousContact() = 0;

	

	virtual void Alloc() = 0;
	virtual void Free() = 0;
	virtual void MountLocalContributions() = 0;
	virtual void SetVariables() = 0;					//Sets variables for AceGen codes interfaces
	virtual void Report() = 0;
	virtual void CompactReport() = 0;
	virtual void InitialGuess() = 0;
	
	virtual double ObjectivePhase1(Matrix& mc) = 0;								//Calcula a fun��o objetivo para um conjunto de coordenadas convectivas - Phase 1
	virtual void GradientPhase1(Matrix& mc, Matrix& mGra) = 0;					//Calcula o Gradiente da fun��o objetivo - Phase 1
	virtual void HessianPhase1(Matrix& mc, Matrix& mHes) = 0;					//Calcula a Hessiana da fun��o objetivo - Phase 1

	//virtual double Gap(Matrix& mc, bool fixed_normals, Matrix& nA, Matrix& nB) = 0;											//Calcula e rotorna o gap (com sinal)
	//virtual void GradientGap(Matrix& mc, Matrix& mGra, bool fixed_normals, Matrix& nA, Matrix& nB) = 0;						//Calcula o Gradiente do gap
	//virtual void HessianGap(Matrix& mc, Matrix& mHes, bool fixed_normals, Matrix& nA, Matrix& nB) = 0;						//Calcula a Hessiana do gap
	virtual int VerifyConvectiveRange(Matrix& mc) = 0;							//Verifica range de coordenadas convectivas
	virtual void InitializeConvectiveRange() = 0;								//Initialize range of validity of convective coordinates

	bool FindMinimumSolution(SSContactData* c_data, Matrix* solution, int &return_info);								//Otimiza��o - determina��o de m�nimo
	bool FindMinimumSolutionDegenerated(SSContactData* c_data, Matrix* P_0, Matrix* solution);						//Otimiza��o - determina��o de m�nimo
	//bool FindSaddleSolution(SSContactData* c_data, Matrix* solution, int &return_info, bool return_gap);				//Otimiza��o - determina��o de sela
	//bool FindSaddleSolutionDegenerated(SSContactData* c_data, Matrix* P_0, Matrix* solution, bool return_gap);		//Otimiza��o - determina��o de sela
	//bool FindMinimumGapDegenerated(SSContactData* c_data, Matrix* P_0, Matrix* solution, int &return_info, bool fixed_normals, Matrix& nA, Matrix& nB);			//Otimiza��o - determina��o de m�nimo do gap com sinal
	int CharacterizeCriticalPoint(Matrix* solution);
	int CharacterizeCriticalPointDegenerated(Matrix* solution, Matrix* P_0, bool print = false);
	void DefaultValues();
	double tol_small_1;		//Crit�rio para n�mero muito pequeno - res�duo != 0
	double tol_eig;			//Crit�rio para autovalor baixo
	double tol_convective;	//Criterio para maximo erro nas coordenadas convectivas
	double tol_ascent;
	int max_it_1;			//N�mero m�ximo de itera��es para otimiza��o - phase 1
	int max_it_2;			//N�mero m�ximo de itera��es para otimiza��o - phase 2

	virtual void MountGlobal() = 0;
	virtual void MountGlobalExplicit() = 0;
	void MountContact();
	void MountContactExplicit(double t);
	void SaveConfiguration();
	void Clear();
	bool NightOwlContact();
	void WriteVTK_XMLForces(FILE *f);

	//Variables for contact evaluation:
	SSContactData* cd;						//information of the contact between surfaces
	double* Rc;								//Vetor de esfor�os internos
	double** Kc;							//Matriz de rigidez

	void EvaluateInvertedHessian();			//Calcula a inversa da Hessiana
	
	Matrix* I3;
	Matrix* GammaA;
	Matrix* GammaB;

	//Common AceGenPointers (to all surface pairs)
	double* fn;
	double* ft;
	double* v;
	double* dA;
	double* dB;
	double* duiA;
	double* dduiA;
	double* duiB;
	double* dduiB;
	
	double* me;				//Equivalent body-pair mass (for contact-impact purposes)

	bool eligible;			//Set by the function that creates surface pairs - may change in each iteration of NR
	bool prev_eligible;		//Previous converged eligible

	bool alloc_control;

	double*dA_zero;
	double*dB_zero;

	Matrix* convective_range;	//Matrix que guarda os ranges de coordenadas convectivas validas para as superficies
	Matrix* convective_max;		//Matrix que guarda os valores m�ximos de coordenadas convectivas
	Matrix* convective_min;		//Matrix que guarda os valores m�nimos de coordenadas convectivas
	double minimum_convective_range;

	bool invalid;

	//TR report
	FILE *f_TR_report;
	void OpenTRReport();
	void InitializeTRReport();
	bool write_report;
	bool write_report_diverged;
	char name[1000];

	//Interface model parameters
	double(*epsn1);
	double(*n1);
	double(*n2);
	double(*gnb);
	double(*gnbb);
	double(*zetan);
	double(*mus);
	double(*mud);
	double(*epst);
	double(*ct);

	bool interface_0_flag;
	bool interface_1_flag;
	Interface_0* inter_0;
	Interface_1* inter_1;
};

