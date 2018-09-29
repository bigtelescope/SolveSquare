#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <cfloat>
#include <cmath>

//----------------------------------------------------------------

int SolveSquare(double a, double b, double c, double * p1, double * p2);			// Calculating solutions of the equation
int SolveLinear(double b, double c, double * p1, int solves);						// Calculating solution of the linear equation
void Input(double * a, double *b, double * c);										// Input of coefficients

//----------------------------------------------------------------

int SolveSquare(double a, double b, double c, double * p1, double * p2)
{
	assert(std::isfinite(a));
	assert(std::isfinite(b));
	assert(std::isfinite(c));
	assert(p1 != NULL);
	assert(p2 != NULL);
	int solves = INT_MAX;
	if(a == 0)
	{
		if(b == 0)
		{
			solves = INT_MAX;
		}
		else if(b != 0)
		{
			solves = SolveLinear(b, c, p1, solves);
		}
	}
	else if(b == 0) // Is "else" needed here?
	{
		if(a != 0 && c != 0)
		{
			*p1 = sqrt(c/a);
			*p2 = -sqrt(c/a);
			solves = 2;
		}
		if(a != 0 && c == 0)
		{
			*p1 = 0;
			solves = 1;
		}
	}
	else if(c == 0) // Is "else" needed here?
	{
		if(a != 0 && b != 0)
		{
			*p1 = -b/a;
			*p2 = 0;
			solves = 2;
		}
	}
	else
	{
		double d = (b * b - 4 * a * c);
		if(d < 0)
			solves = 0;
		if(d == 0)
		{
			solves = 1;
			*p1 = (-b) / (2 * a);
		}
		if(d > 0)
		{
			solves = 2;
			*p1 = (-b + sqrt(d)) / (2 * a);
			*p2 = (-b - sqrt(d)) / (2 * a);
		}
	}
	return solves;
}

int SolveLinear(double b, double c, double * p1, int solves)
{
	assert(b != 0);
	solves = 1;
	*p1 = -c/b;
	if(c == 0)
		*p1 = 0;
	return solves;
}

void Input(double * a, double * b, double * c)
{
	int retValue = 0;
	retValue = scanf("%lg %lg %lg", a ,b ,c);
	/*do
	{
		printf("before %d\n", retValue);
		retValue = scanf("%lg %lg %lg", &a, &b, &c);
		printf("after %d\n", retValue);
	}*/
	/*while(retValue != 3);*/
}

int main()
{
	printf("#Calculating if a square equation\n");
	printf("#Enter numbers:\n");

	double a, b, c;															// initialization of coefficients
	double x1, x2;															// initialization of solves

	/*if(scanf("%lg %lg %lg", &a, &b, &c) != 3)								// input of values
	{
		printf("Error\n");
		//exit(0);
	}*/

	Input(&a, &b, &c);

	int nSolves = SolveSquare(a, b, c, &x1, &x2);							// calculation of numbers of solves
	
	switch(nSolves)
	{
		case 0:
			printf("You have no solutions:(\n");
			break;

		case 1:
			printf("You have 1 solutions:\nIt's %lg\n", x1);
			break;

		case 2:
			printf("You have 2 solutions:\nFirst = %lg\nSecond = %lg\n", x1, x2);
			break;

		case INT_MAX:
			printf("Endless number of solutions\nAny number is a solution\n");
			break;

		default :
			printf("Invalid value\n");
	}
	return 0;
}
