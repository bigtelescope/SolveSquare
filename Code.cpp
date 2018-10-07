#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

#define SS_INF_ROOTS -1

//----------------------------------------------------------------

// Calculating solutions of the equation
int SolveSquare(double a, double b, double c, double * x1, double * x2);

// Calculating solution of the linear equation			
int SolveLinear(double b, double c, double * x1);	

// Input of coefficients								
void Input(double * a, double *b, double * c);	

//----------------------------------------------------------------

int SolveSquare(double a, double b, double c, double * x1, double * x2)
{
	if(!isfinite(a) || !isfinite(b) || !isfinite(c))
	{
		printf("Incorrect values\nProgramm crashed with code 1");
		exit(1);
	}

	if(x1 == x2 || x1 == NULL || x2 == NULL)
	{
		printf("Incorrect values\nProgramm crashed with code 2");
		exit(2);
	}

	int solves = 0;
	if(a == 0)
	{
		solves = SolveLinear(b, c, x1);
	}
	else
	{
		double d = (b * b - 4 * a * c);
		if(d < 0)
			solves = 0;
		if(d == 0)
		{
			solves = 1;
			*x1 = (-b) / (2 * a);
		}
		if(d > 0)
		{
			solves = 2;
			*x1 = (-b + sqrt(d)) / (2 * a);
			*x2 = (-b - sqrt(d)) / (2 * a);
		}
	}
	return solves;
}

int SolveLinear(double b, double c, double * x1)
{
	int solves = 0; 
	if(b == 0 && c == 0)
		solves = SS_INF_ROOTS;
	else if(b == 0 && c != 0)
		solves = 0;
	else
	{
		*x1 = -(c / b);
		solves = 1;
	}
	return solves;
}

void Input(double * a, double * b, double * c)
{
	while(scanf("%lg%lg%lg", a, b, c) != 3)
	{
		printf("\n");
		while(getchar() != '\n');
		printf("Incorrect value\nPlease, enter numbers:\n");
	}
	printf("\n");
}

int main()
{
	printf("#Calculating if a square equation\n");
	printf("#Enter numbers:\n");

	double a = 0, b = 0, c = 0;														// initialization of coefficients
	double x1 = 0, x2 = 0;															// initialization of solutions

	Input(&a, &b, &c);																// Input of coefficients

	int nSolves = SolveSquare(a, b, c, &x1, &x2);									// calculation of solutions
	
	switch(nSolves)
	{
		case 0:
			printf("You have no solutions:(\n");
			break;

		case 1:
			printf("You have only 1 solution:\nIt's %lg\n", x1);
			break;

		case 2:
			printf("You have 2 solutions:\nFirst = %lg\nSecond = %lg\n", x1, x2);
			break;

		case SS_INF_ROOTS:
			printf("Endless number of solutions\nAny number is a solution\n");
			break;

		default :
			printf("Unexpected error: nSolves = %d, a = %lg, b = %lg, c = %lg\nReturning with error.\n", nSolves, a, b, c);
	}
	return 0;
}
