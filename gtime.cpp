#include<iostream>
#include<cstring>
#include<ctime>
#include<math.h>
typedef unsigned long long ul;

using namespace std;

inline ul get_remainder(ul & time,int exponent){
    ul divisor=(ul)pow(10,exponent);
    ul rem=time%divisor;
    time=time/divisor;
    return rem;
}

inline ul get_isttime(ul tme,int precision){
    
    // 11 digit or less --> second(0), 12 to 14 digit --> millisecond(1), 15 to 16 digit --> microsecond(2), 17 digit or upper --> nanosecond(3).
    ul temp=((5*60)*60+(30*60));
    if(precision==0)
        tme=tme+temp;
    if(precision==1)
        tme=tme+temp*1000;
    if(precision==2)
        tme=tme+temp*1000000;
    if(precision==3)
        tme=tme+temp*1000000000;
    return tme;
}

inline char* get_week(int day){

char* ch;
    if(day==0)
        ch="Sunday";
    if(day==1)
        ch="Monday";
    if(day==2)
        ch="Tuesday";
    if(day==3)
        ch="Wednesday";
    if(day==4)
        ch="Thursday";
    if(day==5)
        ch="Fiday";
    if(day==6)
        ch="Saturday";
   return ch;
}

inline char* get_month(int mon){
    char* ch;
    if(mon==0)
        ch="January";
    if(mon==1)
        ch="February";
    if(mon==2)
        ch="March";
    if(mon==3)
        ch="April";
    if(mon==4)
        ch="May";
    if(mon==5)
        ch="June";
    if(mon==6)
        ch="July";
    if(mon==7)
        ch="August";
    if(mon==8)
        ch="September";
    if(mon==9)
        ch="October";
    if(mon==10)
        ch="November";
    if(mon==11)
        ch="December";
    return ch;
}

inline int get_year(int ey){
    return 1900+ey;
    }

inline char* get_meridian(int hr){
    if(hr>=12 && hr<=23)
        return "PM";
    else if(hr>=0 && hr<=11 )
        return "AM" ;
}
inline int TwelveHRFormat(struct tm* ptm){
    return  ((ptm->tm_hour%24)>=13&&(ptm->tm_hour%24)<=23)?(ptm->tm_hour%24)%12:ptm->tm_hour%24;
}

inline void print(int& zone, struct tm*& ptm, time_t& ms, time_t& us, time_t& ns){

    char* zch,*timezone;
    if(zone==1){
        zch="LOCAL";
        timezone="IST";
        }
    else if(zone==0){
        zch="GLOBAL";
        timezone="GMT";
        }
    printf ("%6s TIME : %9s, %s %dth, %d, %02d:%02d:%02d %s, %3d MilliSec, %3d MicroSec, %3d NanoSec %s\n", zch, get_week(ptm->tm_wday), get_month(ptm->tm_mon), ptm->tm_mday, get_year(ptm->tm_year), TwelveHRFormat(ptm), ptm->tm_min, ptm->tm_sec, get_meridian((ptm->tm_hour)%24),ms,us,ns,timezone);
}

//gmt=0,local=1
void print_time(time_t tme, int precision, int zone)
{
    char* zch;
    if(zone==0)
        zch="(GMT)";
    else if(zone==1)
        zch="(LOCAL)";
    //time(&rawtime);
    struct tm *ptm;
    
    string gmtTime,localTimes;
    ul tm=tme,nanorem;
    time_t ns,us,ms;
    ns=us=ms=0;
    time_t sec=0;
    //precision=3;
    switch (precision)
    {
    case 3:         //nano sec
        tme=get_remainder(tm,9);
        sec=tm;
        nanorem=tme;
        tme=get_remainder(nanorem,6);
        ms=nanorem;
        nanorem=tme;
        ns=get_remainder(nanorem,3);
        us=nanorem;
        ptm = gmtime (&sec);
        print(zone,ptm, ms, us, ns);
        break;
    case 2:     //microsec
        tme=get_remainder(tm,6);
        sec=tm;
        nanorem=tme;
        us=get_remainder(nanorem,3);
        ms=nanorem;
        ptm = gmtime (&sec);
        print(zone,ptm, ms, us, ns);
        break;
    case 1:     //milli sec
        tme=get_remainder(tm,3);
        sec=tm;
        ms=tme;
        ptm = gmtime (&sec);
        print(zone,ptm, ms, us, ns);
        break;
    case 0:
        //printf("%s\n", asctime(ptm));
        ptm = gmtime ( &tme );
        print(zone,ptm, ms, us, ns);
        break;

    default: cout<<"Not a valid time"<<endl;
        break;
    }
}

int main(int argc, char const *argv[]){

    

    int precision=-1,l=0;  

    if(argc>1)
        l=strlen(argv[1]);
    else{
        cout<<"Enter a valid time"<<endl;
        exit(0);
    }
    // 11 digit or less --> second(0), 12 to 14 digit --> millisecond(1), 15 to 16 digit --> microsecond(2), 17 digit or upper --> nanosecond(3).
    if(l<=11)
        precision = 0;
    else if(l>=12 && l<=14)
        precision = 1;
    else if(l>=15 && l<=16)
        precision = 2;
    else if(l>=17 && l<=21)
        precision = 3;
    /* else{
        cout<<"Enter a valid time"<<endl;
        exit(0);
    } */

    ul tme = atoll(argv[1]);

    //gmtTime
    print_time((time_t)tme,precision,0);


    
    //ISTTime
    //tme=tme+((5*60)*60+(30*60));
    time_t ist=get_isttime(tme,precision);
    print_time(ist,precision,1);


return 0;
}