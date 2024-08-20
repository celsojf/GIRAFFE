#include "Matrix.h"
#include "SurfaceData.h"

#pragma once
class SSContactData
{
public:
	SSContactData();
	~SSContactData();
	int n_solutions;
	double** convective;
	double** copy_convective;
	double** copy_deg_coordinates;				//degenerated coordinates copy
	double** initial_guess;						//initial guess to be used in SSMP
	
	bool** deg_control;							//control of degeneration
	Matrix** P;									//degeneration basis
	Matrix** P_0;								//Degenerative operator
	void MountDegenerativeOperator();			//Using info from deg_control and P, establishes P_0 by selecting appropriate columns

	int* characterization_index;
	int* copy_characterization_index;
	int* return_value;
	int* copy_return_value;
	bool* copy_convergedLCP;
	bool* convergedLCP;
	bool* repeated;
	double*** invHessian;						//Inverse of the Hessian matrix - determined during the FindMinimumParameters routine
	
	bool* copy_degenerated;						//true ou false para indicar se o contato foi ou n�o degenerado no passo anterior
	bool* degenerated;							//true ou false para indicar se o contato � ou n�o degenerado
	
	double* g_n;								//gap normal
	double* copy_g_n;							//gap normal
	Matrix** g_t;								//gap tangencial - atual
	Matrix** copy_g_t;							//gap tangencial - c�pia
	Matrix** g;									//gap vetorial - atual
	Matrix** copy_g;							//gap vetorial - c�pia
	Matrix ** n;								//contact normal direction
	Matrix ** copy_n;							//contact normal direction - copia
	bool* stick;								//boolean - indicates stick (true) or slide (false)
	bool* copy_stick;							//boolean - indicates stick (true) or slide (false) - copia
	
	SurfaceData* surf1;							//Dados - superf�cie 1
	SurfaceData* surf2;							//Dados - superf�cie 2

	bool alloced;								//Booleana que indica se est� ou n�o alocado - controle de aloca��o
	void CheckRepeated(double tol_coordinate_value);	//Checa repeti��o de ra�zes e salva a informa��o na matriz 'repeated'
	void Plot();
	void PlotSmallReport();
	void Alloc();										//Aloca matrizes
	void Free();										//Desaloca matrizes	
};	

