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
int Input(double * a, double *b, double * c);

// Tests
int UnitTests(void);	

//----------------------------------------------------------------

int UnitTests(void)
{
	int nSolves = 0;
	double x1 = 0, x2 = 0;
	int arr[11][6] = 
	{
		{0, 0, 9, 0},
		{1, 0, 0, 1, 0},
		{0, 5, 0, 1, 0},
		{0, 1, -1, 1, 1},
		{4, 4, 0, 2, 0, -1},
		{-1, -4, -4, 1, -2},
		{-1, 0, 4, 2, -2, 2},
		{0, -2, -12, 1, -6},
		{1, 3, 2, 2, -1, -2},
		{-1, 4, 5, 2, -1, 5},
		{0, 0, 0, -1},
	};
	for(int i = 0; i < 11; i++)
	{
		nSolves = SolveSquare(arr[i][0], arr[i][1], arr[i][2], &x1, &x2);
		if(nSolves != arr[i][3])
		{
			printf("Programm crashed on the %d line with error #3\n", i);
			printf("%d %d %d %d\n", nSolves, arr[i][0], arr[i][1], arr[i][2]);
			exit(3);
		}
		switch(arr[i][3])
		{
			case 1:
				if(x1 != arr[i][4])
				{
					printf("Programm crashed on the %d line with error #4\n", i);
					exit(4);
				}
				break;

			case 2:
				if(x1 != arr[i][4] || x2 != arr[i][5])
				{
					printf("Programm crashed on the %d line with error #5\n", i);
					exit(5);
				}
				break;
		}
	}
	printf("\nProgramm is ready:)\n\n");
	return 0;
}

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

int Input(double * a, double * b, double * c)
{
	int Count = 0;
	while(scanf("%lg%lg%lg", a, b, c) != 3)
	{
		printf("\n");
		while(getchar() != '\n');
		printf("Incorrect value\nPlease, enter numbers:\n");
		Count++;
	}
	printf("\n");
	return Count;
}

int main()
{
	UnitTests();
	printf("#Calculating if a square equation\n");
	printf("#Enter numbers:\n");

	double a = 0, b = 0, c = 0;														// initialization of coefficients
	double x1 = 0, x2 = 0;															// initialization of solutions
	int Count = 0;

	Count = Input(&a, &b, &c);																// Input of coefficients
	printf("It's was your %d attempt\n", ++Count);

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
