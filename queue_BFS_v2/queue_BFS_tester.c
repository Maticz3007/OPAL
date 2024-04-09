// v2 (otwarcie pliku tylko raz w trybie od odczytu i zapisu, skakanie po nim aby odczytywac i zapisywac w odpowiednich miejscach)
#include "queue_BFS.h"
#include "config.h"
#include<stdlib.h>
#include<time.h>

short int los(short int p, short int k) {
    double r = (double)rand()/RAND_MAX;
    r *= (k-p+1);
    r += p;
    short int rint = (short int)r;
    if (rint < p) rint = p;
    if (rint > k) rint = k;
    return rint;
}
void losowy_element(kolejka_element * zwrocony_element) {
    zwrocony_element->PoleD.a = los(1,100);zwrocony_element->PoleD.b = los(1,100);
    zwrocony_element->PoleP.a = los(1,100);zwrocony_element->PoleP.b = los(1,100);
}
void ustaw_element_0(kolejka_element * zwrocony_element) {
    zwrocony_element->PoleD.a = 0;zwrocony_element->PoleD.b = 0;
    zwrocony_element->PoleP.a = 0;zwrocony_element->PoleP.b = 0;
}
void test_wrzuc(kolejka * Q, kolejka_element element) {
    //printf("Wrzucam ((%i,%i),(%i,%i))\n",element.PoleD.a,element.PoleD.b,element.PoleP.a,element.PoleP.b);
    short int wynik = kolejka_wrzuc(Q,element);
    //printf("kolejka_wrzuc:%i\n",wynik);
}
void test_zrzuc(kolejka * Q, kolejka_element * elem) {
    kolejka_element element;
    element.PoleD.a = 0;element.PoleD.b = 0;
    element.PoleP.a = 0;element.PoleP.b = 0;
    short int wynik = kolejka_zrzuc(Q,&element);
    //printf("kolejka_zrzuc:%i\n",wynik);
    elem->PoleD.a = element.PoleD.a;
    elem->PoleD.b = element.PoleD.b;
    elem->PoleP.a = element.PoleP.a;
    elem->PoleP.b = element.PoleP.b;
    //printf("Odczytalem ((%i,%i),(%i,%i))\n",element.PoleD.a,element.PoleD.b,element.PoleP.a,element.PoleP.b);
    if (element.PoleD.a < 1 || element.PoleD.b < 1 || element.PoleP.a < 1 || element.PoleP.b < 1) {
        if (element.PoleD.a == 0 && element.PoleD.b == 0 && element.PoleP.a == 0 && element.PoleP.b == 0) {
            //printf("Skonczyly sie elementy.\n");
        } else {
            printf("Cos poszlo nie tak 1.\n");
            abort();
        }
    }
    if (element.PoleD.a > 100 || element.PoleD.b > 100 || element.PoleP.a > 100 || element.PoleP.b > 100) {
        printf("Cos poszlo nie tak 2.\n");
        abort();
    }
}
short int te_same_elementy(kolejka_element elem1, kolejka_element elem2) {
    return (elem1.PoleD.a == elem2.PoleD.a && elem1.PoleD.b == elem2.PoleD.b && elem1.PoleP.a == elem2.PoleP.a && elem1.PoleP.b == elem2.PoleP.b);
}
/*void test_zrzuc(kolejka * Q) {
    printf("zrzuc:%i\n",kolejka_zrzuc(Q));
}*/

int main(int argc, char ** argv) {
    kolejka Q0;kolejka Q1; // Kolejka Q0 w trybie 0, kolejka Q1 w trybie 1
    kolejka_inicjuj(&Q0);
    kolejka_inicjuj(&Q1);
    srand(time(NULL));
    char kolejka_plik[MAX_SCIEZKA];
    //sprintf(kolejka_plik,KOLEJKA_FORMAT_SCIEZKI_PLIKU,(void *)(&Q));
    //sprintf(kolejka_plik,KOLEJKA_FORMAT_SCIEZKI_PLIKU);
    _kolejka_sciezka_do_pliku(&Q1,kolejka_plik);
    printf("sciezka do pliku:%s\n",kolejka_plik);
    //printf("%s\n",kolejka_sciezka);
    printf("zrob plik:%i\n",_kolejka_zrob_plik(&Q1));Q1.tryb = 1; // Testujemy tryb z plikiem
    int i;
    kolejka_element elem0;kolejka_element elem1;kolejka_element elem2;
    ustaw_element_0(&elem1);ustaw_element_0(&elem2);
    for (i = 0;i < 10000;i++) {
        if (Q0.lel != Q1.lel) {
            printf("Nie zgadza sie lel kolejek:%i %i",Q0.lel,Q1.lel);
            abort();
        }
        switch (los(1,2)) {
            case 1:
                //if (Q0.lel != MAX_KOLEJKA) {
                    losowy_element(&elem0);
                    test_wrzuc(&Q0,elem0);
                    test_wrzuc(&Q1,elem0);
                    break;
                /*} else {
                    test_zrzuc(&Q0,&elem1);
                    test_zrzuc(&Q1,&elem2);
                    break;
                }*/
            case 2:
                test_zrzuc(&Q0,&elem1);
                test_zrzuc(&Q1,&elem2);
                break;
        }
        if (!te_same_elementy(elem1,elem2)) {
            printf("Kolejki Q0 i Q1 dzialaja inaczej!\n");
            abort();
        }
    }
    /*
    test_wrzuc(&Q);
    test_wrzuc(&Q);
    test_wrzuc(&Q);
    test_zrzuc(&Q);
    test_zrzuc(&Q);
    test_zrzuc(&Q);
    */
    printf("zniszcz:%i\n",kolejka_zniszcz(&Q0));
    printf("zniszcz:%i\n",kolejka_zniszcz(&Q1));
    return 0;
}