typedef struct{
    char partenza[20];
    char destinazione[20];
    Data data;
    int postiDisp;
    float costoBiglietto;
} Viaggio;

typedef struct listaViaggi{
    int id;
    Viaggio viaggio;
    struct listaViaggi *next;
} ListaViaggi;

/*

    RICERCA

*/
ListaViaggi* isThere(ListaViaggi* list, int idToSearch){
    if(list != NULL){
        if(list->id == idToSearch)
            return list;
        else
            return isThere(list->next, idToSearch);
    }
    return NULL;
}

int presentiPostiDisp(ListaViaggi* list){
    if(list != NULL){
        if(list->viaggio.postiDisp != 0)
            return 1;
        return presentiPostiDisp(list->next);
    }
    return 0;
}

int presentiViaggi(ListaViaggi* lista){
    if(lista == NULL)
        return 0;
    return 1;
}

void visualizzaViaggi(ListaViaggi* list){
    if(list != NULL){
        printf("%d\t%s\t\t\t%s\t\t\t%d/%d/%d\t\t%d:%d\t\t%.2f\t\t\t%d\n", list->id, list->viaggio.destinazione, list->viaggio.partenza, list->viaggio.data.day, list->viaggio.data.month, list->viaggio.data.year, list->viaggio.data.hour, list->viaggio.data.minute, list->viaggio.costoBiglietto, list->viaggio.postiDisp);
        visualizzaViaggi(list->next);
    }
}

// non visualizza i voli senza posti dsponibili
void visualizzaViaggiAcquisto(ListaViaggi* list){
    if(list != NULL){
        if(list->viaggio.postiDisp > 0)
            printf("%d\t%s\t\t\t%s\t\t\t%d/%d/%d\t\t\t%d:%d\t\t\t%.2f\n", list->id, list->viaggio.destinazione, list->viaggio.partenza, list->viaggio.data.day, list->viaggio.data.month, list->viaggio.data.year, list->viaggio.data.hour, list->viaggio.data.minute, list->viaggio.costoBiglietto);
        visualizzaViaggiAcquisto(list->next);
    }
}

/*

    INSERIMENTI e IMPOSTAZIONE DATI

*/
int maxId(ListaViaggi* list){
    int tempMax = 0;
    while(list != NULL){
        if(list->id > tempMax)
            tempMax = list->id;
        list = list->next;
    }    
    return tempMax;
}

void setDatiViaggio(ListaViaggi* new, Viaggio temp){

    strcpy(new->viaggio.partenza, temp.partenza);
    strcpy(new->viaggio.destinazione, temp.destinazione);

    new->viaggio.data.day = temp.data.day;
    new->viaggio.data.month = temp.data.month;
    new->viaggio.data.year = temp.data.year;
    new->viaggio.data.hour = temp.data.hour;
    new->viaggio.data.minute = temp.data.minute;

    new->viaggio.postiDisp = temp.postiDisp;
    new->viaggio.costoBiglietto = temp.costoBiglietto;
}

ListaViaggi* newViaggio(Viaggio temp, int id){
    ListaViaggi* new = (ListaViaggi*)malloc(sizeof(ListaViaggi));
    setDatiViaggio(new, temp);
    new->id = id;
    return new;
}

void pushViaggio(ListaViaggi** lista, Viaggio temp){
    if(*lista != NULL){
        ListaViaggi *temporaneo;
        if(datecmp((*lista)->viaggio.data, temp.data) > 0){
            temporaneo = newViaggio(temp, maxId(*lista) + 1);
            temporaneo->next = *lista;
            *lista = temporaneo;
        }
        else{
            temporaneo = *lista;
            while(datecmp(temporaneo->viaggio.data, temp.data) < 0){
                if(temporaneo->next == NULL){
                    temporaneo->next = newViaggio(temp, maxId(*lista) + 1);
                    temporaneo->next->next = NULL;
                    break;
                }
                else if(datecmp(temporaneo->next->viaggio.data, temp.data) >= 0){
                    ListaViaggi *succ = temporaneo->next;
                    temporaneo->next = newViaggio(temp, maxId(*lista) + 1);
                    temporaneo->next->next = succ;

                    break;
                }
                else
                    temporaneo = temporaneo->next;
            }
            
        }    
    }
    else{
        *lista = newViaggio(temp, 0);
        (*lista)->next = NULL;
    }
}

void inserisciViaggio(ListaViaggi** viaggi){
    Viaggio temp;

    printf("Inserisci citta' di partenza: ");
    scanf("%s", temp.partenza);
    fflush(stdin);
    printf("Inserisci citta' di destinazione: ");
    scanf("%s", temp.destinazione);
    fflush(stdin);

    printf("Inserisci data di partenza: \n");
    printf("[ANNO]: ");
    do{
        scanf("%d", &temp.data.year);
        fflush(stdin);
    } while (temp.data.year <  getYear());
    // se siamo nell anno corrente non si possono inserire voli in una data precedente
    printf("[MESE]: ");
    if(isCurrentYear(temp.data.year)){
        do{
            scanf("%d", &temp.data.month);
            fflush(stdin);
        } while (temp.data.month > 12 || temp.data.month < getMonth());
    }
    else{
        do{
            scanf("%d", &temp.data.month);
            fflush(stdin);
        } while (temp.data.month > 12 || temp.data.month < 1);
    }
    printf("[GIORNO]: ");
    if(isCurrenyMonth(temp.data.year, temp.data.month)){
        do{
            scanf("%d", &temp.data.day);
            fflush(stdin);
        } while (temp.data.day > 31 || temp.data.day < getDay());
    }
    else{
        do{
            scanf("%d", &temp.data.day);
            fflush(stdin);
        } while (temp.data.day > 31 || temp.data.day < 1);
    }
    
    
    printf("Inserisci orario di partenza: \n");
    printf("[ORA]: ");
    if(isCurrentDay(temp.data.year, temp.data.month, temp.data.day)){   
        do{
            scanf("%d", &temp.data.hour);
            fflush(stdin);
        } while (temp.data.hour <  getHour() || temp.data.hour > 23);
    }
    else{
        do{
            scanf("%d", &temp.data.hour);
            fflush(stdin);
        } while (temp.data.hour < 0 || temp.data.hour > 23);
    }
    printf("[MINUTO]");
    if(isCurrentHour(temp.data.year, temp.data.month, temp.data.day, temp.data.hour)){
        do{
            scanf("%d", &temp.data.minute);
            fflush(stdin);
        } while (temp.data.minute <=  getMinute() || temp.data.minute > 59);
    }
    else{
        do{
            scanf("%d", &temp.data.minute);
            fflush(stdin);
        } while (temp.data.minute < 0 || temp.data.minute > 59);
    }
    printf("Inserisci costo biglietto: ");
    scanf("%f", &temp.costoBiglietto);
    fflush(stdin);
    printf("Inserisci posti disponibili [MAX 300]: ");
    do{
        scanf("%d", &temp.postiDisp);
    } while (temp.postiDisp > 300);
    fflush(stdin);

    pushViaggio(viaggi, temp);
}

/*

    RIMOZIONI

*/
//rimuovere (quando acquisti o quando si vuole)
void popInOgniPosizione(ListaViaggi** list, ListaViaggi* temp){
    if(*list == temp){
        *list = (*list)->next;
        free(temp);
    }
    else if((*list)->next == NULL){
        (*list)->next = NULL;
        free(temp);
    }
    else{
        ListaViaggi *tempToMove = *list;
        while(tempToMove->next != temp){
            tempToMove = tempToMove->next;
        }
        tempToMove->next = tempToMove->next->next;
        free(temp);
    }
}

void rimuoviViaggio(ListaViaggi** list, int idToRemove){
    ListaViaggi *temp = *list;
    while (temp != NULL)
    {
        if(temp->id == idToRemove){
            popInOgniPosizione(list, temp);
            break;
        }
        temp = temp->next;
    }
}

void svuotaLista(ListaViaggi** list){
    ListaViaggi *temp = *list;
    ListaViaggi* toDelete;
    while (temp != NULL){
        toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }
    *list = NULL;
}

/*

    FA "PARTIRE GLI AEREI"

*/

// non cempletata in tempo
// void takeOff(ListaViaggi** list){
//     ListaViaggi *temp = *list;

//     while(temp != NULL){
//         printf(":::%d:::\n", temp->id);
//         if(datecmp(temp->viaggio.data, getData()) >= 0){
//             rimuoviViaggio(list, temp->id);
            
//         }
        
//     }
// }

/*

    GESTIONE FILE

*/
void downloadViaggi(ListaViaggi** lista, char* fileName){
    FILE *fpin = fopen(fileName, "rb");
    Viaggio temp;
    while(fread(&temp, sizeof(Viaggio), 1, fpin)){
        pushViaggio(lista, temp);
        //printf("nome: %s conome: %s anni:%d\n", temp.name, temp.surname, temp.year);
    }
    fclose(fpin);
}

void uploadViaggi(ListaViaggi* lista, char* fileName){
    FILE *fpout = fopen(fileName, "wb");
    while(lista != NULL){
        ListaViaggi *temp2 = lista;
        fwrite(&lista->viaggio, sizeof(Viaggio), 1, fpout);
        lista = lista->next;
        free(temp2);
    }
    fclose(fpout);
}