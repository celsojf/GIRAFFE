#include "SurfacePairGeneralContact.h"

#include "TimeStepControlData.h"
#include "SSContactData.h"
#include "Matrix.h"

////////////////////////////////////////////////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
////////////////////////////////////////////////////////////////////

SurfacePairGeneralContact::SurfacePairGeneralContact()
{
}


SurfacePairGeneralContact::~SurfacePairGeneralContact()
{
}

bool SurfacePairGeneralContact::GetActive()
{
	return active;
}

void SurfacePairGeneralContact::Alloc()
{
	AllocSpecific();
}

void SurfacePairGeneralContact::SetActive()
{
	if (active == false)
	{
		td = DBG_NEW TimeStepControlData();
		cd = DBG_NEW SSContactData();
		cd->n_solutions = 1;
		cd->Alloc();
		PreCalc();
		active = true;
	}
}

void SurfacePairGeneralContact::SetUnnactive()
{
	if (active == true)
	{
		delete td;
		delete cd;
		active = false;
	}
	Free();
}

void SurfacePairGeneralContact::Free()
{
	FreeSpecific();
}

//Calcula a inversa da Hessiana
void SurfacePairGeneralContact::EvaluateInvertedHessian()
{
	Matrix invHes(4, 4);
	if (cd->P_0[0]->getColumns() != 0)
	{
		//Tolerance for precision of eigenvalues extraction
		double tol_eig = 1e-14;
		Matrix Hes(4, 4);
		Matrix xk(4);
		for (int i = 0; i < 4; i++)
			xk(i, 0) = cd->convective[0][i];
		HessianPhase1(Hes);

		Matrix Hes_minor = transp(*cd->P_0[0])*Hes*(*cd->P_0[0]);
		int order_minor = cd->P_0[0]->getColumns();
		Matrix P(order_minor, order_minor);
		Matrix D(order_minor, order_minor);
		fulleigen1(Hes_minor, P, D, tol_eig);
		//Invers�o da Hessiana
		for (int i = 0; i < order_minor; i++)
		{
			D(i, i) = 1.0 / D(i, i);
		}
		invHes = (*cd->P_0[0])*P*D*transp(P)*transp(*cd->P_0[0]);
	}
	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			cd->invHessian[0][i][j] = invHes(i, j);
}
