//repository.c
#include "repository.h"

bool CreeazaRepository(REPOSITORY_CHELTUIELI_P* Repository){
    if(Repository == NULL)
        return 0;

    REPOSITORY_CHELTUIELI_P repo = (REPOSITORY_CHELTUIELI_P)malloc(sizeof(REPOSITORY_CHELTUIELI));
    if(repo == NULL)
        return 0;

    CHELTUIALA_P* a = (CHELTUIALA_P*)malloc(sizeof(CHELTUIALA)*INIT_SIZE);
    if(a == NULL)
        return 0;

    repo->Array = a;
    repo->Capacitate = INIT_SIZE;
    repo->Lungime = 0;

    *Repository = repo;
    return 1;
}

bool DistrugeRepository(REPOSITORY_CHELTUIELI_P* Repository){
    if(Repository == NULL)
        return 0;

    while(GetLungimeRepository(*Repository)>0)
        if (StergeCheltuialaRepository(*Repository, *((*Repository)->Array[0])) == 0)
            return 0;

    free((*Repository)->Array);
    free(*Repository);

    *Repository = NULL;
    return 1;
}

bool RedimRepository(REPOSITORY_CHELTUIELI_P Repository){
    bool mod = 0;
    if(Repository->Capacitate == Repository->Lungime) {
        Repository->Capacitate = Repository->Capacitate * 2;
        mod = 1;
    }
    else if(Repository->Capacitate > INIT_SIZE && Repository->Capacitate / Repository->Lungime > 2){
        Repository->Capacitate = Repository->Capacitate/2;
        mod = 1;
    }
    if(mod){
        CHELTUIALA_P* a = (CHELTUIALA_P*)malloc(sizeof(CHELTUIALA*)*Repository->Capacitate);
        if(a == NULL)
            return 0;
        for(int i=0; i< Repository->Lungime; i++)
            a[i] = Repository->Array[i];
        free(Repository->Array);
        Repository->Array = a;
    }
    return 1;
}

int GetLungimeRepository(REPOSITORY_CHELTUIELI_P Repository){
    return (*Repository).Lungime;
}

bool GetAll(REPOSITORY_CHELTUIELI_P Repository, CHELTUIALA_P* Array){
    if(Repository == NULL || Array == NULL)
        return 0;

    int len = GetLungimeRepository(Repository);
    CHELTUIALA_P a = (CHELTUIALA_P)malloc(sizeof(CHELTUIALA)*len);
    if(a == NULL)
        return 0;

    for(int i=0; i<len;i++)
        a[i]=*(Repository->Array[i]);

    *Array = a;
    return 1;
}

bool AdaugaCheltuialaRepository(REPOSITORY_CHELTUIELI_P Repository, CHELTUIALA_P Cheltuiala){
    if(Repository == NULL || Cheltuiala == NULL)
        return 0;

    RedimRepository(Repository);
    Repository->Array[Repository->Lungime] = Cheltuiala;
    Repository->Lungime +=1;
    return 1;
}


bool StergeCheltuialaRepository(REPOSITORY_CHELTUIELI_P Repository, CHELTUIALA Cheltuiala){
    bool succes = 0;
    for(int i=0;i<Repository->Lungime;i++){
        if(CheltuieliEgale(*(Repository->Array[i]), Cheltuiala)){
            DistrugeCheltuiala(&(Repository->Array[i]));
            for(int j=i;j<Repository->Lungime-1;j++)
                Repository->Array[j]=Repository->Array[j+1];
        }
        succes = 1;
        Repository->Lungime -=1;
        //break;
    }
    RedimRepository(Repository);
    return succes;
}


bool ModificaCheltuialaRepository(REPOSITORY_CHELTUIELI_P Repository, CHELTUIALA_P Cheltuiala){
    if(Repository == NULL || Cheltuiala == NULL)
        return 0;

    int poz = CautaCheltuialaRepository(Repository, *Cheltuiala);

    if(poz==-1)
        return 0;

    SetSuma(Repository->Array[poz], GetSuma(*Cheltuiala));
    SetTip(Repository->Array[poz], GetTip(*Cheltuiala));
    return 1;
}

int CautaCheltuialaRepository(REPOSITORY_CHELTUIELI_P Repository, CHELTUIALA Cheltuiala){
    for(int i=0;i<Repository->Lungime;i++)
        if(CheltuieliEgale(*(Repository->Array[i]), Cheltuiala))
            return i;
    return -1;
}



