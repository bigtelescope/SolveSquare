#include <stdio.h>
#include <stdlib.h>
#include <cfloat>
 
int main()
{
    int a, b, c;   
    int retValue = 0;
    /*do
    {
        printf("before %d\n", retValue);
        retValue = scanf("%lg%lg%lg", &a, &b, &c);
        printf("after %d\n", retValue);
        //continue;
    }
    while(retValue == 3);*/
    while(scanf("%d%d%d", &a, &b, &c) != 3)
        printf("Error\n");
 
    /*if(scanf("%lg%lg%lg", &a, &b, &c) != 3)
    {
        while(fgetc(stdin) != '\n');
        continue;
    }*/
 
 
    return 0;
}
