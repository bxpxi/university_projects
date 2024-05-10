#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("in.txt");

int infinita = 9999;
int main() {
    int a[100][100]={0}, n, ok, grad, contor, distanta[100][100]={0};

    int i, j;
    fin>>n;
    for(int k=0; k<n; k++){
        fin>>i>>j;
        a[i-1][j-1]=1;
        a[j-1][i-1]=1;
    }

    for (int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout<<a[i][j]<<" ";
        cout<<'\n';
    }

    for (int i=0; i<n; i++){
        cout<<i+1<<" are varfurile: ";
        for(int j=0; j<n; j++)
            if (a[i][j]!=0)
                cout<<j+1<<" ";
        cout<<'\n';
    }

    cout<<"Varfurile izolate sunt: ";
    for (int i=0; i<n; i++){
        ok = 1;
        for (int j=0; j<n; j++)
            if (a[i][j]==1)
                ok = 0;
        if (ok == 1)
            cout<<i+1<<", ";
    }

    cout<<'\n';

    ok = 1;
    grad = 0;
    for (int i=0; i<n; i++)
        grad = grad + a[i][0];

    for (int i=1; i<n; i++){
        contor = 0;
        for (int j=0; j<n; j++)
            if (a[i][j]==1)
                contor++;
        if(contor!=grad) {
            ok = 0;
            break;
        }
    }
    if (ok==0)
        cout<<"Graful nu este regulat!"<<'\n';
    else
        cout<<"Graful este regulat!"<<'\n';


    int conex = 1;
    for(int i=0; i<n; i++){
        ok = 0;
        for (int j=0; j<n; j++)
            if(a[i][j]==1)
                ok = 1;
        if (ok==0)
            conex = 0;
    }
    if(conex==0)
        cout<<"Graful nu este conex!"<<'\n';
    else
        cout<<"Graful este conex!"<<'\n';


    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (i==j)
                distanta[i][j]=0;
            else if (a[i][j]==1)
                distanta[i][j]=1;
            else
                distanta[i][j] = infinita;


    for (int k=0; k<n; k++)
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                if (distanta[i][k]+distanta[k][j]<distanta[i][j])
                    distanta[i][j]=distanta[i][k]+distanta[k][j];
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++)
            if (distanta[i][j] == infinita)
                cout<<0;
            else
                cout<<distanta[i][j]<<" ";
        cout<<'\n';
    }
    return 0;


}
