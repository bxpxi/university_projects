#include <iostream>
#include <fstream>
#include <queue>

#define infinit 1000

using namespace std;

ifstream f1("graf.txt");

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

void problema1(){
    int lista_adiacenta[100][100];
    int frecventa;
    int n; //nr noduri
    int x, y; //pentru citirea muchiilor

    //citire din fisier
    f1>>n;
    while(f1>>x>>y){
        lista_adiacenta[x][0]++;
        frecventa = lista_adiacenta[x][0];
        lista_adiacenta[x][frecventa] = y;
    }

    f1.close();

    //citire varf sursa de la tastatura
    int vf;
    cout<<"Introduceti varful sursa: ";
    cin>>vf;

    Moore(lista_adiacenta, n, vf);

    //afisare
    for(int i=1;i<=n;i++){
        if(lungime[i]!=infinit){
            cout<<"Lungimea drumului minim intre "<<vf<<" si "<<i<<" este: "<<lungime[i]<<'\n';
            cout<<"Drumul este: \n";
            Drum_Moore(i);
            cout<<'\n';
        }
        if(lungime[i] == infinit){
            cout<<"Nu exista drum intre "<<vf<<" si "<<i<<'\n';
        }
    }
}

int main(){
    problema1();
    return 0;
}
