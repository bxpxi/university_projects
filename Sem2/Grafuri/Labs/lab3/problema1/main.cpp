#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

const int NMAX = 100005;
int D[NMAX];
int n, m , start;
vector <pair <int, int>> G[NMAX];
const int oo = 1<<30;
bool InCoada[NMAX];

struct compara {
    bool operator()(int x, int y)
    {
        return D[x] > D[y];
    }
};

priority_queue <int, vector <int>, compara> Coada;

void Citeste(){
    fin>>n>>m>>start;
    for(int i=1;i<=m;i++){
        int x, y, c;
        fin>>x>>y>>c;
        G[x].push_back(make_pair(y, c));
    }
}

void Dijkstra(int start){
    //initializare distante cu INFINIT
    for(int i=0;i<n;i++)
        D[i]=oo;

    D[start]=0;

    //adaugare nod start in coada si il marcam in vectorul InCoada
    Coada.push(start);
    InCoada[start]=true;

    while(!Coada.empty()){
        //scoatem un nod din coada
        int nodCurent = Coada.top();
        Coada.pop();

        InCoada[nodCurent] = false;

    }
}
