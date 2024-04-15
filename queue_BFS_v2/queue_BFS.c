// v2 (otwarcie pliku tylko raz w trybie od odczytu i zapisu, skakanie po nim aby odczytywac i zapisywac w odpowiednich miejscach)
#include "maze_storage.h" // Pole
#include "queue_BFS.h"

#ifdef OS_WINDOWS
#include<processenv.h> // ExpandEnvironmentStringsA - do uzyskania wartosci %Temp%
#endif

void Kolejka_inicjuj(Kolejka * Q) {
    Q->lel = 0;
    Q->poczatek = 0;
    Q->koniec = 0;
    Q->plik = NULL;
    Q->plik_poczatek = 0;
    Q->plik_koniec = 0;
    Q->tryb = 0;
}

short int Kolejka_zniszcz(Kolejka * Q) {
    if (Q->tryb == 1) {
        short int czy_udalo_sie = _Kolejka_usun_plik(Q);
        Kolejka_inicjuj(Q); // reset do domyslnych wartosci
        return czy_udalo_sie;
    }
    Kolejka_inicjuj(Q); // reset do domyslnych wartosci
    return 0;
}

short int Kolejka_wrzuc(Kolejka * Q, KolejkaElement element) {
    if (Q->tryb == 0) {
        if (Q->lel == MAX_KOLEJKA) {
            short int nie_udalo_sie;
            nie_udalo_sie = _Kolejka_przepisz(Q);
            if (nie_udalo_sie) return nie_udalo_sie;
            Q->tryb = 1;
            return Kolejka_wrzuc(Q,element);
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
        //printf("TESTESTEST%p\n",(void *)Q->plik_koniec);
        // Nie mozemy uzyc \n jako separatora, bo wtedy czasami psuje sie synchronizacja miedzy zapisem a odczytem
        if (fprintf(Q->plik,"%i %i %i %i|", element.PoleD.a, element.PoleD.b, element.PoleP.a, element.PoleP.b) < 0) {
            Kolejka_zniszcz(Q); // Gdy cos tu pojdzie nie tak od razu zniszczymy kolejke wraz z jej plikiem
            return -30;
        } else {
            Q->plik_koniec++;
            Q->lel++;
        }
    }
    return 0;
}

// zamiast Kolejka_przod, od razu zrzucamy element po odczytaniu
short int Kolejka_zrzuc(Kolejka * Q, KolejkaElement * zwrocony_element) {
    if (Q->lel == 0) {
        // Tu nie niszczymy kolejki
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
        KolejkaElement element;
        //element.PoleD.a = 0;element.PoleD.b = 0;element.PoleP.a = 0;element.PoleP.b = 0;
        rewind(Q->plik); // Cofamy sie na poczatek pliku, aby odczytac przod kolejki
        int i; // Musimy przejsc przez niepotrzebne elementy na poczatku pliku
        char sep;
        for (i = 0;i < Q->plik_poczatek;i++) fscanf(Q->plik,"%hi %hi %hi %hi %c",&element.PoleD.a,&element.PoleD.b,&element.PoleP.a,&element.PoleP.b,&sep);
        /*int odczyt = */fscanf(Q->plik,"%hi %hi %hi %hi %c",&element.PoleD.a,&element.PoleD.b,&element.PoleP.a,&element.PoleP.b,&sep);
        Q->plik_poczatek++;
        /*printf("odczyt:%i\n",odczyt);
        if (ferror(Q->plik)) printf("Wystapil blad przy czytaniu.\n");
        if (feof(Q->plik)) printf("Wystapil EOF przy czytaniu.\n");
        if (odczyt == EOF) printf("odczyt to EOF.\n");*/
        int nie_udalo_sie = (ferror(Q->plik) || element.PoleP.b < 1);
        // Teraz musimy przesunac Q->plik do poprzedniego miejsca na koncu kolejki
        rewind(Q->plik);
        short int smiec;
        for (i = 0;i < Q->plik_koniec;i++) fscanf(Q->plik,"%hi %hi %hi %hi %c",&smiec,&smiec,&smiec,&smiec,&sep);
        // Zwracamy element na przodzie
        if (nie_udalo_sie) {
            //printf("fail:%i %i %i %i\n",element.PoleD.a,element.PoleD.b,element.PoleP.a,element.PoleP.b); // DEBUG
            zwrocony_element = NULL;
            Kolejka_zniszcz(Q); // Gdy cos tu pojdzie nie tak od razu zniszczymy kolejke wraz z jej plikiem
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

short int _Kolejka_przepisz(Kolejka * Q) {
    printf("Przechodzimy w tryb 1!\n"); // DEBUG żeby można było zobaczyć kiedy zacznie spadać wydajność
    unsigned short int lel_tryb_0 = Q->lel;
    unsigned short int lel_tryb_1 = lel_tryb_0;
    short int nie_udalo_sie;
    nie_udalo_sie = _Kolejka_zrob_plik(Q);
    if (nie_udalo_sie) return nie_udalo_sie;
    while (lel_tryb_0 > 0) {
        KolejkaElement element;
        nie_udalo_sie = Kolejka_zrzuc(Q, &element);
        if (nie_udalo_sie) return nie_udalo_sie;
        lel_tryb_0--;
        Q->tryb = 1;
        nie_udalo_sie = Kolejka_wrzuc(Q, element);
        if (nie_udalo_sie) return nie_udalo_sie;
        Q->tryb = 0;
    }
    Q->lel = lel_tryb_1;
    return 0;
}

//

void _Kolejka_sciezka_do_pliku(Kolejka * Q, char * zwrocona_sciezka) {
#ifdef OS_WINDOWS // Na Windowsie trzeba uzyskac wartosc %Temp% z TEMP_DIR
    char Kolejka_sciezka[MAX_SCIEZKA];
    ExpandEnvironmentStringsA(TEMP_DIR,Kolejka_sciezka,MAX_SCIEZKA);
#else
    char Kolejka_sciezka[] = TEMP_DIR;
#endif
    sprintf(zwrocona_sciezka,KOLEJKA_FORMAT_SCIEZKI_PLIKU,Kolejka_sciezka,(void *)Q);
    //sprintf(zwrocona_sciezka,KOLEJKA_FORMAT_SCIEZKI_PLIKU,Kolejka_sciezka);
}

short int _Kolejka_zrob_plik(Kolejka * Q) {
    char Kolejka_plik[MAX_SCIEZKA];
    _Kolejka_sciezka_do_pliku(Q,Kolejka_plik);
    FILE * plik = fopen(Kolejka_plik,"w+");
    if (plik == NULL) return 4234;
    Q->plik = plik;
    return 0;
}

short int _Kolejka_usun_plik(Kolejka * Q) {
    //if (Q->plik_poczatek != NULL) fclose(Q->plik_poczatek);
    //if (Q->plik_poczatek != NULL) fclose(Q->plik_koniec);
    if (Q->plik != NULL) fclose(Q->plik);
    char Kolejka_plik[MAX_SCIEZKA];
    _Kolejka_sciezka_do_pliku(Q,Kolejka_plik);
    if (remove(Kolejka_plik) != 0) return 3241; // jesli plik zostanie usuniety wczesniej, to rowniez wywola to blad
    return 0;
}