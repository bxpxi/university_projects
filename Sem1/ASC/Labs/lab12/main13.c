#include <stdio.h>

void concatenare(char a[],char b[],char c[]);

char a[101],b[101],c[101],d[101];

int main()
{
    scanf("%s",&a);
    scanf("%s",&b);

    concatenare(a,b,c);
    printf("\n%s",c);
    concatenare(b,a,d);
    printf("\n%s",d);
	return 0;
}