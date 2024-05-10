#include <stdio.h>

void concatenare(char a[],char b[],char c[]);

int main()
{
    char a[101]="ana are 10 mere si 3 pere"
    char b[101]="maria are 3 mere si 10 pere"
    
    char c[201]=""
    char d[202]=""
    concatenare(a,b,c);
    concatenare(b,a,d);
    
    printf("%s\n",c);
    printf("%s\n",d);
	return 0;
}