typedef struct{
    int day;
    int month;
    int year;
    int hour;
    int minute;
} Data;

/*
    Funzione che restituisce l'anno corrente.

    @return Anno corrente
*/
int getYear(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return 1900 + tm.tm_year;
}

/*
    Funzione che restituisce il mese corrente.

    @return Mese corrente
*/
int getMonth(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return 1 + tm.tm_mon;
}

/*
    Funzione che restituisce il giorno corrente.

    @return Giorno corrente
*/
int getDay(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return tm.tm_mday;
}

/*
    Funzione che restituisce l'ora corrente corrente.

    @return Ora corrente
*/
int getHour(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return tm.tm_hour;
}

/*
    Funzione che restituisce il minuto corrente.

    @return Minuto corrente
*/
int getMinute(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return tm.tm_min;
}

/*
    Funzione che restituisce la data corrente completa.

    @return Data corrente
*/
Data getData(){
    Data temp;
    temp.year = getYear();
    temp.month = getMonth();
    temp.day = getDay();
    temp.hour = getHour();
    temp.minute = getMinute();

    return temp;
}

/*
    Funzione che calcola se l'anno inserito è quello corrente.

    @param int Anno da verificare

    @return 1 se corrente, se no 0
*/
int isCurrentYear(int year){
    if(year == getYear())
        return 1;
    return 0;
}

/*
    Funzione che calcola se il mese inserito è quello corrente.

    @param int Anno della data da verificare
    @param int Mese della data da verificare

    @return 1 se corrente, se no 0
*/
int isCurrenyMonth(int year, int month){
    if(isCurrentYear(year) && month == getMonth())
        return 1;
    return 0;
}

/*
    Funzione che calcola se il giorno inserito è quello corrente.

    @param int Anno della data da verificare
    @param int Mese della data da verificare
    @param int Giorno della data da verificare

    @return 1 se corrente, se no 0
*/
int isCurrentDay(int year, int month, int day){
    if(isCurrentYear(year) && isCurrenyMonth(year, month) && day == getDay())
        return 1;
    return 0;
}

/*
    Funzione che calcola se l'ora inserito è quello corrente.

    @param int Anno della data da verificare
    @param int Mese della data da verificare
    @param int Giorno della data da verificare
    @param int Ora della data da verificare

    @return 1 se corrente, se no 0
*/
int isCurrentHour(int year, int month, int day, int hour){
    if(isCurrentYear(year) && isCurrenyMonth(year, month) && isCurrentDay(year, month, day) && hour == getHour())
        return 1;
    return 0;
}

/*
    Funzione che calcola se l'ora inserito è quello corrente.

    @param int Anno della data da verificare
    @param int Mese della data da verificare
    @param int Giorno della data da verificare
    @param int Ora della data da verificare
    @param int Minuto della data da verificare

    @return 1 se corrente, se no 0
*/
int isCurrentMinute(int year, int month, int day, int hour, int minute){
    if(isCurrentYear(year) && isCurrenyMonth(year, month) && isCurrentDay(year, month, day) && isCurrentHour(year, month, day, hour) && minute == getMinute())
        return 1;
    return 0;
}


/*
    Funzione che compara due date

    @param Data Prima data
    @param Data Seconda data

    @return 0 se uguali, 1 se il primo è maggiore, -1 se il secondo è maggiore
*/
int datecmp(Data d1, Data d2){
    if(d1.year == d2.year && d1.month == d2.month && d1.day == d2.day && d1.hour == d2.hour && d1.minute == d2.minute)
        return 0;
    // se il primo è maggiore del secondo --> 1
    // se il primo è minore del secondo ---> -1
    if(d1.year < d2.year)
        return -1;
    else if(d1.year > d2.year)
        return 1;

    if(d1.month < d2.month)
        return -1;
    else if(d1.month > d2.month)
        return 1;
        
    if(d1.day < d2.day)
        return -1;
    else if(d1.day > d2.day)
        return 1;

    if(d1.hour < d2.hour)
        return -1;
    else if(d1.hour > d2.hour)
        return 1;

    if(d1.minute < d2.minute)
        return -1;
    else if(d1.minute > d2.minute)
        return 1;
}