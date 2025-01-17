#pragma once
#include "Element.h"
#include "Matrix.h"

class SpringDashpot_1 :
	public Element
{
public:
	SpringDashpot_1();
	~SpringDashpot_1();
	bool Check();				//Checa inconsist�ncias no elemento para evitar erros de execu��o
	bool Read(FILE *f);
	void Write(FILE *f);
	void WriteResults(FILE *f);//Escreve arquivo de resultados
	void WriteMonitor(FILE *f, bool first_record, double time);	//Escreve no monitor do elemento
	void WriteVTK_XMLBase(std::vector<float> *float_vector);
	void WriteVTK_XMLRender(FILE *f);
	void Mount();			//Monta elementos
	void MountElementLoads();			//Monta carregamentos associados ao elemento
	void MountMass();					//Monta a matriz de massa
	void MountMassModal();				//Monta a matriz de massa para realiza��o da analise modal
	void MountDamping(bool update_rayleigh);				//Monta a matriz de amortecimento
	void MountDampingModal();			//Monta a matriz de amortecimento para realiza��o da analise modal
	void MountDyn();					//Montagens - Newmark
	void MountDynModal();				//Montagens para analise modal - inser��o da matriz de massa e amortecimento na matriz de rigidez para posterior montagem global
	void TransformMatrix();	//Monta matriz de transforma��o de coordenadas
	void MountGlobal();		//Preenche a contribui��o do elemento nas matrizes globais

	void SaveLagrange();	//Salva variaveis nos pontos de Gauss uteis para descri��o lagrangiana atualizada
	void PreCalc();		//Pre-calculo de variaveis que e feito uma unica vez no inicio
	void Zeros();			//Zera matrizes locais do elemento

	//Variaveis do elemento
	double k;	//Stiffness
	double c;	//Damping
	double initial_distance;
	double gn;		//gap normal
	Matrix z1, z2;	//Posi��es dos n�s
	Matrix xd1, xd2;//Velocidades dos n�s
	Matrix c_stiffness;									//Matriz de rigidez
	Matrix c_damping;									//Matriz de amortecimento
	Matrix c_damping_modal;									//Matriz de amortecimento
	Matrix c_stiffness_force;							//Vetor de esfor�os elasticos
	Matrix c_damping_force;								//Vetor de esfor�os de amortecimento
	Matrix I3;
	Matrix z1z2;	//distancia atual entre n�s
	Matrix n;		//dire��o normal da mola
	
	Matrix non;
	double f;
	Matrix C1;
	Matrix C2;
	Matrix C3;

	//P�s-processamento
	double elastic_force;
	double damping_force;

	Matrix last_n;	//ultima dire��o normal convergida da mola
	bool first_evaluation;
};

