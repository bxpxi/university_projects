#include <iostream>
#include <fstream>
#include <queue>

#define infinit 1000

using namespace std;

ifstream f2("graf2.in");

int lungime[100];
int parinte[100];

void Moore(int l[100][100], int n, int u){
    int x, y;

    for(int i=1;i<=n;i++){
        lungime[i] = infinit;
    }
    lungime[u] = 0;

    queue<int>coada;
    coada.push(u);

    while(!coada.empty()){
        x=coada.front();
        coada.pop();

        for(int y=1;y<=l[x][0];y++){
            if(lungime[l[x][y]] == infinit){
                parinte[l[x][y]] = x;
                lungime[l[x][y]] = lungime[x] + 1;
                coada.push(l[x][y]);
            }
        }
    }
}

void Drum_Moore(int vf){
    int dim = lungime[vf];
    int drum[100];
    drum[dim] = vf;

    while(dim){
        dim--;
        drum[dim] = parinte[drum[dim+1]];
    }

    for(int i=0;i<lungime[vf];i++){
        cout<<drum[i]<<" ";
    }
    cout<<drum[lungime[vf]];
}

void problema2(){
    int inchidere_tranzitiva[100][100]={0};
    int lista_adiacenta[100][100];
    int frecventa;
    int n;
    int x, y;

    f2>>n;
    while(f2>>x>>y){
        lista_adiacenta[x][0]++;
        frecventa = lista_adiacenta[x][0];
        lista_adiacenta[x][frecventa] = y;
    }

    f2.close();

    for(int i=1;i<=n;i++){
        Moore(lista_adiacenta, n, i);
        for(int j=1;j<=n;j++){
            if(lungime[j]!=infinit && lungime[j]!=0){
                inchidere_tranzitiva[i][j] = 1;
            }
        }
    }

    cout<<"Inchiderea tranzitiva a grafului este: \n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<inchidere_tranzitiva[i][j]<<' ';
        }
        cout<<'\n';
    }
}

int main(){
    problema2();
    return 0;
}
