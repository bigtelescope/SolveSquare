#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <cfloat>
#include <cmath>

/*
	Глобальные мысли:

	0. Чтобы не писать каждый раз об одной и той же заметке, я
	пропишу их наверху и буду в скобочках квадратных ссылаться. 
	Если ты не против, конечно :)

	1. Можно не скупиться на '\n' в коде, чтобы разбивать его на 
	логические куски, так будет читабельнее. Пример - вызвал функцию
	и сразу же проверил ее возвращаемое значение. Весь этот кусочек
	написан примерно слитно, а от остального кода отделен пустыми
	строчками. Выглядит вполне себе.

	2. Когда в цикле или ифе всего одна инструкция, обычно скобочки
	не ставят, они только мешают читабельности. Ну и когда условие
	и так короткое довольно, то есть смысл писать в той же строке.
	Не стоит, конечно, перегибать с этим и писать все в одну строку
	при любой возможности, но, скажем, строка <else return 0;> - 
	очень даже норм.

	3. Неинициализированные переменные. Конечно, такое происходит
	и в коде профессионалов, но это не особо круто. Иногда можно 
	реально забыть проинициализировать и будут дикие результаты,
	сложно искать косяк. Посему лучше всего инициализировать нулями,
	нулевыми указателями, минус единичками, inf'ами и прочим, в 
	зависимости от ситуации. 

	4. "Магические цифры" в коде - не по фен-шую. Лучше давать им имена.
	В С это будут дефайны, в С++ можно юзать const int глобальные.
	В частности, есть задефайненные EXIT_SUCCESS и EXIT_FAILURE, равные
	0 и 1. Все по-линуховски)
 */

//----------------------------------------------------------------

int SolveSquare(double a, double b, double c, double * p1, double * p2);			// Calculating solutions of the equation
int SolveLinear(double b, double c, double * p1, int solves);						// Calculating solution of the linear equation
void Input(double * a, double *b, double * c);										// Input of coefficients

//----------------------------------------------------------------

// Что-то мне подсказывает, что очень мудреная иерархия ифов...
// С ходу и не скажешь даже, что и где вызывается, в нужных ли
// местах. Как мне кажется, лучше как-то так.
//
// И p1 и p2 не отражают сути. Лучше честно x1 и x2.
int SolveSquare(double a, double b, double c, double * p1, double * p2)
{
	assert(std::isfinite(a));
	assert(std::isfinite(b));
	assert(std::isfinite(c));
	assert(p1 != NULL);
	assert(p2 != NULL);
	
	// Можно случайно затереть корень, если передать один указатель
	// в оба параметра. Неприятно получится.
	assert(p1 != p2);

	int n_roots = 0;

	if (a == 0)		// Particular situation: linear
	{
		// Вполне логично тут потребовать от SolveLinear 
		// самостоятельной обработки всех случаев, связанных
		// со стремными вводами.  
		n_roots = SolveLinear(b, c, p1);
	}
	else			 // Full square equation
	{
		double d = b*b - 4*a*c;

		if (d < 0)
		{
			// 0 корней
		}
		else if (d == 0)
		{
			// Считаем единственный корень
		}
		else
		{
			// Считаем корни по формулкам
		}
	}

	return solves;
}


// А зачем тут solves? Функция только меняет значение копии "настоящего"
// solves и возвращает значение этой копии. Достаточно просто локальной
// переменной
int SolveLinear(double b, double c, double * p1, int solves)
{
	// assert'ы - это хорошо, но если собирать проект с ключиком
	// release, а не debug, то они пропадут, а вызывать функцию с
	// b == 0 вроде как легально. Так что лучше все-таки сделать
	// проверку через if, а не assert'ом срубать прогу
	assert(b != 0);

//	[1]

	solves = 1;
	*p1 = -c/b;
	if(c == 0)	*p1 = 0;
	
//	[1]
	
	return solves;
}

// В принципе, тут функция действительно делает войдовые вещи,
// но войдовые функции - не по феншую. Пусть лучше возвращает 
// int, где скажет, сколько она прочитала, или сколько раз 
// пользователь ошибся, или код успешного завершения. Она знает
// достаточно много, чтобы этим поделиться с остальными)
void Input(double * a, double * b, double * c)
{
	while(scanf("%lg%lg%lg", a, b, c) != 3)
	{
		while(getchar() != '\n');
		printf("Incorrect value\nPlease, enter numbers: ");
	}
}

int main()
{
	printf("#Calculating if a square equation\n");
	printf("#Enter numbers:\n");

//	[3]
	double a, b, c;	
//	[3]																// initialization of coefficients
	double x1, x2;																	// initialization of solutions

// В принципе, конкретно тут неважно, но лучше проверять
// возвращаемые значения	
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

		case INT_MAX:
			printf("Endless number of solutions\nAny number is a solution\n");
			break;

		default :
			// Не слишком информативно. Можно что-то типа
			// "Unexpected error: nSolves = %d, a = %lg, b = %lg, c = %lg\n."
			// "Returning with error.\n"
			// И да, это в некотором роде аварийное завершение, посему
			// после printf'а надо бы впендюрить сразу <return ERROR;>
			printf("Invalid value\n");
	}

//	[4]
	return 0;
}
