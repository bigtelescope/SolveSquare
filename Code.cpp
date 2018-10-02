#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

/*
	С++, конечно, поддерживает обратную совместимость с С,
	но миксовать не стоит. Лучше либо все С, и писать Сшный
	код, либо все-таки С++ юзать. Плюсовые аналоги есть, вроде,
	на каждую библиотеку сишную, если что, на cplusplus.com
	можно глянуть.
 */

#include <cfloat>
#include <cmath>

// Не надо слеплять все в кучу:)

/* 
	И лучше более говорящее имя. Насколько помню, Дед предлагал
	SS_INF_ROOTS. А то сейчас получается, что ты задефайнил 42
	как бесконечность, и это довольно стремно
 */
#define INF 42

//----------------------------------------------------------------

/*
	Длинные строчки - не бро. Есть такая тема, что строчки не 
	длиннее 80 символов. Посему комменты не стоит туда пихать.

	Ну и Доксигенчик любимый на замену сим комментам :)
 */

// Calculating solutions of the equation
int SolveSquare(double a, double b, double c, double * x1, double * x2);
// Calculating solution of the linear equation
int SolveLinear(double b, double c, double * x1);
// Input of coefficients
void Input(double * a, double *b, double * c);

//----------------------------------------------------------------

int SolveSquare(double a, double b, double c, double * x1, double * x2)
{
/* 
	Наверное, есть смысл эти три проверки вынести в ифы. Ассерты -
	проверки ошибок программиста, а в данном случае есть смысел 
	проверять ифами, ибо это при сборке в release надо бы оставить
 */
	assert(std::isfinite(a));
	assert(std::isfinite(b));
	assert(std::isfinite(c));
	assert(x1 != x2);
	assert(x1 != NULL);
	assert(x2 != NULL);

	int solves = 0;
	if(a == 0)
	{
		solves = SolveLinear(b, c, x1);
	}
	else
	{
		double d = (b * b - 4 * a * c);
		if(d <  0)
			solves = 0;
		if(d == 0)
		{
			solves = 1;
			*x1 = (-b) / (2 * a);
		}
		if(d >  0)
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
/*
	Сюда бы тоже проверки. Функция же независима от того,
	с какими параметрами ее вызывают. В данной задаче да,
	у тебя сюда всякие inf не пройдут, но вообще говоря
	они же могут здесь оказаться. Так что надо бы ифы пихнуть.
	И ассерт на указатель.
 */
	int solves = 0; 
	if(b == 0)
/*
	Кажется, 0 0 0 - inf, а 0 0 5 - 0. У уравнения 5 = 0 корней
	вроде нет, а прога говорит, что бесконечно их
 */
		solves = INF;
	else
	{
		*x1 = -(c / b);
		solves = 1;
	}
	return solves;
}

/* 
	Войд - не круто. Лучше возвращать что-то. В данном случае 
	можно число неудачных попыток.
 */
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
			printf("You have 1 solutions:\nIt's %lg\n", x1);
			break;

		case 2:
			printf("You have 2 solutions:\nFirst = %lg\nSecond = %lg\n", x1, x2);
			break;

		case INF:
			printf("Endless number of solutions\nAny number is a solution\n");
			break;

		default :
			printf("Unexpected error: nSolves = %d, a = %lg, b = %lg, c = %lg\nReturning with error.\n", nSolves, a, b, c);
	}

/*
	Если захотеть прикопаться, то там какой-то неправильный 
	английский) "1 solutions", например...)
 */

	return 0;
}


/*
	Ну и немножко юнит-тестов :)
 */


