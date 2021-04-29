#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#include "data.c"
#include "viaggi.c"
#include "finanza.c"


/*
    Funzione che crea il file indicato se non presente.

    @param char* Nome del file da configurare
*/
void configureAndTestFile(char* fileName){
    FILE *fpin;
    fpin = fopen(fileName, "rb");
    if(!fpin){
        fclose(fpin);
        fpin = fopen(fileName, "wb");
        fclose(fpin);
    }
    else{
        fclose(fpin);
    }
}

int main(){
    int sceltaGestione;
    ListaViaggi *viaggi = NULL;
    char *viaggiFileName = "viaggi.bin";
    char *entrateFileName = "entrate.bin";

    configureAndTestFile(viaggiFileName);
    configureAndTestFile(entrateFileName);

    downloadViaggi(&viaggi, viaggiFileName);
    // takeOff(viaggi);  da finire

    do{
        printf("MENU DI SCELTA\n1. GESTIONE VOLI    2. GESTIONE FINANZA   3. COMPRA BIGLIETTO    0. USCITA\n");
        scanf("%d", &sceltaGestione);
        fflush(stdin);
        system("CLS");

        switch (sceltaGestione)
        {
            // gestione voli
            case 1 : {
                int sceltaCase1;

                do{    
                    printf("1.PROGRAMMA NUOVO VIAGGIO     2.VISUALIZZA VIAGGI      3.ELIMINA UN VIAGGIO      4.ELIMINA TUTTI I VIAGGI    0.TORNA INDIETRO\n");
                    do{
                        scanf("%d", &sceltaCase1);
                        fflush(stdin);
                    }while (sceltaCase1 > 4 || sceltaCase1 < 0);
                    system("CLS");

                    if(sceltaCase1 == 1){           // inserimento nuovo viaggio
                        inserisciViaggio(&viaggi);
                    }
                    else if(sceltaCase1 == 2){      // viasualizzazione lista
                        if(presentiViaggi(viaggi)){
                            system("CLS");
                            printf("LISTA COMPLETA VIAGGI\nID\tPARTENZA\t\tDESTINAZIONE\t\tDATA\t\t\tORA\t\tCOSTO BIGLIETTO\t\tBIGLIETTI DISPONIBILI\n");
                            visualizzaViaggi(viaggi);

                            printf("\n\npremi un tasto per continuare...");
                            getch();
                        }       
                        else{
                            printf("Non ci sono viaggi da visualizzare\n");
                            printf("\n\npremi un tasto per continuare...\n");
                            getch();
                        }
                    }
                    else if(sceltaCase1 == 3){      // eliminazione viaggio
                        if(presentiViaggi(viaggi)){    
                            int toDelete;

                            printf("LISTA COMPLETA VIAGGI\nID\tPARTENZA\t\tDESTINAZIONE\t\tDATA\t\t\tORA\t\tCOSTO BIGLIETTO\t\tBIGLIETTI DISPONIBILI\n");
                            visualizzaViaggi(viaggi);
                            printf("\n\nInserire l'id del volo da eliminare: ");
                            do{
                                scanf("%d", &toDelete);
                            } while (isThere(viaggi, toDelete) == NULL);

                            fflush(stdin);
                            rimuoviViaggio(&viaggi, toDelete);
                        }
                        else{
                            printf("Non ci sono viaggi da eliminare\n");
                            printf("\n\npremi un tasto per continuare...\n");
                            getch();
                        }
                    }
                    else if(sceltaCase1 == 4){      // cancellazione di tutti i viaggi
                        if(presentiViaggi(viaggi)){    
                            svuotaLista(&viaggi);
                            printf("tutti i viaggi sono stati cancellati!\n");
                            printf("\n\npremi un tasto per continuare...");
                            getch();
                        }
                        else{
                            printf("Non ci sono viaggi da eliminare\n");
                            printf("\n\npremi un tasto per continuare...\n");
                            getch();
                        }
                    }
                    system("CLS");
                } while (sceltaCase1 != 0);
                break;
            }

            case 2 : {
                int sceltaCase2;
                printf("1. VISUALIZZA ENTRATE       0. USCITA\n");
                scanf("%d", &sceltaCase2);
                system("CLS");
                
                if(sceltaCase2 == 1){
                    printf("LISTA TRANSAZIONI IN ENTRATA\nTIPOLOGIA\t\tIMPORTO\t\tDATA\t\tORA\n");
                    visualizzaTransazioni(entrateFileName);
                }
                getch();
                break;
            }

            // acquisto biglietti
            case 3 : {
                if(presentiPostiDisp(viaggi) != 0){    
                    int idToBuy;
                    int sceltaCase3;
                    ListaViaggi *viaggioSelezionato;
                    
                    printf("LISTA COMPLETA VIAGGI\nID\tPARTENZA\t\tDESTINAZIONE\t\tDATA\t\t\t\tORA\t\t\tCOSTO BIGLIETTO\n");
                    visualizzaViaggiAcquisto(viaggi);

                    printf("\n\n1. PROSEGUIRE CON L'ACQUISTO    0.TORNARE INDIETRO\n");
                    scanf("%d", &sceltaCase3);
                    if(sceltaCase3 == 1){
                        printf("\nInserire l'id del volo di cui acquistare il biglietto: ");
                        do{
                            scanf("%d", &idToBuy);
                            fflush(stdin);
                            viaggioSelezionato = isThere(viaggi, idToBuy);
                        } while (viaggioSelezionato == 0 || viaggioSelezionato->viaggio.postiDisp <= 0);

                        if(viaggioSelezionato->viaggio.postiDisp > 0){
                            pagamento(viaggioSelezionato, entrateFileName);
                            viaggioSelezionato->viaggio.postiDisp = viaggioSelezionato->viaggio.postiDisp - 1;
                        }
                    }    
                }
                else{
                    printf("Siamo spiacenti non ci sono voli disponibili\n");
                }
                getch();
                break;
            }
        }
        system("CLS");
    } while (sceltaGestione);

    uploadViaggi(viaggi, viaggiFileName);

    return 0;
}