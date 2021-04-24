typedef struct{
    char type[20];
    Data data;
    float importo;
} Transazione;

/*

    GESTIONE FILE

*/
void visualizzaTransazioni(char* fileName){
    Transazione temp;
    FILE *fpin = fopen(fileName, "rb");     
    while(fread(&temp, sizeof(Transazione), 1, fpin)){
            printf("%s\t\t\t%.2f\t\t%d/%d/%d\t%d:%d\n", temp.type, temp.importo, temp.data.day, temp.data.month, temp.data.year, temp.data.hour, temp.data.minute);
    }
    fclose(fpin);
}

void setDataTransazione(Data* data){
    data->day = getDay();
    data->month = getMonth();
    data->year = getYear();
    data->hour = getHour();
    data->minute = getMinute();
}

void uploadTransazione(char* type, float importo, char* fileName){
    Transazione temp;
    strcpy(temp.type, type);
    setDataTransazione(&(temp.data));
    temp.importo = importo;

    FILE *fpout = fopen(fileName, "ab");
    fwrite(&temp, sizeof(Transazione), 1, fpout);
    fclose(fpout);
}

/*

    PAGAMENTO 

*/
void pagamento(ListaViaggi* viaggioDaPagare, char* fileName){
    int metodoPag;

    printf("Benvenuto nell'area pagamento\n\nTotale da pagare: %.2f euro\n\n1. PAGA CON CARTA\t2. PAGA IN CONTANTI\n", viaggioDaPagare->viaggio.costoBiglietto);
    do{
        scanf("%d", &metodoPag);
        fflush(stdin);
    } while (metodoPag != 1 && metodoPag != 2);

    if(metodoPag == 1){
        printf("Avvicinare la carta di credito al bancomat e premere un pulsante...\n");
        getch();
        printf("\nPagamento effettuato correttamente. Arrivederci e grazie!\n");
    }
    else{
        float contante;
        printf("Inserisci il valore del contante: ");
        do{
            scanf("%f", &contante);
            fflush(stdin);
        } while (contante < viaggioDaPagare->viaggio.costoBiglietto);
        printf("Grazie a lei ed ecco il suo resto di %.2f euro\n", contante-(viaggioDaPagare->viaggio.costoBiglietto));
    }

    uploadTransazione("ticket", viaggioDaPagare->viaggio.costoBiglietto, fileName);
}