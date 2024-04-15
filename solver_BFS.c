#include "solver_BFS.h"
#include "maze_storage.h"

//short int rozwiaz_BFS(Pole przy_wejsciu, Pole przy_wyjsciu); - musimy znac wymiary labiryntu, aby go podzielic i zainicjowac MazeStorage
short int rozwiaz_BFS(Pole przy_wejsciu, Pole przy_wyjsciu, short int a, short int b, FILE * plik_wejsciowy) {
    // a - liczba kolumn labiryntu, b - liczba wierszy labiryntu, plik_wejsciowy - plik do podzialu na chunki

    // Tymczasowy sposob podzialu (pewnie mozliwe sa wieksze chunki):
    // jesli max(a,b) <= 512 : podziel na 1 chunk
    // jesli 512 < max(a,b) <= 1024 : podziel na 4 chunki
    // jesli 1024 < max(a,b) <= 1536 : podziel na 9 chunkow
    // na razie wiekszych nie wspieramy
    
    short int max_a_b = a;short int l_chunkow; // l_chunkow to pierwiastek z liczby chunkow
    if (b > max_a_b) max_a_b = b;
    if (max_a_b <= 512) l_chunkow = 1;
    else if (512 < max_a_b && max_a_b <= 1024) l_chunkow = 2;
    else if (1024 < max_a_b && max_a_b <= 1536) l_chunkow = 3;
    else return 777; // jeszcze nie wspierane!
    // Ta wersja algorytmu rozwiazujacego wykorzystuje 3 bity na Pole
    MazeStorage_inicjuj(3, l_chunkow, a, b, 1, 1); // na pewno chunk (1,1) istnieje
    podziel_labirynt(3, l_chunkow, a, b, plik_wejsciowy);
    //_MazeStorage_wypisz(2); 
    // Mniej optymalna wersja algorytmu, ale z wieksza pewnoscia ze zadziala
    // Kolejka bedzie potrzebowala pewnie kilka razy wiecej elementow niz max(a,b) - to samo Pole moze zostac wrzucone wiecej niz raz

    short int nie_udalo_sie = 0;//short int wynik_funkcji;
    short int czy_mozna_w_prawo, czy_mozna_w_dol;
    Kolejka Q;
    Kolejka_inicjuj(&Q);
    // Zaczynamy przy wyjsciu z labiryntu i idziemy do wejscia
    Pole PoleD, PoleP, PoleT;KolejkaElement element;
    element.PoleD.a = przy_wyjsciu.a;element.PoleD.b = przy_wyjsciu.b;
    element.PoleP.a = 0;element.PoleP.b = 0; // przyjmujemy, ze jesli jestesmy na Polu startowym, to przyszlismy z nikad
    nie_udalo_sie = Kolejka_wrzuc(&Q, element);
    if (nie_udalo_sie) return nie_udalo_sie;
    while (Q.lel > 0) {
        _MazeStorage_wypisz(2);
        nie_udalo_sie = Kolejka_zrzuc(&Q, &element);
        if (nie_udalo_sie) return nie_udalo_sie;
        PoleD.a = element.PoleD.a;PoleD.b = element.PoleD.b;
        PoleP.a = element.PoleP.a;PoleP.b = element.PoleP.b;
        // Kolejnosc postepowania (inna niz na diagramie zmodyfikowana tak, aby nie wczytywac chunkow wiecej razy niz trzeba):
        // 1. Czy PoleD istnieje (powinno zawsze istniec)
        // 2. Czy PoleD jest w aktualnie wczytanym chunku (jesli nie to wczytaj)
        // (usunieto) Czy PoleD zostalo odwiedzone (nie powinno byc) - a jednak moze byc odwiedzone po raz drugi, jesli w tym samym momencie przyjdziemy do niego z 2 roznych miejsc
        // 3. Sprawdzamy czy mozna isc do sasiadow Pola PoleD (najpierw z prawej, potem z dolu aby nie wczytywac chunkow wiecej razy niz trzeba)
        // 4. PoleD zostaje odwiedzone
        // 5. Ustawiamy skad doszlismy do Pola PoleD
        // 6. Zapisujemy aktualnie wczytany chunk
        // 7. Wczytujemy sasiadow Pola PoleD z prawej i dolu oraz sprawdzamy czy sa odwiedzeni
        // 8. Sprawdzamy sasiadow Pola PoleD (z gory i z lewej, wymaga to wczytania chunkow z tymi Polami)
        if (!Pole_czy_istnieje(PoleD)) { // 1. Czy PoleD istnieje? Powinno zawsze istniec
            return 778;
        }
        if (!Pole_czy_w_chunku(PoleD)) { // 2. Czy PoleD jest w aktualnie wczytanym chunku (jesli nie to wczytaj)
            nie_udalo_sie = wczytaj_chunk_z_Polem(PoleD);
            if (nie_udalo_sie) return nie_udalo_sie;
        }
        if (Pole_czy_odwiedzone(PoleD)) { // PoleD powinno byc jeszcze nieodwiedzone - jednak nie, mozliwe ze zostanie odwiedzone w tym samym momencie z 2 roznych miejsc
            //return 779;
            continue; // wracamy na poczatek petli i ignorujemy to
        }
        // Sprawdzamy sasiednie Pola
        element.PoleP.a = PoleD.a;element.PoleP.b = PoleD.b;
        // 4. najpierw z prawej, potem z dolu
        PoleT.a = PoleD.a+1;PoleT.b = PoleD.b; // PoleT == PoleE (Pole po prawej od PoleD)
        czy_mozna_w_prawo = 0;
        if (Pole_czy_istnieje(PoleT) && PoleT.a != PoleP.a && PoleT.b != PoleP.b) {
            if (Pole_czy_mozna_w_prawo(PoleD)) { 
                czy_mozna_w_prawo = 1;
            }
        }
        PoleT.a = PoleD.a;PoleT.b = PoleD.b+1; // PoleT == PoleS (Pole z dolu od PoleD)
        czy_mozna_w_dol = 0;
        if (Pole_czy_istnieje(PoleT) && PoleT.a != PoleP.a && PoleT.b != PoleP.b) {
            if (Pole_czy_mozna_w_dol(PoleD)) { 
                czy_mozna_w_dol = 1;
            }
        }
        nie_udalo_sie = Pole_ustaw_czy_odwiedzone(PoleD, 1); // 5. PoleD zostaje odwiedzone
        if (nie_udalo_sie) return nie_udalo_sie;
        nie_udalo_sie = Pole_ustaw_skad_doszedl(PoleD, PoleP); // 6. Ustawiamy skad doszlismy do Pola PoleD
        if (nie_udalo_sie) return nie_udalo_sie;
        nie_udalo_sie = zapisz_chunk(); // 7. Zapisujemy aktualnie wczytany chunk
        if (nie_udalo_sie) return nie_udalo_sie;
        // 8. Wczytujemy sasiadow Pola PoleD z prawej i dolu oraz sprawdzamy czy sa odwiedzeni
        PoleT.a = PoleD.a+1;PoleT.b = PoleD.b; // PoleT == PoleE (Pole po prawej od PoleD)
        if (czy_mozna_w_prawo) {
            if (!Pole_czy_w_chunku(PoleT)) {
                nie_udalo_sie = wczytaj_chunk_z_Polem(PoleT);
                if (nie_udalo_sie) return nie_udalo_sie;
            }
            if (!Pole_czy_odwiedzone(PoleT)) { 
                element.PoleD.a = PoleT.a;element.PoleD.b = PoleT.b;
                nie_udalo_sie = Kolejka_wrzuc(&Q, element);
                if (nie_udalo_sie) return nie_udalo_sie;
            }
        }
        PoleT.a = PoleD.a;PoleT.b = PoleD.b+1; // PoleT == PoleS (Pole z dolu od PoleD)
        if (czy_mozna_w_dol) {
            if (!Pole_czy_w_chunku(PoleT)) {
                nie_udalo_sie = wczytaj_chunk_z_Polem(PoleT);
                if (nie_udalo_sie) return nie_udalo_sie;
            }
            if (!Pole_czy_odwiedzone(PoleT)) { 
                element.PoleD.a = PoleT.a;element.PoleD.b = PoleT.b;
                nie_udalo_sie = Kolejka_wrzuc(&Q, element);
                if (nie_udalo_sie) return nie_udalo_sie;
            }
        }
        // 9. z gory i z lewej
        PoleT.a = PoleD.a;PoleT.b = PoleD.b-1; // PoleT == PoleN (Pole nad PoleD)
        if (Pole_czy_istnieje(PoleT) && PoleT.a != PoleP.a && PoleT.b != PoleP.b) {
            if (!Pole_czy_w_chunku(PoleT)) {
                nie_udalo_sie = wczytaj_chunk_z_Polem(PoleT);
                if (nie_udalo_sie) return nie_udalo_sie;
            }
            // Musimy sprawdzic czy mozna w dol dopiero po sprawdzeniu czy zostalo odwiedzone
            // inaczej sie nie da przez nadpisywanie danych w Polach
            if (!Pole_czy_odwiedzone(PoleT) && Pole_czy_mozna_w_dol(PoleT)) { 
                element.PoleD.a = PoleT.a;element.PoleD.b = PoleT.b;
                nie_udalo_sie = Kolejka_wrzuc(&Q, element);
                if (nie_udalo_sie) return nie_udalo_sie;
            }
        }
        PoleT.a = PoleD.a-1;PoleT.b = PoleD.b; // PoleT == PoleW (Pole po lewej od PoleD)
        if (Pole_czy_istnieje(PoleT) && PoleT.a != PoleP.a && PoleT.b != PoleP.b) {
            if (!Pole_czy_w_chunku(PoleT)) {
                nie_udalo_sie = wczytaj_chunk_z_Polem(PoleT);
                if (nie_udalo_sie) return nie_udalo_sie;
            }
            // Musimy sprawdzic czy mozna w dol dopiero po sprawdzeniu czy zostalo odwiedzone
            // inaczej sie nie da przez nadpisywanie danych w Polach
            if (!Pole_czy_odwiedzone(PoleT) && Pole_czy_mozna_w_dol(PoleT)) { 
                element.PoleD.a = PoleT.a;element.PoleD.b = PoleT.b;
                nie_udalo_sie = Kolejka_wrzuc(&Q, element);
                if (nie_udalo_sie) return nie_udalo_sie;
            }
        }
    }
    // Przeszlismy przez wszystkie Pola, czyli znalezlismy najkrotsza sciezke jesli isniala
    // Wystarczy ja teraz tylko przesledzic wstecznie przez modul solution_output
    nie_udalo_sie = Kolejka_zniszcz(&Q);
    if (nie_udalo_sie) return nie_udalo_sie; // byloby dziwne, gdyby kolejka zostala zniszczona wczesniej i wciaz jescze nie wyszlismy z funkcji
    return 0;
}

//short int Pole_ustaw_czy_mozna_w_prawo(Pole P); - przeniesione do modulu maze_storage

//short int Pole_ustaw_czy_mozna_w_dol(Pole P); - przeniesione do modulu maze_storage
