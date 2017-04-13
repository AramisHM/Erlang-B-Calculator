#include <stdio.h>
#include <stdlib.h>
#include <math.h> // abs


/*

Alunos : Aramis Hornung
		 Alexandre Martins
*/

/*
The MIT License (MIT)

Copyright (c) 2015
Aramis Hornung (PUCPR - Computer Science);
Alexandre Martins (PUCPR - Computer Science)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// extended erlangB precisa do calculo de erlangB
float erlangB(float E, int m)
{
	float invB = 1.0;
	float erlB;

	for (int i = 0; i <= m; i++)
	{
		invB = 1.0 + invB * i / E;
	}

	erlB = 1.0 / invB;

	return erlB;
}

// iterative calculation of extended erlang B
float extended_erlangB(float E0, int m, float prf, float epsolon)
{
	float Bi = 0, Ai = 0, Ei1 = 0, r = 0;
	float diff = 99999;
	float Ei = E0; 

	while(diff > epsolon)
	{
		// 1. calculate erlangB
		Bi = erlangB(Ei, m);

		// 2. calculate probable blocked calls
		Ai = Ei * Bi;

		// 3. calculate number of recalls, r assuming recall factor, rf
		r = Ai * prf;

		// 4. calculate new offered traffic
		Ei1 = E0 + r;

		// 5 - iterate!
		diff = abs(Ei1-Ei); // auxiliar condicao de parada epsolon
		Ei = Ei1;
		
	}
	return Bi;
}

// Probabilidade de chamada ser perdida
float loss_erlang(float B, float p)
{
	float L = 0;
	return (B*(1-p)) / (1-(B*p));
}

int main(int argc, char *argv[])
{
	//E0 = intensidade de chamadas
	//m  = numero servidores
	//p  = probabilidade de retry
	//-------------------------------
	//B  = probabilidade de bloqueio
	//L  = probabilidad de perda
	float epsolon = 0.0001; // usado como condição de parada
	float intensidade_chamadas = 0;//0.2;
	int numero_servidores = 0;//1;
	float probabilidade_retry = 0;//0.5;
	//---------------------------
	float probabilidade_bloqueio;	// Resultado esperado
	float probabilidade_perda;		// Resultado esperado
	
	printf("intensidade_chamadas: "); fflush(stdin); scanf("%f", &intensidade_chamadas );
	printf("numero_servidores: "); fflush(stdin); scanf("%d", &numero_servidores );
	printf("probabilidade_retry: "); fflush(stdin); scanf("%f", &probabilidade_retry );
		
	float B = extended_erlangB(intensidade_chamadas, numero_servidores, probabilidade_retry, epsolon);
	float p = probabilidade_retry;
	float L = loss_erlang(B, p);
	printf("intensidade_chamadas (E0): %f\nnumero_servidores (m): %d\nprobabilidade_retry (p): %f\n\n\n", intensidade_chamadas, numero_servidores, probabilidade_retry);
	printf("probabilidade_bloqueio (B): %f\n\n", B);
	printf("probabilidade_perda (L): %f\n\n", L);
	
	return 1;
}