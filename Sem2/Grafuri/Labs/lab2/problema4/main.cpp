#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>

#define infinit (1 << 30)

using namespace std;

ifstream fin("graf4.in");

vector<int>Graf[101];
queue<int>coada;
int n, m, nod_sursa;

struct varf{
    char culoare[10];
    int parinte;
    int distanta;
}v[101];

void BFS(int s){
    for(int i=1; i<=n; i++){
        strcpy(v[i].culoare, "alb");
        v[i].distanta = infinit;
        v[i].parinte = -1;
    }
    cout<<"Varfurile descoperite sunt: ";
    strcpy(v[s].culoare, "gri");
    v[s].distanta = 0;
    v[s].parinte = -1;
    coada.push(s);
    while(!coada.empty()){
        int nod = coada.front();
        coada.pop();
        for(size_t i=0; i< Graf[nod].size(); i++){
            int vecin = Graf[nod][i];
            if(strcmp(v[vecin].culoare, "alb") == 0){
                cout<<" "<<vecin;
                strcpy(v[vecin].culoare, "gri");
                v[vecin].distanta = v[nod].distanta + 1;
                v[vecin].parinte = nod;
                coada.push(vecin);
            }
        }
        strcpy(v[nod].culoare, "negru");
    }
}

int main(){
    fin>>n>>m;
    int a, b;
    for(int i=1; i<=m; i++){
        fin>>a>>b;
        Graf[a].push_back(b);
    }
    cout<<"Nodul sursa: ";
    cin>>nod_sursa;
    BFS(nod_sursa);
    cout<<"\nDistantele fata de varful "<<nod_sursa<<'\n';
    for(int i=1; i<=n; i++){
        cout<<i<<": ";
        if(v[i].distanta == infinit)
            cout<<'-';
        else
            cout<<v[i].distanta;
        cout<<'\n';
    }
    return 0;
}

