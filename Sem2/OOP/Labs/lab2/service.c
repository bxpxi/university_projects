//service.c
#include "service.h"

bool CreeazaService(SERVICE_CHELTUIELI_P* Service, REPOSITORY_CHELTUIELI_P Repository, Validator ValidatorC){
    if(Service == NULL || Repository == NULL || ValidatorC == NULL) {
        if (Repository != NULL)
            DistrugeRepository(&Repository);
        return 0;
    }

    SERVICE_CHELTUIELI_P s = (SERVICE_CHELTUIELI_P)malloc(sizeof(SERVICE_CHELTUIELI));
    s->Repository=Repository;
    s->ValidatorCheltuiala = ValidatorC;

    *Service =s;
    return 1;
}

bool DistrugeService(SERVICE_CHELTUIELI_P* Service){
    if(Service == NULL)
        return 0;

    REPOSITORY_CHELTUIELI_P repo = (*Service)->Repository;
    DistrugeRepository(&repo);
    free(*Service);
    *Service = NULL;
    return 1;
}

bool AdaugaCheltuialaService(SERVICE_CHELTUIELI_P Service, int Nr_ap, float Suma, char* Tip, char* erori){
    if(erori == NULL)
        return 0;
    erori[0]='\0';

    if(Service == NULL){
        //strcat(erori, "Parametri invalizi!\n");
        return 0;
    }

    CHELTUIALA_P Cheltuiala;
    CreeazaCheltuiala(&Cheltuiala, Nr_ap, Suma, Tip);
    if(Service->ValidatorCheltuiala(*Cheltuiala, erori) == 0){
        DistrugeCheltuiala(&Cheltuiala);
        return 0;
    }
    AdaugaCheltuialaRepository(Service->Repository, Cheltuiala);
    return 1;
}

bool StergeCheltuialaService(SERVICE_CHELTUIELI_P Service, int Nr_ap, char* erori){
    if(erori == NULL)
        return 0;
    erori[0]='\0';

    if(Service == NULL)
        return 0;

    CHELTUIALA_P Cheltuiala;
    CreeazaCheltuiala(&Cheltuiala, Nr_ap, 0, "");
    CautaCheltuialaRepository(Service->Repository, *Cheltuiala);

    bool succes = StergeCheltuialaRepository(Service->Repository, *Cheltuiala);
    if(!succes){
        strcat(erori, "Cheltuiala nu exista!\n");
        return 0;
    }
    DistrugeCheltuiala(&Cheltuiala);
    return 1;
}

bool ModificaCheltuialaService(SERVICE_CHELTUIELI_P Service, int Nr_ap, float Suma, char* Tip, char* erori){
    if(erori == NULL)
        return 0;
    erori[0]='\0';

    if(Service == NULL)
        return 0;

    CHELTUIALA_P Cheltuiala;
    CreeazaCheltuiala(&Cheltuiala, Nr_ap, Suma, Tip);
    if(Service->ValidatorCheltuiala(*Cheltuiala, erori) == 0){
        strcat(erori, "Parametri invalizi!\n");
        DistrugeCheltuiala(&Cheltuiala);
        return 0;
    }
    bool succes = ModificaCheltuialaRepository(Service->Repository, Cheltuiala);
    if(!succes)
    {
        strcat(erori, "Cheltuiala nu poate fi modificata\n");
        DistrugeCheltuiala(&Cheltuiala);
        return 0;
    }
    DistrugeCheltuiala(&Cheltuiala);
    return 1;
}

bool GetAllService(SERVICE_CHELTUIELI_P Service, int optiune, char filtru[], CHELTUIALA_P* Array, int* len, char* erori){
    if(erori == NULL)
        return 0;
    erori[0]='\0';

    if(Service == NULL)
        return 0;

    int lenRepo = GetLungimeRepository(Service->Repository);
    if(lenRepo == 0){
        strcat(erori, "Nu  exista cheltuieli in bloc.\n");
        return 0;
    }

    CHELTUIALA_P a, b;
    b = (CHELTUIALA_P)malloc(sizeof(CHELTUIALA)*lenRepo);
    GetAll(Service->Repository, &a);

    if(optiune == 0) {
        *len = lenRepo;
        *Array = a;
    }
    else if(optiune == 1){
        *len = 0;
        int nr_ap = strtol(filtru, NULL, 10);

        if(nr_ap == 0){
            strcat(erori, "Nu se pot afisa cheltuieli cu filtrul dat\n");
            return 0;
        }
        for(int i=0; i<lenRepo;i++)
            if(GetNr_ap(a[i]) == nr_ap){
                b[*len] = a[i];
                ++(*len);
            }
        *Array = b;
    }
    else if(optiune == 2){
        *len = 0;
        float suma = (float)strtod(filtru, NULL);
        if(suma == 0){
            strcat(erori, "Nu se pot afisa cheltuieli cu filtrul dat\n");
            return 0;
        }
        for(int i=0;i<lenRepo;i++)
            if(GetSuma(a[i]) == suma){
                b[*len] = a[i];
                ++(*len);
            }
        *Array = b;
    }
    else if(optiune == 3){
        *len = 0;
        for(int i=0; i<lenRepo; i++)
            if(GetTip(a[i]) == filtru){
                b[*len] = a[i];
                ++(*len);
            }
        *Array = b;
    }
    else{
        free(a);
        free(b);
        strcat(erori, "Optiune invalida\n");
        return 0;
    }

    if(*len == 0){
        free(a);
        free(b);
        strcat(erori, "Nu exista cheltuieli cu filtrul dat\n");
        return 0;
    }

    if(optiune!=0)
        free(a);
    else
        free(b);

    return 1;
}

bool Sorteaza(SERVICE_CHELTUIELI_P Service, int optiune, CHELTUIALA_P* Array, char* erori){
    if(erori == NULL)
        return 0;
    erori[0]='\0';

    if(Service == NULL || Array == NULL){
        strcat(erori, "Parametri necorespunzatori\n");
        return 0;
    }

    int len = GetLungimeRepository(Service->Repository);
    GetAll(Service->Repository, Array);
    if(len<=0){
        strcat(erori, "Nu exista sufieciente cheltuieli pentru a fi sortate\n");
        return 0;
    }

    if(optiune==0)
        BubbleSort(*Array, ComparaCrescatorSuma,  len);
        //SelectionSort(*Array, ComparaCrescatorSuma,  len);
    else if(optiune==1)
        BubbleSort(*Array, ComparaDescrescatorSuma,  len);
        //SelectionSort(*Array, ComparaDescrescatorSuma,  len);
    else if(optiune==2)
        BubbleSort(*Array, ComparaCrescatorTip,  len);
        //SelectionSort(*Array, ComparaCrescatorTip,  len);
    else if(optiune==3)
        BubbleSort(*Array, ComparaDescrescatorTip,  len);
        //SelectionSort(*Array, ComparaDescrescatorTip,  len);
    else{
        strcat(erori, "Optiune invalida!\n");
        return 0;
    }
    return 1;
}