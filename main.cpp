/*
(1) Temat: Kasyno
(2)Dane studenta: Kuba Horochowski 241154
(3) Opis zasobów/wątków:
Wątki: Klienci kasyna (kilka/kilkanaście)
Krupierzy (kilka)
Zasoby: Maszyny (kilka/kilkanaście)
Bar (kilka)
Stoliki do gry dla różnej ilości osób (kilka)
Miejsca przy barze
(4) Opis: Problem opisuje pracę kasyna. Klienci kasyna mogą:
grać na maszynie (losowa ilość czasu)
grać w blackjack (losowa ilość czasu).
Krupierzy znajduja sie przy przy stolikach i zmieniaja sie co jakis czas.
Przy jednej maszynie może grać tylko 1 klient, przy stoliku do blackjacka może grać od 1 do 4os.
Aby gracz mógł przystąpić do grania maszyna musi być wolna lub musi być miejsce przy stoliku do blackjacka. Klient po zakończeniu gry (po losowej)
ilości czasu zwalnia swoje stanowisko.
Planuje aby gracze trzymali się kolejności grania maszyna - blackjack, z małym prawdopodobieństwem złamania tej kolejności (na poziomie 5-10%).
Klienci moga również siadac przy barze.
*/
 
 
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <unistd.h>
#include <ncurses.h>
#include <vector>
#define LICZBA_KLIENTOW 10
#define LICZBA_KRUPIEROW 2
#define LICZBA_MASZYN 5
bool exitProgram = false;
using namespace std;
 
 
class Maszyna{
    public:
    mutex mmutex;
    string status;
 
    Maszyna(){
        status = "Wolna";
    }
 
    string wezStatusMaszyny(){
        return status;
    };
};
 
class Stolik{
    public:
    mutex miejsce1;
    mutex miejsce2;
    mutex miejsce3;
    mutex miejsce4;
    mutex krupierm;
    string statuss;
    int miejscaStolik = 4;
    bool wolnyPraca = true;
 

 
    Stolik(){
        statuss = "Wolny";
    }
 
    bool getWolnyPraca(){
        return wolnyPraca;
    }
 
    void pracujPrzy(){
        wolnyPraca = false;
        krupierm.lock();
    }
 
    void idziePrzerwa(){
        krupierm.unlock();
        wolnyPraca = true;
    }
 
    string czyWolny(){
        return statuss;
    }
 
    void przerwaKrup(){
            wolnyPraca = true;
            statuss = "Zajety";
            krupierm.unlock();
    }
 
    void pracaKrup(){
            wolnyPraca = false;
            statuss = "Wolny";
            krupierm.lock();
    }
 
    string wezWolneMiejsca(){
        return to_string(miejscaStolik);
    };

    string wezStatusStolika(){
        if(miejscaStolik == 0)
            statuss = "Zajety";
        else
            statuss = "Wolny";
        
    return statuss;
    };
};
 
 
class Bar{
    public:
    mutex bar1;
    mutex bar2;
    mutex bar3;
    mutex bar4;
    mutex bar5;
    string statusss;
    int miejscaBar = 5;
 
    Bar(){
        statusss = "Wolny";
    };
 
    string wezStatusBaru(){
        if(miejscaBar == 0)
            statusss = "Zajety";
        else
            statusss = "Wolny";
        
        return statusss;
    };
 
    string wezWolneMiejsca(){
        return to_string(miejscaBar);
    };
 
};
 
class Klient{
    string status;
    Bar* ba1;
    Stolik* st1;
    Stolik* st2;
    Maszyna* ma1;
    Maszyna* ma2;
    Maszyna* ma3;
    Maszyna* ma4;
    Maszyna* ma5;

   
public:
 
    int maszynaProgres;
    int stolikProgres;
    int barProgres;
 
    int getMaszynaProgres(){
        return maszynaProgres;
    }
 
    int getStolikProgres(){
        return stolikProgres;
    }
 
    int getBarProgres(){
        return barProgres;
    }
 
 
    Klient(Bar* b1, Stolik* stl1, Stolik* stl2, Maszyna* m1, Maszyna* m2, Maszyna* m3, Maszyna* m4, Maszyna* m5){
        ba1 = b1;
        st1 = stl1;
        st2 = stl2;
        ma1 = m1;
        ma2 = m2;
        ma3 = m3;
        ma4 = m4;
        ma5 = m5;
        status = "czeka";
 
    }
   
    void graMaszyna(){
        if(!exitProgram){
            maszynaProgres = 0;
            if(ma1->mmutex.try_lock()){
                ma1->status = "Zajeta";
                status = "gra na maszynie";
                for(int i = 0; i <10; i++){
                    maszynaProgres++;
                    usleep(300000 + rand() % 100000);}
                ma1->status = "Wolna";
                ma1->mmutex.unlock();}
            else if(ma2->mmutex.try_lock()){
                ma2->status = "Zajeta";
                status = "gra na maszynie";
                for(int i = 0; i <10; i++){
                    maszynaProgres++;
                    usleep(300000 + rand() % 100000);}
                ma2->status = "Wolna";
                ma2->mmutex.unlock();}
            else if(ma3->mmutex.try_lock()){
                ma3->status = "Zajeta";
                status = "gra na maszynie";
                for(int i = 0; i <10; i++){
                    maszynaProgres++;
                    usleep(300000 + rand() % 100000);}
                ma3->status = "Wolna";
                ma3->mmutex.unlock();}
            else if(ma4->mmutex.try_lock()){
                ma4->status = "Zajeta";
                status = "gra na maszynie";
                for(int i = 0; i <10; i++){
                    maszynaProgres++;
                    usleep(300000 + rand() % 100000);}
                ma4->status = "Wolna";
                ma4->mmutex.unlock();}
            else if(ma5->mmutex.try_lock()){
                ma5->status = "Zajeta";
                status = "gra na maszynie";
                for(int i = 0; i <10; i++){
                    maszynaProgres++;
                    usleep(300000 + rand() % 100000);}
                ma5->status = "Wolna";
                ma5->mmutex.unlock();}
            status = "czeka";
        }
    }
   
    void graStolik(){
        if(!exitProgram){
            stolikProgres = 0;
        if(st1->miejsce4.try_lock()){
            st1->miejscaStolik--;
            status = "gra przy stoliku";
            for(int i = 0; i < 10; i++){
                stolikProgres++;
                usleep(300000 + rand()%100000);
            }
            st1->miejscaStolik++;
            st1->miejsce4.unlock();}
        else if(st1->miejsce3.try_lock()){
            st1->miejscaStolik--;
            status = "gra przy stoliku";
            for(int i = 0; i < 10; i++){
                stolikProgres++;
                usleep(300000 + rand()%100000);
            }
            st1->miejscaStolik++;
            st1->miejsce3.unlock();}
        else if(st1->miejsce2.try_lock()){
            st1->miejscaStolik--;
            status = "gra przy stoliku";
            for(int i = 0; i < 10; i++){
                stolikProgres++;
                usleep(300000 + rand()%100000);
            }
            st1->miejscaStolik++;
            st1->miejsce2.unlock();}
        else if(st1->miejsce1.try_lock()){
            st1->miejscaStolik--;
            status = "gra przy stoliku";
            for(int i = 0; i < 10; i++){
                stolikProgres++;
                usleep(300000 + rand()%100000);
            }
            st1->miejscaStolik++;
            st1->miejsce1.unlock();}

        else if(st2->miejsce4.try_lock()){
            st2->miejscaStolik--;
            status = "gra przy stoliku";
            for(int i = 0; i < 10; i++){
                stolikProgres++;
                usleep(300000 + rand()%100000);
            }
            st2->miejscaStolik++;
            st2->miejsce4.unlock();}
        else if(st2->miejsce3.try_lock()){
            st2->miejscaStolik--;
            status = "gra przy stoliku";
            for(int i = 0; i < 10; i++){
                stolikProgres++;
                usleep(300000 + rand()%100000);
            }
            st2->miejscaStolik++;
            st2->miejsce3.unlock();}
        else if(st2->miejsce2.try_lock()){
            st2->miejscaStolik--;
            status = "gra przy stoliku";
            for(int i = 0; i < 10; i++){
                stolikProgres++;
                usleep(300000 + rand()%100000);
            }
            st2->miejscaStolik++;
            st2->miejsce2.unlock();}
        else if(st2->miejsce1.try_lock()){
            st2->miejscaStolik--;
            status = "gra przy stoliku";
            for(int i = 0; i < 10; i++){
                stolikProgres++;
                usleep(300000 + rand()%100000);
            }
            st2->miejscaStolik++;
            st2->miejsce1.unlock();}
        status = "czeka";    
        }
    }
 
    void siedziBar(){
        if(!exitProgram){
            barProgres = 0;
                if(ba1->bar5.try_lock()){
                    ba1->miejscaBar--;
                    status = "siedzi przy barze";
                    for(int i = 0; i < 10; i++){
                        barProgres++;
                        usleep(300000 + rand()%100000);}
                    ba1->miejscaBar++;
                    ba1->bar5.unlock();}
                else if(ba1->bar4.try_lock()){
                    ba1->miejscaBar--;
                    status = "siedzi przy barze";
                    for(int i = 0; i < 10; i++){
                        barProgres++;
                        usleep(300000 + rand()%100000);}
                    ba1->miejscaBar++;
                    ba1->bar4.unlock();}
                else if(ba1->bar3.try_lock()){
                    ba1->miejscaBar--;
                    status = "siedzi przy barze";
                    for(int i = 0; i < 10; i++){
                        barProgres++;
                        usleep(300000 + rand()%100000);}
                    ba1->miejscaBar++;
                    ba1->bar3.unlock();}
                else if(ba1->bar2.try_lock()){
                    ba1->miejscaBar--;
                    status = "siedzi przy barze";
                    for(int i = 0; i < 10; i++){
                        barProgres++;
                        usleep(300000 + rand()%100000);}
                    ba1->miejscaBar++;
                    ba1->bar2.unlock();}
                else if(ba1->bar1.try_lock()){
                    ba1->miejscaBar--; 
                    status = "siedzi przy barze";
                    for(int i = 0; i < 10; i++){
                        barProgres++;
                        usleep(300000 + rand()%100000);}
                    ba1->miejscaBar++;
                    ba1->bar1.unlock();}
                status = "czeka";
        }
    }
 
    int getStatus(){
        if(this->status == "gra na maszynie"){
            return 1;
        } else if (this->status == "gra przy stoliku"){
            return 2;
        } else if (this->status == "siedzi przy barze"){
            return 3;
        } else return 4;    
    }
};

class Krupier{
    string status;
    Stolik* st1;
    Stolik* st2;
    int ktorySt = 0;
 
public:
 
    int pracaProgres;
    int przerwaProgres;
 
    int getPracaProgres(){
        return pracaProgres;
    }
 
    int getPrzerwaProgres(){
        return przerwaProgres;
    }
 
    Krupier(Stolik* stl1, Stolik* stl2){
        st1 = stl1;
        st2 = stl2;
    }
   
    void pracuj(){
        if(!exitProgram){
            if(st1->getWolnyPraca()){
                ktorySt=1;
                st1->pracaKrup();
            }
            else if(st2->getWolnyPraca()){
                ktorySt=2;
                st2->pracaKrup();
            }
            pracaProgres = 0;
            status = "pracuje";
            for(int i = 0; i <10; i++){
                pracaProgres++;
                usleep(2000000 + rand() % 1000000);
            }
        }
    };
   
    void przerwa(){
        if(!exitProgram){
            if(this->ktorySt == 1){
                ktorySt=0;
                st1->przerwaKrup();
            }
            else if(this->ktorySt == 2){
                ktorySt=0;
                st2->przerwaKrup(); 
            }
            przerwaProgres = 0;
            status = "Ma przerwe";
 
            for(int i = 0; i < 10; i++){
                przerwaProgres++;
                usleep(600000 + rand()%10000);
            }
        }
    }
 
    int getStatus(){
        if(this->status == "pracuje"){
            return 1;
        } else if (this->status == "Ma przerwe")
            return 2;
        return 3;    
    }
};
 
void display(std::vector<Klient*> klienci, std::vector<Krupier*> krupierzy, Stolik* stolik1, Stolik* stolik2, Bar* bar, Maszyna* maszyna1, 
            Maszyna* maszyna2,Maszyna* maszyna3,Maszyna* maszyna4,Maszyna* maszyna5)
{
    int maszynaProgress = 0;
    int stolikProgress = 0 ;
    int barProgress = 0 ;
    int pracaProgress = 0 ;
    int przerwaProgress = 0 ;
 
    noecho();
 
    while(!exitProgram) {
        clear();
        mvprintw(0, 0,"Zagadnienie pracy kasyna, wprowadz q, zeby zakonczyc");
 
        for(int i = 0; i < LICZBA_KLIENTOW; i++) {
           
            mvprintw(i+1, 1, "Klient %d", i+1);
            mvprintw(i+1, 29, "Progres:");
            mvprintw(i+1, 38, "__________");
 
            switch (klienci[i]->getStatus()){
                case 1:
                    mvprintw(i+1, 11, "gra na maszynie");
                    maszynaProgress = klienci[i]->getMaszynaProgres();
                    for(int j=0; j<maszynaProgress; j++)
                    {
                        mvprintw(i+1, 38+j, "#");
                    };
 
                    break;
 
                case 2:
                    mvprintw(i+1, 11, "gra przy stoliku");
                    stolikProgress = klienci[i]->getStolikProgres();
                    for(int j=0; j<stolikProgress; j++)
                    {
                        mvprintw(i+1, 38+j, "#");
                    };
                    break;
 
                case 3:
                    mvprintw(i+1, 11, "siedzi przy barze");
                    barProgress = klienci[i]->getBarProgres();
                    for(int j=0; j<stolikProgress; j++)
                    {
                        mvprintw(i+1, 38+j, "#");
                    };
                    break;
 
                case 4:
                    mvprintw(i+1, 13, "czeka");
                    break;              
            };
           
        }

                mvprintw(1, 50, "Maszyna 1: ");
                mvprintw(1, 61, maszyna1->wezStatusMaszyny().c_str());
                mvprintw(2, 50, "Maszyna 2: ");
                mvprintw(2, 61, maszyna2->wezStatusMaszyny().c_str());
                mvprintw(3, 50, "Maszyna 3: ");
                mvprintw(3, 61, maszyna3->wezStatusMaszyny().c_str());
                mvprintw(4, 50, "Maszyna 4: ");
                mvprintw(4, 61, maszyna4->wezStatusMaszyny().c_str());
                mvprintw(5, 50, "Maszyna 5: ");
                mvprintw(5, 61, maszyna5->wezStatusMaszyny().c_str());
 
        for(int i = 0; i < LICZBA_KRUPIEROW; i++) {
           
            mvprintw(i+1+LICZBA_KLIENTOW, 1, "Krupier %d", i+1);
            mvprintw(i+1+LICZBA_KLIENTOW, 29, "Progres:");
            mvprintw(i+1+LICZBA_KLIENTOW, 38, "__________");
 
            switch (krupierzy[i]->getStatus()){
                case 1:
                    mvprintw(i+1+LICZBA_KLIENTOW, 11, "pracuje");
                    pracaProgress = krupierzy[i]->getPracaProgres();
                    for(int j=0; j<pracaProgress; j++)
                    {
                        mvprintw(i+1+LICZBA_KLIENTOW, 38+j, "#");
                    };
 
                    break;
 
                case 2:
                    mvprintw(i+1+LICZBA_KLIENTOW, 11, "na przerwie");
                    przerwaProgress = krupierzy[i]->getPrzerwaProgres();
                    for(int j=0; j<przerwaProgress; j++)
                    {
                        mvprintw(i+1+LICZBA_KLIENTOW, 38+j, "#");
                    };
                    break;
 
                case 3:
                    mvprintw(i+1+LICZBA_KLIENTOW, 13, "czeka");
                    break;              
            };
           
            mvprintw(i+1+LICZBA_KLIENTOW, 50, "Stolik %d: ", i+1);
            mvprintw(1+LICZBA_KLIENTOW, 61, stolik1->wezStatusStolika().c_str());
            mvprintw(1+LICZBA_KLIENTOW, 68, stolik1->wezWolneMiejsca().c_str());
            mvprintw(2+LICZBA_KLIENTOW, 61, stolik2->wezStatusStolika().c_str());
            mvprintw(2+LICZBA_KLIENTOW, 68, stolik2->wezWolneMiejsca().c_str());
 
        }
 
 
        mvprintw(LICZBA_KLIENTOW+LICZBA_KRUPIEROW+1, 1, "Bar: ");
        mvprintw(LICZBA_KLIENTOW+LICZBA_KRUPIEROW+1, 7, bar->wezStatusBaru().c_str());
        mvprintw(LICZBA_KLIENTOW+LICZBA_KRUPIEROW+1, 15, "Ilosc wolnych miejsc: ");
        mvprintw(LICZBA_KLIENTOW+LICZBA_KRUPIEROW+1, 37, bar->wezWolneMiejsca().c_str());
 
           
        refresh();
        usleep(10000);
    }
}
 
void graj(Klient* k){
    while(!exitProgram){
        k -> graStolik();
        if(rand()%100 < 9)
            k-> siedziBar();
        else if (rand()%100 < 10)
            k-> graStolik();
        k -> graMaszyna();
        if(rand()%100 < 15)
            k-> graMaszyna();
        else if (rand()%100 < 10)
            k-> graStolik();
        
        k -> siedziBar();
    }
}
 
void pracuj(Krupier* k) {
    while(!exitProgram){
        k->pracuj();
        k->przerwa();
    }
}
 
 
int main(){
   
    srand(time(NULL));
    initscr();
    refresh();
 
    Stolik* s1 = new Stolik();
    Stolik* s2 = new Stolik();
    Bar* b1 = new Bar();
    Maszyna* m1 = new Maszyna();
    Maszyna* m2 = new Maszyna();
    Maszyna* m3 = new Maszyna();
    Maszyna* m4 = new Maszyna();
    Maszyna* m5 = new Maszyna();
 
    // std::vector < Maszyna* > maszyny;
    // for(int i = 0; i < LICZBA_MASZYN; i++){
    // Maszyna* maszyna = new Maszyna();
    // maszyny.push_back(maszyna);}
 
 
    std::vector < Krupier* > krupierzy;
    for(int i = 0; i < LICZBA_KRUPIEROW; i++){
    Krupier* krupier = new Krupier(s1, s2);
    krupierzy.push_back(krupier);}
 
 
    std::vector < Klient* > klienci;
    for(int i = 0; i < LICZBA_KLIENTOW; i++){
    Klient* klient = new Klient(b1, s1, s2, m1, m2, m3, m4, m5);
    klienci.push_back(klient);}
 
 
    thread threads[LICZBA_KLIENTOW];
    thread kthreads[LICZBA_KRUPIEROW];
 
    for(int i = 0; i < LICZBA_KLIENTOW; i++)
         threads[i] = thread(graj, klienci[i]);
 
    for(int i = 0; i < LICZBA_KRUPIEROW; i++)
         kthreads[i] = thread(pracuj, krupierzy[i]);
 
    thread displayThread(display, klienci, krupierzy, s1, s2, b1, m1, m2, m3, m4, m5);
 
    while (!exitProgram)
    {
        int q = getch();
        if (q == 113)
        {
            exitProgram = true;
        }
    }
 
    for(int i = 0 ; i < LICZBA_KLIENTOW; i ++)
        threads[i].join();
    for(int i = 0; i < LICZBA_KRUPIEROW; i++)
        kthreads[i].join();

    displayThread.join();
    endwin();
    return 0;
}