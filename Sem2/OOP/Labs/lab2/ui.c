//ui.c
#include "ui.h"

void PrintCheltuiala(CHELTUIALA Cheltuiala){
    printf("\n [Nr apartament: %d; Suma: %.2f; Tip: %s] \n", Cheltuiala.Nr_ap, Cheltuiala.Suma, Cheltuiala.Tip);
}

bool CreeazaUI(UI_P* Ui, SERVICE_CHELTUIELI_P Service){
    if(Ui == NULL || Service == NULL)
        return 0;

    UI_P console = (UI_P)malloc(sizeof(UI));
    console->Service = Service;
    *Ui = console;

    return 1;
}

bool DistrugeUI(UI_P* Ui){
    if(Ui == NULL)
        return 0;

    SERVICE_CHELTUIELI_P service = (*Ui)->Service;
    if(DistrugeService(&service) == 0)
        return 0;
    free(*Ui);

    return 1;
}

int CitesteCmd(){
    printf("\n************\n"
                  "Comenzi disponibile:\n"
                  "0 - Exit\n"
                  "1 - Adauga cheltuiala\n"
                  "2 - Sterge cheltuiala\n"
                  "3 - Modifica cheltuiala\n"
                  "4 - Vizualizare cheltuieli\n"
                  "5 - Sortare cheltuieli\n"
                  "************\n"
                  "Comanda ta este: ");
    int cmd;
    scanf("%d", &cmd);
    return cmd;
}

bool AdaugaCheltuialaUI(UI_P Ui, char* erori){
    erori[0]='\0';
    int nr_ap;
    float suma;
    char* tip;
    bool succes;

    tip = (char*)malloc(sizeof(char)*INPUT_SIZE);

    printf("Adauga cheltuiala(nr apartament, suma, tip):\n");
    scanf("%d %f %s", &nr_ap, &suma, tip);
    succes= AdaugaCheltuialaService(Ui->Service, nr_ap, suma, tip, erori);
    free(tip);
    if(!succes)
        strcat(erori, "Adaugare esuata!\n");
    return succes;
}

bool StergeCheltuialaUI(UI_P Ui, char* erori){
    erori[0]='\0';
    int nr_ap;
    bool succes;

    printf("Sterge apartamentul cu numarul:\n");
    scanf("%d", &nr_ap);

    succes= StergeCheltuialaService(Ui->Service, nr_ap, erori);

    if(!succes)
        strcat(erori, "Stergere esuata!\n");

    return succes;
}

bool ModificaCheltuialaUI(UI_P Ui, char* erori){
    erori[0]='\0';
    char nr_ap[3];
    char suma[5];
    char *tip;
    int nr_apINT;
    float sumaFLOAT;
    bool succes;

    tip = (char*)malloc(sizeof(char)*INPUT_SIZE);
    printf("Modifica cheltuiala(nr_apartament, suma, tip):\n");
    scanf("%s %s %s", nr_ap, suma, tip);
    nr_apINT = strtol(nr_ap, NULL, 10);
    sumaFLOAT = (float)strtod(suma, NULL);

    succes = ModificaCheltuialaService(Ui->Service, nr_apINT, sumaFLOAT, tip, erori);

    free(tip);

    if(!succes)
        strcat(erori, "Modificare esuata!\n");

    return succes;
}

bool VizualizeazaUI(UI_P Ui, char* erori){
    erori[0]='\0';
    CHELTUIALA_P Array;
    printf("0. Vizualizeaza tot\n"
                  "1. Vizualizeaza dupa nr apartament\n"
                  "2. Vizualizeaza dupa suma\n"
                  "3. Vizualizeaza dupa tip\n");
    int cmd;
    char filtru[10]="";
    scanf("%d", &cmd);
    int len;
    if(cmd == 1){
        printf("Numar apartament: ");
        scanf("%s", filtru);
    }
    else if(cmd == 2){
        printf("Suma: ");
        scanf("%s", filtru);
    }
    else if(cmd == 3){
        printf("Tip: ");
        scanf("%s", filtru);
    }

    bool succes = GetAllService(Ui->Service, cmd, filtru, &Array, &len, erori);

    if(!succes) {
        strcat(erori, "Vizualizare esuata!\n");
        return 0;
    }

    for(int i=0;i<len;i++)
        PrintCheltuiala(Array[i]);

    free(Array);
    return 1;
}

bool SorteazaUi(UI_P Ui, char* erori) {
    erori[0] = '\0';
    CHELTUIALA_P Array;
    printf("Sorteaza:\n"
           "0.Crescator dupa suma\n"
           "1.Descrescator dupa suma\n"
           "2.Crescator dupa tip\n"
           "3.Descrescator dupa tip\n"
           "Optiunea ta este: ");
    int cmd;
    scanf ("%d", &cmd);
    int len = GetLungimeRepository(Ui->Service->Repository);
    bool success = Sorteaza(Ui->Service, cmd, &Array, erori);
    if (!success) {
        strcat(erori, "Sortare esuata!\n");
        return 0;
    }

    for (int i = 0; i < len; i++)
        PrintCheltuiala(Array[i]);
    free(Array);
    return 1;
}

void runUI(UI_P Ui) {
    if (Ui == NULL)
        return;
    char *erori = (char*) malloc (100 * sizeof(char));
    bool exit = 0;
    while(!exit) {
        int cmd = CitesteCmd();
        bool success = 1;
        if (cmd == 0)
            exit = 1;
        else if (cmd == 1)
            success = AdaugaCheltuialaUI(Ui, erori);
        else if (cmd == 2)
            success = StergeCheltuialaUI(Ui, erori);
        else if (cmd == 3)
            success = ModificaCheltuialaUI(Ui, erori);
        else if (cmd == 4)
            success = VizualizeazaUI(Ui, erori);
        else if (cmd == 5)
            success = SorteazaUi(Ui, erori);
        else
            printf("Comanda invalida!\n");

        if (!success) {
            printf("%s", erori);
        }
    }
    free(erori);
    printf("Iesire din aplicatie..");
}