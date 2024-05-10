#include <stdio.h>

/*12. Determina valoarea x^n (x este un numar real dat, n este un numar natural
    dat), utilizand operatii de inmultire si de ridicare la patrat.
*/

int calculeaza(int x, int n)
{
    /*
     * Functie care calculeaza x^n
     * input: x, n
     * type input: int
     * output: rez
     * type output: int
     */
    int rez=1;
    for(int i=1;i<=n;i++)
        rez=rez*x;
    return rez;
}

int produs_numere(int produs)
{
    /*
     Functia calculeaza produsul a numerelor introduse
     input : produs
     type input : int
     output: produs
     type output: produs
     */
    int numar;
    printf("%s","Introduceti numerele (0 pentru oprire): \n");
    do {
        scanf("%d", &numar);
        if(numar != 0)
            produs = produs * numar;
    }while(numar != 0);

    return produs;
}

int cifre_zero(int rezultat)
{
    /*
     * Functia calculeaza numarul de zero-uri al unui numar
     * input: rezultat
     * type input : int
     * output: count
     * type output: int
     */
    int count = 0;
    if (rezultat == 0)
        return 1;
    else
    {
        while(rezultat > 0)
        {
            if(rezultat%10 == 0)
                count++;
            rezultat/=10;
        }
    }
    return count;
}

void meniu()
{
    /*
     * Functie care afiseaza meniul aplicatiei
     */
    printf("MENIU\n");
    printf("1. Calcul 1\n");
    printf("2. Calcul 2\n");
    printf("3. Iesire\n");
}
int main()
{
    int op, x, n;
    meniu();
    printf("Optiune: ");
    scanf("%d",&op);
    while(op!=3)
    {
        if(op==1)
        {
            int produs = 1, rezultat, cifre;
            rezultat = produs_numere(produs);
            cifre = cifre_zero(rezultat);
            printf("Sunt %d cifre de zero.", cifre);
            printf("\n");
        }
        if(op==2)
        {
            printf("Baza: ");
            scanf("%d", &x);
            printf("Exponent: ");
            scanf("%d", &n);
            int rez = calculeaza(x,n);
            printf(" Rezultat: %d", rez);
            printf("\n");
        }
        if(op==3){
            printf("Iesire...");
            break;
        }
        printf("Optiune: ");
        scanf("%d",&op);
    }
    return 0;
}
