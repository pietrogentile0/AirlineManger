typedef struct{
    int day;
    int month;
    int year;
    int hour;
    int minute;
} Data;

int getYear(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return 1900 + tm.tm_year;
}

int getMonth(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return 1 + tm.tm_mon;
}

int getDay(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return tm.tm_mday;
}

int getHour(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return tm.tm_hour;
}

int getMinute(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return tm.tm_min;
}

Data getData(){
    Data temp;
    temp.year = getYear();
    temp.month = getMonth();
    temp.day = getDay();
    temp.hour = getHour();
    temp.minute = getMinute();

    return temp;
}

int isCurrentYear(int year){
    if(year == getYear())
        return 1;
    return 0;
}

int isCurrenyMonth(int year, int month){
    if(isCurrentYear(year) && month == getMonth())
        return 1;
    return 0;
}

int isCurrentDay(int year, int month, int day){
    if(isCurrentYear(year) && isCurrenyMonth(year, month) && day == getDay())
        return 1;
    return 0;
}

int isCurrentHour(int year, int month, int day, int hour){
    if(isCurrentYear(year) && isCurrenyMonth(year, month) && isCurrentDay(year, month, day) && hour == getHour())
        return 1;
    return 0;
}

int isCurrentMinute(int year, int month, int day, int hour, int minute){
    if(isCurrentYear(year) && isCurrenyMonth(year, month) && isCurrentDay(year, month, day) && isCurrentHour(year, month, day, hour) && minute == getMinute())
        return 1;
    return 0;
}

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