#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

ifstream fin("graf5.in");

int n, m, timp;
vector<int>Graf[101];

struct varf{
    char culoare[10];
    int parinte;
    int timp_descoperire;
    int timp_finalizare;
}v[101];

void DFS_VISIT(int nod){
    timp++;
    v[nod].timp_descoperire = timp;
    strcpy(v[nod].culoare, "gri");
    for(size_t i=0; i < Graf[nod].size(); i++){
        int vecin = Graf[nod][i];
        if(strcmp(v[vecin].culoare, "alb") == 0){
            v[vecin].parinte = nod;
            DFS_VISIT(vecin);
        }
    }
    strcpy(v[nod].culoare, "negru");
    timp++;
    v[nod].timp_finalizare = timp;
}

void DFS(){
    for(int i=1; i<=n; i++){
        strcpy(v[i].culoare, "alb");
        v[i].parinte = -1;
    }

    timp = 0;

    for(int i=1; i<=n; i++){
        int tmp = timp + 1;
        if(strcmp(v[i].culoare, "alb") == 0){
            DFS_VISIT(i);
        }
        if(tmp != timp+1){
            for(int j=1; j<=n; j++){
                if(v[j].timp_descoperire >= tmp && v[j].timp_finalizare <= timp){
                    cout<<j<<" ";
                }
            }
            cout<<"\n";
        }
    }
}

int main(){
    fin>>n>>m;
    int a, b;
    for(int i=1; i<=m; i++){
        fin>>a>>b;
        Graf[a].push_back(b);
    }
    cout<<"Nodurile sunt descoperite in urmatoarea ordine: ";
    DFS();
    return 0;
}
