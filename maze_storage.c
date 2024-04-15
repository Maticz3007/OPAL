#include "maze_storage.h"
#include<stdio.h> // NULL

MazeStorage labirynt;

void Pole_wypisz(Pole P) {
    printf("(%i, %i)",P.a,P.b);
}

short int Pole_czy_istnieje(Pole P) {
    // Pole P istnieje
    if (P.a > 0 && P.a <= labirynt.a && P.b > 0 && P.b <= labirynt.b) return 1;
    // Pole P nie istnieje
    return 0;
}

short int Pole_czy_w_chunku(Pole P) {
    // Pole P w aktualnie wczytanym chunku
    if (P.a >= 1+(labirynt.chunk_a-1)*labirynt._l_Pol_w_chunku &&
        P.b >= 1+(labirynt.chunk_b-1)*labirynt._l_Pol_w_chunku &&
        P.a <= labirynt.chunk_a*labirynt._l_Pol_w_chunku &&
        P.b <= labirynt.chunk_b*labirynt._l_Pol_w_chunku) return 1;
    // Pole P nie w aktualnie wczytanym chunku
    return 0;
}

short int Pole_ustaw_czy_odwiedzone(Pole P, short int czy_odw) {
    // Czy Pole istnieje
    if (!Pole_czy_istnieje(P)) return -51; // nie okreslone w Specyfikacji Implementacyjnej
    // Czy Pole jest w aktualnie wczytanym chunku
    if (!Pole_czy_w_chunku(P)) return -50;
    // Trzeci bit to czy dane Pole zostalo odwiedzone
    MazeStorage_ustaw_bit(P, 3, czy_odw);
    return 0;
}

short int Pole_czy_odwiedzone(Pole P) {
    // Czy Pole istnieje
    if (!Pole_czy_istnieje(P)) return -71;
    // Czy Pole jest w aktualnie wczytanym chunku
    if (!Pole_czy_w_chunku(P)) return -70;
    return MazeStorage_odczytaj_bit(P, 3);
}

short int Pole_ustaw_czy_mozna_w_prawo(Pole P) {
    // Czy Pole istnieje
    if (!Pole_czy_istnieje(P)) return -31;
    // Czy Pole jest w aktualnie wczytanym chunku
    if (!Pole_czy_w_chunku(P)) return -30;
    // Czy informacja ta zostala nadpisana przez Pole_ustaw_skad_doszedl,
    // tzn. czy Pole P zostalo odwiedzone
    if (Pole_czy_odwiedzone(P)) return -32;
    // Pierwszy bit kazdego Pola to informacja czy mozna isc w prawo
    MazeStorage_ustaw_bit(P, 1, 1);
    return 0;
}

short int Pole_ustaw_czy_mozna_w_dol(Pole P) {
    // Czy Pole istnieje
    if (!Pole_czy_istnieje(P)) return -41;
    // Czy Pole jest w aktualnie wczytanym chunku
    if (!Pole_czy_w_chunku(P)) return -40;
    // Czy informacja ta zostala nadpisana przez Pole_ustaw_skad_doszedl,
    // tzn. czy Pole P zostalo odwiedzone
    if (Pole_czy_odwiedzone(P)) return -42;
    // Drugi bit kazdego Pola to informacja czy mozna isc w dol
    MazeStorage_ustaw_bit(P, 2, 1);
    return 0;
}

short int Pole_czy_mozna_w_prawo(Pole P) {
    // Czy Pole istnieje
    if (!Pole_czy_istnieje(P)) return -81;
    // Czy Pole jest w aktualnie wczytanym chunku
    if (!Pole_czy_w_chunku(P)) return -80;
    // Czy informacja ta zostala nadpisana przez Pole_ustaw_skad_doszedl,
    // tzn. czy Pole P zostalo odwiedzone
    if (Pole_czy_odwiedzone(P)) return -82;
    // Pierwszy bit kazdego Pola to informacja czy mozna isc w prawo
    return MazeStorage_odczytaj_bit(P, 1);
}

short int Pole_czy_mozna_w_dol(Pole P) {
    // Czy Pole istnieje
    if (!Pole_czy_istnieje(P)) return -91;
    // Czy Pole jest w aktualnie wczytanym chunku
    if (!Pole_czy_w_chunku(P)) return -90;
    // Czy informacja ta zostala nadpisana przez Pole_ustaw_skad_doszedl,
    // tzn. czy Pole P zostalo odwiedzone
    if (Pole_czy_odwiedzone(P)) return -92;
    // Drugi bit kazdego Pola to informacja czy mozna isc w dol
    return MazeStorage_odczytaj_bit(P, 2);
}

short int Pole_ustaw_skad_doszedl(Pole D, Pole P) {
    if (P.a == 0 && P.b == 0) return 0; // na poczatku algorytmu przychodzimy z nikad
    // Czy Pole P istnieje i czy Pole D istnieje
    if ((!Pole_czy_istnieje(P)) || (!Pole_czy_istnieje(D))) return -61;
    // Czy Pole D jest w aktualnie wczytanym chunku
    if (!Pole_czy_w_chunku(D)) return -60;
    // Pierwszy i drugi bit kazdego Pola to informacja skad doszedl
    if (P.a == D.a-1) {
        if (P.b == D.b) {
            // przyszlismy z lewej - 11
            //printf("Przyszlismy z lewej.\n");
            MazeStorage_ustaw_bit(D, 1, 1);
            MazeStorage_ustaw_bit(D, 2, 1);
        } else return -61; // nie sasiaduja
    } else if (P.a == D.a+1) {
        if (P.b == D.b) {
            // przyszlismy z prawej - 01
            //printf("Przyszlismy z prawej.\n");
            MazeStorage_ustaw_bit(D, 1, 0);
            MazeStorage_ustaw_bit(D, 2, 1);
        } else return -61; // nie sasiaduja
    } else if (P.b == D.b+1) {
        if (P.a == D.a) {
            // przyszlismy z dolu - 10
            //printf("Przyszlismy z dolu.\n");
            MazeStorage_ustaw_bit(D, 1, 1);
            MazeStorage_ustaw_bit(D, 2, 0);
        } else return -61; // nie sasiaduja
    } else if (P.b == D.b-1) {
        if (P.a == D.a) {
            // przyszlismy z gory - 00
            //printf("Przyszlismy z gory.\n");
            MazeStorage_ustaw_bit(D, 1, 0);
            MazeStorage_ustaw_bit(D, 2, 0);
        } else return -61; // nie sasiaduja
    } else return -61; // nie sasiaduja
    return 0;
}

void Pole_skad_doszedl(Pole * P) {
    // Czy Pole P istnieje
    if (!Pole_czy_istnieje(*P)) {
        P = NULL;
        return;
    }
    // Czy Pole D jest w aktualnie wczytanym chunku
    if (!Pole_czy_w_chunku(*P)) {
        P = NULL;
        return;
    }
    // Czy ta informacja juz zostala zapisana,
    // tzn. czy Pole P zostalo odwiedzone
    if (!Pole_czy_odwiedzone(*P)) {
        P = NULL;
        return;
    }
    short int skad_doszedl = MazeStorage_odczytaj_bit(*P, 1);
    skad_doszedl *= 10;skad_doszedl += MazeStorage_odczytaj_bit(*P, 2);
    switch (skad_doszedl) {
        case 0: // przyszlismy z gory - 00
            P->b--;
            break;
        case 1: // przyszlismy z prawej - 01
            P->a++;
            break;
        case 10: // przyszlismy z dolu - 10
            P->b++;
            break;
        case 11: // pprzyszlismy z lewej - 11
            P->a--;
            break;
    }
    return;
}

void MazeStorage_inicjuj(short int l_bitow, short int l_chunkow, short int a, short int b, short int chunk_a, short int chunk_b) {
    // Tu nie sprawdzamy, czy podane do inicjacji dane maja sens!
    labirynt.l_bitow = l_bitow;
    labirynt.l_chunkow = l_chunkow;
    labirynt.a = a;
    labirynt.b = b;
    labirynt.chunk_a = chunk_a;
    labirynt.chunk_b = chunk_b;
    short int max_a_b = a;
    if (b > max_a_b) max_a_b = b;
    if (max_a_b % l_chunkow == 0) labirynt._l_Pol_w_chunku = max_a_b/l_chunkow;
    else labirynt._l_Pol_w_chunku = max_a_b/l_chunkow+1;
    return;
}

void MazeStorage_ustaw_bit(Pole P, short int ktory_bit, short int wartosc) {
    int numer_Pola = _MazeStorage_transformacja_wspolrzednych_Pola(P);
    _MazeStorage_transformacja_3(&numer_Pola, &ktory_bit);
    /// (numer_Pola, ktory_bit) -> (idx, nb)
    // przyklad dla nb 0    i bajtu     00010110:
    uint8_t maska = 1;       // maska = 00000001
    maska <<= (7-ktory_bit); // maska = 10000000
    switch (wartosc) {
        case 1:
            // na wartosc 1
            labirynt.chunk[numer_Pola] |= maska; // OR-ujemy z maska
            // otrzymujemy bajt:        10010110
            break;
        case 0:
            // na wartosc 0
            maska ^= 255;    // maska = 01111111
            labirynt.chunk[numer_Pola] &= maska; // AND-ujemy z maska
            // otrzymujemy bajt:        00010110
            break;
    }
    return;
}

short int MazeStorage_odczytaj_bit(Pole P, short int ktory_bit) {
    int numer_Pola = _MazeStorage_transformacja_wspolrzednych_Pola(P);
    _MazeStorage_transformacja_3(&numer_Pola, &ktory_bit);
    /// (numer_Pola, ktory_bit) -> (idx, nb)
    // przyklad dla nb 0           i bajtu          10010110:
    uint8_t maska = 1;                   // maska = 00000001
    maska <<= (7-ktory_bit);             // maska = 10000000
    if (numer_Pola < 0 || numer_Pola >= MAX_MAZE_STORAGE) { // tu nie powinnismy trafic
        printf("Zly numer Pola!: (%i,%i) %i | %i\n",P.a,P.b,ktory_bit,numer_Pola);
        return 1231;
    }
    maska &= labirynt.chunk[numer_Pola]; // maska = 10000000
    maska >>= (7-ktory_bit);             // maska = 00000001
    return (short int)(maska);
}

void MazeStorage_wyczysc() {
    int i;
    for (i = 0;i < MAX_MAZE_STORAGE;i++) {
        labirynt.chunk[i] = 0; // zeruje wszystkie bity bajta
    }
    return;
}

// ------

// Przeksztalca dwuwymiarowe wspolrzedne Pola P na jednowymiarowy numer Pola
// w odpowiednim dla niego chunku
// Zwraca jednowymiarowy numer Pola P (numerowany od 0)
// Pola o tej samej wzglednej pozycji w roznych chunkach zwroca takie same indeksy
// np. dla labiryntu podzielonego na 2^2 chunki
// (1,1) (2,1) (3,1)|(4,1) (5,1) (6,1)
// (1,2) (2,2) (3,2)|(4,2) (5,2) (6,2)
// (1,3) (2,3) (3,3)|(4,3) (5,3) (6,3)
// -----------------+-----------------
// (1,4) (2,4) (3,4)|(4,4) (5,4) (6,4)
// (1,5) (2,5) (3,5)|(4,5) (5,5) (6,5)
// (1,6) (2,6) (3,6)|(4,6) (5,6) (6,6)
// Pole (5,3) zostanie przeksztalcone na numer 7, tak samo jak Pole (2,3)
// Funkcja zaklada, ze Pole P istnieje
int _MazeStorage_transformacja_wspolrzednych_Pola(Pole P) {
    // Transformacja 1
    // Pole P w chunku (a,b) -> Pole P w chunku (1,1) o wzglednie tych samych wspolrzednych
    //P.a -= (P.a/labirynt._l_Pol_w_chunku)*labirynt._l_Pol_w_chunku;if (P.a == 0) P.a += labirynt._l_Pol_w_chunku;
    //P.b -= (P.b/labirynt._l_Pol_w_chunku)*labirynt._l_Pol_w_chunku;if (P.b == 0) P.b += labirynt._l_Pol_w_chunku;
    P.a %= labirynt._l_Pol_w_chunku;if (P.a == 0) P.a += labirynt._l_Pol_w_chunku;
    P.b %= labirynt._l_Pol_w_chunku;if (P.b == 0) P.b += labirynt._l_Pol_w_chunku;
    // Transformacja 2
    // Pole P o wspolrzednych (a,b) -> jednowymiarowy numer Pola P
    int numer_Pola = (int)(P.b-1); // ostroznie: mozliwosc przepelnienia gdyby wynikiem byl short int
    numer_Pola *= (int)(labirynt._l_Pol_w_chunku); // ostroznie: mozliwosc przepelnienia gdyby wynikiem byl short int
    numer_Pola += (int)(P.a-1);
    return numer_Pola;
}

// Przeksztalca pare (numer_Pola, ktory_bit) -> (idx, nb)
// gdzie:
// idx - indeks Pola w MazeStorage.chunk
// nb  - numer bitu od lewej w bajcie licząc od 0 w indeksie idx MazeStorage.chunk, tzn. MazeStorage.chunk[idx][nb] to ktory_bit Pola numer_Pola
// idx zostanie przekazane do numer_Pola, nb do ktory_bit
void _MazeStorage_transformacja_3(int * numer_Pola, short int * ktory_bit) {
    int sumaryczny_nb; // w short intcie moze sie nie zmiescic
    sumaryczny_nb = (int)labirynt.l_bitow; // ostroznie: mozliwosc przepelnienia gdyby wynikiem byl short int
    sumaryczny_nb *= *numer_Pola;
    sumaryczny_nb += (int)((*ktory_bit)-1);
    *numer_Pola = (int)(sumaryczny_nb / 8);
    *ktory_bit = (short int)(sumaryczny_nb % 8);
    return;
}

// DEBUG: wypisuje MazeStorage
// format:
// 1 - podzial na bajty
// 2 - podzial na l_bitow
void _MazeStorage_wypisz(short int format) {
    short int a,b,ktory_bit;
    Pole P;
    short int l_wyp = 0;
    printf("Chunk (%i,%i):\n",labirynt.chunk_a,labirynt.chunk_b);
    switch (format) {
        case 1:
            for (b = 1;b <= labirynt._l_Pol_w_chunku;b++) {
                P.b = b;
                for (a = 1;a <= labirynt._l_Pol_w_chunku;a++) {
                    P.a = a;
                    for (ktory_bit = 1;ktory_bit <= labirynt.l_bitow;ktory_bit++) {
                        putc((int)(MazeStorage_odczytaj_bit(P,ktory_bit)+48),stdout);
                        // 48 to '0'
                        l_wyp++;
                        if (l_wyp == 8) {
                            putc(32,stdout);
                            // 32 to ' '
                            l_wyp = 0;
                        }
                    }
                }
            }
            break;
        case 2:
            for (b = 1;b <= labirynt._l_Pol_w_chunku;b++) {
                P.b = b;
                for (a = 1;a <= labirynt._l_Pol_w_chunku;a++) {
                    P.a = a;
                    for (ktory_bit = 1;ktory_bit <= labirynt.l_bitow;ktory_bit++) {
                        putc((int)(MazeStorage_odczytaj_bit(P,ktory_bit)+48),stdout);
                        // 48 to '0'
                    }
                    putc(32,stdout);
                    // 32 to ' '
                }
                putc((int)'\n',stdout);
            }
            break;
    }
    printf("\n");
    return;
}