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

/*
    Funzione che, se presente un viaggio con l'ID corrispondente, ne comunica l'indirizzo.

    @param ListaViaggi* Indirizzo della testa della lista
    @param int ID del viaggio da cercare

    @return Indirizzo del viaggio se presente, NULL se assente
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

/*
    Funzione che comunica se, tra tutti i viaggi nella lista, almeno uno ha almeno un posto disponibile.

    @param ListaViaggi* Indirizzo della testa della lista

    @return 0 se non presenti posti, 1 se presenti
*/
int presentiPostiDisp(ListaViaggi* list){
    if(list != NULL){
        if(list->viaggio.postiDisp != 0)
            return 1;
        return presentiPostiDisp(list->next);
    }
    return 0;
}

/*
    Funzione che comunica se ci sono oppure no viaggi.

    @param ListaViaggi* Indirizzo della testa della lista

    @return 0 se non ci sono viaggi, 1 se ci sono
*/
int presentiViaggi(ListaViaggi* lista){
    if(lista == NULL)
        return 0;
    return 1;
}

/*
    Funzione che visualizza tutti i viaggi presenti nella lista.

    @param ListaViaggi* Indirizzo della testa della lista
*/
void visualizzaViaggi(ListaViaggi* list){
    if(list != NULL){
        printf("%d\t%s\t\t\t%s\t\t\t%d/%d/%d\t\t%d:%d\t\t%.2f\t\t\t%d\n", list->id, list->viaggio.destinazione, list->viaggio.partenza, list->viaggio.data.day, list->viaggio.data.month, list->viaggio.data.year, list->viaggio.data.hour, list->viaggio.data.minute, list->viaggio.costoBiglietto, list->viaggio.postiDisp);
        visualizzaViaggi(list->next);
    }
}

/*
    Funzione che visualizza tutti i viaggi presenti nella lista con almeno 1 posto disponibile.

    @param ListaViaggi* Indirizzo della testa della lista
*/
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

/*
    Funzione che calcola l'ID massimo presente in una lista.

    @param ListaViaggi* Indirizzo della testa della lista

    @return int ID massimo presente nella lista
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

/*
    Funzione che imposta i dati del viaggio.

    @param ListaViaggi* Indirizzo del nodo di cui impostare i dati
    @param Viaggio Struttura che contiene i dati da impostare nel nuovo nodo
*/
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


/*
    Funzione che alloca il nodo e chiama la funzione che ne imposta i dati.

    @param Viaggio Struttura che contiene i dati da impostare nel nuovo nodo
    @param int ID da associare al viaggio

    @return ListaViaggi* Indirizzo del nuovo nodo
*/
ListaViaggi* newViaggio(Viaggio temp, int id){
    ListaViaggi* new = (ListaViaggi*)malloc(sizeof(ListaViaggi));
    setDatiViaggio(new, temp);
    new->id = id;
    return new;
}

/*
    Funzione che aggiunge il viaggio alla lista, in ordine di partenza crescente (il più recente all'inizio).

    @param ListaViaggi** Doppio puntatore alla testa della lista dei viaggi
    @param Viaggio Struttura che contiene i dati del viaggio da inserire alla lista
*/
void pushViaggio(ListaViaggi** lista, Viaggio temp){
    if(*lista != NULL){
        ListaViaggi *temporaneo;
        // se la data del viaggio da inserire è minore di quella del primo viaggio
        if(datecmp((*lista)->viaggio.data, temp.data) > 0){
            temporaneo = newViaggio(temp, maxId(*lista) + 1);
            temporaneo->next = *lista;
            *lista = temporaneo;
        }
        else{
            temporaneo = *lista;
            //scorre la lista finchè il viaggio da inserire ha data maggiore di quella del nodo corrente
            while(datecmp(temporaneo->viaggio.data, temp.data) < 0){
                // qui è arrivata alla fine
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

/*
    Funzione che richide tutti i dati del viaggio (con relativi controlli) e chiama la funzione che lo aggiunge alla lista.

    @param ListaViaggi** Doppio puntatore alla testa della lista dei viaggi
*/
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
    Funzione che rimuove un viaggio dalla lista.

    @param ListaViaggi** Doppio puntatore alla testa della lista dei viaggi
    @param ListaViaggi* Indirizzo del viaggio da rimuovere
*/
void popInOgniPosizione(ListaViaggi** list, ListaViaggi* temp){
    // fa questo se il viaggio da togliere è in testa
    if(*list == temp){
        *list = (*list)->next;
        free(temp);
    }
    // fa questo se in centro o alla fine
    else{
        ListaViaggi *tempToMove = *list;
        // tempToMove alla fine si posiziona sul nodo prima di quello da eliminare
        while(tempToMove->next != temp){
            tempToMove = tempToMove->next;
        }

        // collego precedente e successivo (oppure NULL se alla fine) del nodo da eliminare: per ricomporre la lista
        if(temp->next == NULL)          // se quello da eliminare è alla fine
            tempToMove->next = NULL;
        else                            // se quello da eliminare è in centro
            tempToMove->next = tempToMove->next->next;

        free(temp);
    }
}

/*
    Funzione che ricerca un viaggio dalla lista in base all'ID a lui associato e lo rimuove.

    @param ListaViaggi** Doppio puntatore alla testa della lista dei viaggi
    @param int ID del viaggio da rimuovere
*/
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

/*
    Funzione svuota completamente la lista dei viaggi.

    @param ListaViaggi** Doppio puntatore alla testa della lista dei viaggi
*/
void svuotaLista(ListaViaggi** list){
    ListaViaggi *temp = *list;  // salvo il puntatore alla testa in una variabile temporanea: per avanzare nella lista senza modificare il puntatore originale
    ListaViaggi* toDelete;      // conterrà l'indirizzo del nodo su cui fare la free

    // scorro la lista, salvo temporaneamente l'indirizzo del nodo da eliminare, avanzo al successivo, libero il nodo salvato nel temporaneo
    while (temp != NULL){
        toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }
    *list = NULL;
}

/*
    Funzione che fa "partire" gli aerei: quando la sua data diventa precedente a quella attuale, dovrebbe essere rimosso rimosso dalla lista.

    @param ListaViaggi* Doppio puntatore alla testa della lista dei viaggi
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
    Funzione che legge tutti i viaggi presenti sul file e li inserisce in una lista.

    @param ListaViaggi** Doppio puntatore alla testa della lista dei viaggi
    @param char* Nome del file da cui leggere
*/
void downloadViaggi(ListaViaggi** lista, char* fileName){
    FILE *fpin = fopen(fileName, "rb");
    Viaggio temp;

    // legge un viaggio dal file, lo mette nella variabile "temp" e poi lo aggiunge alla lista
    while(fread(&temp, sizeof(Viaggio), 1, fpin)){
        pushViaggio(lista, temp);
    }
    fclose(fpin);
}


/*
    Funzione che scrive sul file tutti i viaggi.

    @param ListaViaggi* Puntatore alla testa della lista dei viaggi
    @param char* Nome del file su cui scrivere
*/
void uploadViaggi(ListaViaggi* lista, char* fileName){
    FILE *fpout = fopen(fileName, "wb");

    // scorre tutta la lista e mano mano scrive sul file i viaggi
    while(lista != NULL){
        ListaViaggi *temp2 = lista;
        fwrite(&lista->viaggio, sizeof(Viaggio), 1, fpout);
        lista = lista->next;
        free(temp2);
    }
    fclose(fpout);
}