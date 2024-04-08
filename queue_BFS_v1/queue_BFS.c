#include "maze_storage.h" // Pole
#include "queue_BFS.h"

#ifdef OS_WINDOWS
#include<processenv.h> // ExpandEnvironmentStringsA - do uzyskania wartosci %Temp%
#endif

void kolejka_inicjuj(kolejka * Q) {
    Q->lel = 0;
    Q->poczatek = 0;
    Q->koniec = 0;
    Q->plik_poczatek = NULL;
    Q->plik_koniec = NULL;
    Q->tryb = 0;
}

void koleka_zniszcz(kolejka * Q) {
    if (Q->tryb == 1) {
        _kolejka_usun_plik(Q);
        kolejka_inicjuj(Q); // reset do domyslnych wartosci
    }
}

short int kolejka_wrzuc(kolejka * Q, kolejka_element element) {
    if (Q->tryb == 0) {
        if (Q->lel == MAX_KOLEJKA) {
            short int nie_udalo_sie = _kolejka_przepisz(Q);
            if (nie_udalo_sie) return nie_udalo_sie;
            Q->tryb = 1;
            return kolejka_wrzuc(Q,element);
        } else {
            Q->kol[Q->koniec].PoleD.a = element.PoleD.a;
            Q->kol[Q->koniec].PoleD.b = element.PoleD.b;
            Q->kol[Q->koniec].PoleP.a = element.PoleP.a;
            Q->kol[Q->koniec].PoleP.b = element.PoleP.b;
            Q->koniec++;
            if (Q->koniec == MAX_KOLEJKA) Q->koniec = 0;
            Q->lel++;
        }
    } else {
        //printf("BLABLABLA%p\n",(void *)Q->plik_koniec);
        if (fprintf(Q->plik_koniec,"%i %i %i %i\n", element.PoleD.a, element.PoleD.b, element.PoleP.a, element.PoleP.b) < 0) {
            return -30;
        } else Q->lel++;
    }
    return 0;
}

// zamiast kolejka_przod, od razu zrzucamy element po odczytaniu
short int kolejka_zrzuc(kolejka * Q, kolejka_element * zwrocony_element) {
    if (Q->lel == 0) {
        return 1235;
    }
    if (Q->tryb == 0) {
        zwrocony_element->PoleD.a = Q->kol[Q->poczatek].PoleD.a;
        zwrocony_element->PoleD.b = Q->kol[Q->poczatek].PoleD.b;
        zwrocony_element->PoleP.a = Q->kol[Q->poczatek].PoleP.a;
        zwrocony_element->PoleP.b = Q->kol[Q->poczatek].PoleP.b;
        //zwrocony_element = Q->kol+Q->poczatek; - element jest zmienna lokalna, wiec pozniej wskaznik nic nie bedzie znaczyl
        // Jeszcze trzeba zrzucic element z kolejki
        Q->poczatek++;
        if (Q->poczatek == MAX_KOLEJKA) Q->poczatek = 0;
        Q->lel--;
    } else {
        kolejka_element element;
        //element.PoleD.a = 0;element.PoleD.b = 0;element.PoleP.a = 0;element.PoleP.b = 0;
        int odczyt = fscanf(Q->plik_poczatek,"%hi %hi %hi %hi",&element.PoleD.a,&element.PoleD.b,&element.PoleP.a,&element.PoleP.b);
        printf("odczyt:%i\n",odczyt);
        if (ferror(Q->plik_poczatek)) printf("Wystapil blad przy czytaniu.\n");
        if (feof(Q->plik_poczatek)) printf("Wystapil EOF przy czytaniu.\n");
        if (odczyt == EOF) printf("odczyt to EOF.\n");
        if (ferror(Q->plik_poczatek) || element.PoleP.b == 0) {
            printf("fail:%i %i %i %i\n",element.PoleD.a,element.PoleD.b,element.PoleP.a,element.PoleP.b);
            zwrocony_element = NULL;
            return 1234;
        } else {
            //zwrocony_element = &element; - element jest zmienna lokalna, wiec pozniej wskaznik nic nie bedzie znaczyl
            zwrocony_element->PoleD.a = element.PoleD.a;
            zwrocony_element->PoleD.b = element.PoleD.b;
            zwrocony_element->PoleP.a = element.PoleP.a;
            zwrocony_element->PoleP.b = element.PoleP.b;
            Q->lel--; /// Od razu zrzucamy element z kolejki gdy odczytujemy go z pliku
        }
    }
    return 0;
}

short int _kolejka_przepisz(kolejka * Q) {
    unsigned short int lel_tryb_0 = Q->lel;
    unsigned short int lel_tryb_1 = lel_tryb_0;
    short int nie_udalo_sie;
    while (lel_tryb_0 > 0) {
        kolejka_element element;
        nie_udalo_sie = kolejka_zrzuc(Q, &element);
        if (nie_udalo_sie) return nie_udalo_sie;
        lel_tryb_0--;
        Q->tryb = 1;
        nie_udalo_sie = kolejka_wrzuc(Q, element);
        if (nie_udalo_sie) return nie_udalo_sie;
        Q->tryb = 0;
    }
    Q->lel = lel_tryb_1;
    return 0;
}

/*
short int kolejka_zrzuc(kolejka * Q) {
    if (Q->lel == 0) return 4234;
    if (Q->tryb == 0) {
        // ...
    } else {
        // Nic nie musimy robic, kolejka_przod zrzuca elementy
    }
    return 0;
}
*/



//

void _kolejka_sciezka_do_pliku(kolejka * Q, char * zwrocona_sciezka) {
#ifdef OS_WINDOWS // Na Windowsie trzeba uzyskac wartosc %Temp% z TEMP_DIR
    char kolejka_sciezka[MAX_SCIEZKA];
    ExpandEnvironmentStringsA(TEMP_DIR,kolejka_sciezka,MAX_SCIEZKA);
#else
    char kolejka_sciezka[] = TEMP_DIR;
#endif
    sprintf(zwrocona_sciezka,KOLEJKA_FORMAT_SCIEZKI_PLIKU,kolejka_sciezka,(void *)Q);
    //sprintf(zwrocona_sciezka,KOLEJKA_FORMAT_SCIEZKI_PLIKU,kolejka_sciezka);
}

short int _kolejka_zrob_plik(kolejka * Q) {
    char kolejka_plik[MAX_SCIEZKA];
    _kolejka_sciezka_do_pliku(Q,kolejka_plik);
    //sprintf(kolejka_plik,KOLEJKA_FORMAT_SCIEZKI_PLIKU,(void *)Q);
    //sprintf(kolejka_plik,KOLEJKA_FORMAT_SCIEZKI_PLIKU);
    //printf(KOLEJKA_FORMAT_SCIEZKI_PLIKU,(void *)Q);
    //printf("\n");
    Q->plik_koniec = fopen(kolejka_plik,"w");
    if (Q->plik_koniec == NULL) return 4234;
    Q->plik_poczatek = fopen(kolejka_plik,"r");
    if (Q->plik_koniec == NULL) return 2344;
    return 0;
}

short int _kolejka_usun_plik(kolejka * Q) {
    if (Q->plik_poczatek != NULL) fclose(Q->plik_poczatek);
    if (Q->plik_poczatek != NULL) fclose(Q->plik_koniec);
    char kolejka_plik[MAX_SCIEZKA];
    _kolejka_sciezka_do_pliku(Q,kolejka_plik);
    //sprintf(kolejka_plik,KOLEJKA_FORMAT_SCIEZKI_PLIKU,(void *)Q);
    //sprintf(kolejka_plik,KOLEJKA_FORMAT_SCIEZKI_PLIKU);
    if (remove(kolejka_plik) != 0) return 3241;
    return 0;
}