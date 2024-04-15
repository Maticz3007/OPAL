#include "solution_output.h"
#include "maze_storage.h"
#include <stdio.h>

//short int wypisz_liste_krokow(FILE * plik_wejsciowy);
short int wypisz_liste_krokow(FILE * plik_wejsciowy, FILE * plik_wyjsciowy, short int tryb, Pole wejscie, Pole wyjscie) {
    short int nie_udalo_sie;
    unsigned int dl_sciezki = _sprawdz_dlugosc_sciezki(wejscie, wyjscie);
    if (dl_sciezki == 0) return 435; // Sciezka nie istnieje!
    printf("Dlugosc sciezki (bez Pola wejscia) wyniosla %i.\n",dl_sciezki);
    switch (tryb) {
        case 0:
            nie_udalo_sie = _wypisz_liste_krokow_tekstowo(plik_wyjsciowy, wejscie, wyjscie);
            if (nie_udalo_sie) return nie_udalo_sie;
            break;
        case 1:
            nie_udalo_sie = _przepisz_plik_do_sekcji_naglowkowej_rozwiazania(plik_wejsciowy, plik_wyjsciowy);
            if (nie_udalo_sie) return nie_udalo_sie;
            nie_udalo_sie = _wypisz_liste_krokow_binarnie(plik_wyjsciowy, wejscie, wyjscie);
            if (nie_udalo_sie) return nie_udalo_sie;
            break;
        case 2:
            nie_udalo_sie = _przejdz_do_sekcji_naglowkowej_rozwiazania(plik_wejsciowy);
            if (nie_udalo_sie) return nie_udalo_sie;
            nie_udalo_sie = _wypisz_liste_krokow_binarnie(plik_wyjsciowy, wejscie, wyjscie);
            if (nie_udalo_sie) return nie_udalo_sie;
            break;
    }
    return 0;
}

unsigned int _sprawdz_dlugosc_sciezki(Pole wejscie, Pole wyjscie) {
    short int nie_udalo_sie;
    Pole PoleD; // PolePoprzednie, PoleDoszlismy
    Pole * PoleD_G = &PoleD;
    Pole przy_wejsciu = _zwroc_Pole_przy_skrajnym_Polu(wejscie);
    Pole przy_wyjsciu = _zwroc_Pole_przy_skrajnym_Polu(wyjscie);
    unsigned int calkowita_sciezka = 0; // aktualna sciezka;
    PoleD = przy_wejsciu;
    while (PoleD.a != przy_wyjsciu.a || PoleD.b != przy_wyjsciu.b) {
        if (!Pole_czy_istnieje(PoleD)) {
            printf("solution_output: Cos jest bardzo nie tak, doszlismy do nieistniejacego Pola\n");
            return 0;
        }
        if (!Pole_czy_w_chunku(PoleD)) {
            nie_udalo_sie = wczytaj_chunk_z_Polem(PoleD);
            if (nie_udalo_sie) return 0; // w zasadzie powinno sie udac
        }
        if (!Pole_czy_odwiedzone(PoleD)) {
            if (calkowita_sciezka != 0) printf("solution_output: Cos jest bardzo nie tak, doszlismy do nieodwiedzonego Pola niebedacego przy wejsciu.\n");
            return 0; // Sciezka nie istnieje!
        }
        Pole_skad_doszedl(PoleD_G); // to powinno zadzialac bez problemow
        if (PoleD_G == NULL) {
            printf("solution_output: Cos jest bardzo nie tak, nie udalo sie uzyskac informacji skad doszlismy, a powinno to bylo byc mozliwe.\n");
            return 0;
        }
        calkowita_sciezka++;
    }
    // Prawie koniec sciezki
    // Idziemy do wyjscia
    calkowita_sciezka++;
    return calkowita_sciezka;
}

short int _wypisz_liste_krokow_tekstowo(FILE * plik_wyjsciowy, Pole wejscie, Pole wyjscie) {
    short int nie_udalo_sie;
    Pole PoleP, PoleD; // PolePoprzednie, PoleDoszlismy
    Pole przy_wejsciu = _zwroc_Pole_przy_skrajnym_Polu(wejscie);
    Pole przy_wyjsciu = _zwroc_Pole_przy_skrajnym_Polu(wyjscie);
    short int akt_d = 0; // aktualna sciezka TYLKO w 1 kierunku
    // akt_d nie moze przekroczyc max(labirynt.a, labirynt.b)
    uint8_t poprzedni_kierunek, nowy_kierunek;short int wzglednosc_kierunkow;
    PoleP = wejscie;
    PoleD = przy_wejsciu;
    poprzedni_kierunek = _kierunek_z_Odcinka(PoleP, PoleD); // Zaczynamy na wejsciu patrzac w tym kierunku
    fprintf(plik_wyjsciowy,"START\n");
    // Przechodzimy z Pola wejsciowego do Pola przy wejsciu
    akt_d++;
    // Reszta sciezki
    while (PoleD.a != przy_wyjsciu.a || PoleD.b != przy_wyjsciu.b) {
        if (!Pole_czy_w_chunku(PoleD)) {
            nie_udalo_sie = wczytaj_chunk_z_Polem(PoleD);
            if (nie_udalo_sie) return nie_udalo_sie; // w zasadzie powinno sie udac
        }
        // Wiemy juz, ze sciezka istnieje wiec nie musimy sprawdzac czy Pola sa odwiedzone
        PoleP.a = PoleD.a;PoleP.b = PoleD.b;
        //printf("Do Pola (%i, %i)",PoleD.a,PoleD.b);
        Pole_skad_doszedl(&PoleD); // to powinno zadzialac bez problemow
        //printf(" doszlismy z (%i, %i)\n",PoleD.a,PoleD.b);
        nowy_kierunek = _kierunek_z_Odcinka(PoleP, PoleD);
        //printf("(poprzedni_k, nowy_k): (%c, %c)\n",poprzedni_kierunek,nowy_kierunek);
        if (nowy_kierunek != poprzedni_kierunek) {
            fprintf(plik_wyjsciowy, "FORWARD %i\n", akt_d);
            akt_d = 1;
            wzglednosc_kierunkow = _wzglednosc_kierunkow(poprzedni_kierunek, nowy_kierunek);
            switch (wzglednosc_kierunkow) {
                case 1:
                    fprintf(plik_wyjsciowy, "TURNLEFT\n");
                    break;
                case 0:
                    printf("Cos jest bardzo zle...\nNasz program cofa sie...\n");
                    //abort();
                    break;
                case -1:
                    fprintf(plik_wyjsciowy, "TURNRIGHT\n");
                    break;
            }
            poprzedni_kierunek = nowy_kierunek;
        } else akt_d++;
    }
    // Prawie koniec sciezki
    // Idziemy do wyjscia
    nowy_kierunek = _kierunek_z_Odcinka(PoleD, wyjscie);
    if (nowy_kierunek != poprzedni_kierunek) {
        fprintf(plik_wyjsciowy, "FORWARD %i\n", akt_d);
        akt_d = 1;
        wzglednosc_kierunkow = _wzglednosc_kierunkow(poprzedni_kierunek, nowy_kierunek);
        switch (wzglednosc_kierunkow) {
            case 1:
                fprintf(plik_wyjsciowy, "TURNLEFT\n");
                break;
            case 0:
                printf("Cos jest bardzo zle...\nNasz program cofa sie...\n");
                //abort();
                break;
            case -1:
                fprintf(plik_wyjsciowy, "TURNRIGHT\n");
                break;
        }
        poprzedni_kierunek = nowy_kierunek;
    } else akt_d++;
    if (akt_d != 0) {
        fprintf(plik_wyjsciowy, "FORWARD %i\n", akt_d);
        akt_d = 0;
    }
    fprintf(plik_wyjsciowy,"STOP\n");
    return 0;
}

short int _przepisz_plik_do_sekcji_naglowkowej_rozwiazania(FILE * plik_wejsciowy, FILE * plik_wyjsciowy)
{
    return 14312;
} // Jeszcze nie zaimplementowane

short int _przejdz_do_sekcji_naglowkowej_rozwiazania(FILE * plik_wyjsciowy)
{
    return 14312;
} // Jeszcze nie zaimplementowane

short int _wypisz_liste_krokow_binarnie(FILE * plik_wyjsciowy, Pole wejscie, Pole wyjscie)
{
    return 14312;
} // Jeszcze nie zaimplementowane

Pole _zwroc_Pole_przy_skrajnym_Polu(Pole skrajne) {
    if (skrajne.a == 0) skrajne.a++;
    else if (skrajne.b == 0) skrajne.b++;
    else if (skrajne.a > skrajne.b) skrajne.a--;
    else skrajne.b--;
    return skrajne;
}

uint8_t _kierunek_z_Odcinka(Pole P1, Pole P2) {
    if (P1.a == P2.a && P1.b-1 == P2.b) return 78;      // 01001110 (znak 'N')  - w gore
    else if (P1.a+1 == P2.a && P1.b == P2.b) return 69; // 01000101 (znak 'E')  - w prawo
    else if (P1.a == P2.a && P1.b+1 == P2.b) return 83; // 01010011 (znak 'S')  - w dol
    else if (P1.a-1 == P2.a && P1.b == P2.b) return 87; // 01010111 (znak 'W')  - w lewo
    else return 0;                                      // 00000000 (znak NULL) - P1 i P2 nie sasiaduja ze soba
}

short int _wzglednosc_kierunkow(uint8_t kierunek1, uint8_t kierunek2) {
    short int x1,y1,x2,y2;short int jest_bez_sensu = 0;
    // wykorzystujemy iloczyn wektorowy [x1,y1] x [x2,y2]
    // wektor [x1, y1]
    switch (kierunek1) {
        case 78: // 01001110 (znak 'N')  - w gore
            x1 = 0;y1 = 1;
            break;
        case 69: // 01000101 (znak 'E')  - w prawo
            x1 = 1;y1 = 0;
            break;
        case 83: // 01010011 (znak 'S')  - w dol
            x1 = 0;y1 = -1;
            break;
        case 87: // 01010111 (znak 'W')  - w lewo
            x1 = -1;y1 = 0;
            break;
        default:
            jest_bez_sensu = 1;
            break;
    }
    if (jest_bez_sensu) return 0;
    // wektor [x2, y2]
    switch (kierunek2) {
        case 78: // 01001110 (znak 'N')  - w gore
            x2 = 0;y2 = 1;
            break;
        case 69: // 01000101 (znak 'E')  - w prawo
            x2 = 1;y2 = 0;
            break;
        case 83: // 01010011 (znak 'S')  - w dol
            x2 = 0;y2 = -1;
            break;
        case 87: // 01010111 (znak 'W')  - w lewo
            x2 = -1;y2 = 0;
            break;
        default:
            jest_bez_sensu = 1;
            break;
    }
    if (jest_bez_sensu) return 0;
    // jesli [x1,y1] x [x2,y2] > 0 - to znaczy, ze kierunek2 jest na lewo od kierunek1
    // jesli [x1,y1] x [x2,y2] < 0 - to znaczy, ze kierunek2 jest na prawo od kierunek1
    // jesli [x1,y1] x [x2,y2] == 0 - wektory sa wspoliniowe, czyli kierunek1 jest rownolegly do kierunek2
    return ((x1*y2)-(x2*y1));
}