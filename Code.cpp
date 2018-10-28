#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <errno.h>
#include <math.h>


enum SOLUTIONS
{
	SS_INF_SOL = 3,//! Constant, that means infinity amount of solutions
	SS_TWO_SOL = 2,//! Constant, that means two solutions
	SS_ONE_SOL = 1,//! Constant, that means one solution
	SS_NO_SOL  = 0,//! Constant, that means that you have no solutions
};

//----------------------------------------------------------------

/*!  \brief Calculating solutions of the equation

	This function calculates amount of solutions with help of SolveLinear function or
	calculation of a discriminant*/
int SolveSquare(double a, double b, double c, double * x1, double * x2);

/*! \brief Calculating solution of the linear equation			
	
	This function calculates amount of solutions of a linear equation*/
int SolveLinear(double b, double c, double * x1);	

/*! \brief Input of coefficients								

	This one takes coefficients of your equation*/
int Input(double * a, double *b, double * c);

/*! \brief Processing of Results

	Output of an information about your solutions*/
int Results(double a, double b, double c, double x1, double x2, int nSolves);

/*! \brief Tests
		
	Checks a correctness of results of yours algorithm's work*/
int UnitTests(void);	

//----------------------------------------------------------------

int UnitTests(void)
{
	int nSolves = 0;
	double x1 = 0, x2 = 0;
	int arr[11][6] = 
	{
		{ 0,  0,  9, SS_NO_SOL     		  },
		{ 0,  0,  0, SS_INF_SOL    		  },
		{ 1,  0,  0, SS_ONE_SOL,  0		  },
		{ 0,  5,  0, SS_ONE_SOL,  0		  },
		{ 0,  1, -1, SS_ONE_SOL,  1		  },
		{-1, -4, -4, SS_ONE_SOL, -2		  },
		{ 0, -2,-12, SS_ONE_SOL, -6		  },
		{ 4,  4,  0, SS_TWO_SOL,  0,    -1},
		{-1,  0,  4, SS_TWO_SOL, -2,     2},
		{ 1,  3,  2, SS_TWO_SOL, -1,    -2},
		{-1,  4,  5, SS_TWO_SOL, -1,     5},
	};
	for(int i = 0; i < 11; i++)
	{
		nSolves = SolveSquare(arr[i][0], arr[i][1], arr[i][2], &x1, &x2);
		if(nSolves != arr[i][3])
		{
			printf("\nIncorrect amount of solutions on the %d line\n", i);
			return -1;
		}
		switch(arr[i][3])
		{
			case 1:
				if(x1 != arr[i][4])
				{
					printf("\nIncorrect calculation on the %d line\n", i);
					return -1;
				}
				break;

			case 2:
				if(x1 != arr[i][4] || x2 != arr[i][5])
				{
					printf("\nIncorrect calculations on the %d line\n", i);
					return -1;
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
		errno = EINVAL;
		perror("Incorrect values");
		return -1;
	}

	if(x1 == x2 || x1 == NULL || x2 == NULL)
	{
		errno = EINVAL;
		perror("Incorrect values");
		return -1;
	}

	int solves = 0;
	if(a == 0)
	{
		*x2 = NAN;
		solves = SolveLinear(b, c, x1);
	}
	else
	{
		double d = (b * b - 4 * a * c);
		if(d < 0)
			solves = SS_NO_SOL;
		if(d == 0)
		{
			solves = SS_ONE_SOL;
			*x1 = *x2 = (-b) / (2 * a);
		}
		if(d > 0)
		{
			solves = SS_TWO_SOL;
			*x1 = (-b + sqrt(d)) / (2 * a);
			*x2 = (-b - sqrt(d)) / (2 * a);
		}
	}
	return solves;
}

int SolveLinear(double b, double c, double * x1)
{
	if(!isfinite(b) || !isfinite(c))
	{
		errno = EINVAL;
		perror("Incorrect values");
		return -1;
	}

	if(x1 == NULL)
	{
		errno = EINVAL;
		perror("Incorrect values");
		return -1;
	}

	int solves = 0; 
	if(b == 0 && c == 0)
		solves = SS_INF_SOL;
	else if(b == 0 && c != 0)
		solves = SS_NO_SOL;
	else
	{
		*x1 = -(c / b);
		solves = SS_ONE_SOL;
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

int Results(double a, double b, double c, double x1, double x2, int nSolves)
{
	if(!isfinite(a) || !isfinite(b) || !isfinite(c))
	{
		errno = EINVAL;
		perror("Incorrect values");
		return -1;
	}

	switch(nSolves)
	{
		case SS_NO_SOL:// NO_SOLUTIONS
			printf("You have no solutions:(\n");
			break;

		case SS_ONE_SOL:
			printf("You have only 1 solution:\nIt's %lg\n", x1);
			break;

		case SS_TWO_SOL:
			printf("You have 2 solutions:\nFirst = %lg\nSecond = %lg\n", x1, x2);
			break;

		case SS_INF_SOL:
			printf("Endless number of solutions\nAny number is a solution\n");
			break;

		default :
			printf("Unexpected error: nSolves = %d, a = %lg, b = %lg, c = %lg\nReturning with error.\n", nSolves, a, b, c);
	}
	return 0;
}

int main()
{
	if(UnitTests() < 0)
		printf("Programm is not ready:(\n\n");

	printf("#Calculating if a square equation\n");
	printf("#Enter numbers:\n");

	double a = 0, b = 0, c = 0;										
	double x1 = 0, x2 = 0;
	int Count = 0;

	Count = Input(&a, &b, &c);																	
	printf("It's was your %d attempt\n", ++Count);

	int nSolves = SolveSquare(a, b, c, &x1, &x2);
	if(nSolves < 0)
	{
		printf("ERROR : incorrect work of SolveSquare\n");
		return errno;
	}

	if(Results(a, b, c, x1, x2, nSolves) != 0)
	{
		printf("ERROR : incorrect processing of results\n");
		return errno;
	}

	return 0;
}
