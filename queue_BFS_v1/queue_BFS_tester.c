// v1 (proba otwarcia tego samego pliku w 2 roznych miejscach i trybach, aby raz odczytywac a raz zapisywac - NIE UDALO SIE)
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
void test_wrzuc(kolejka * Q) {
    kolejka_element element;
    element.PoleD.a = los(1,100);element.PoleD.b = los(1,100);
    element.PoleP.a = los(1,100);element.PoleP.b = los(1,100);
    printf("Wrzucam ((%i,%i),(%i,%i))\n",element.PoleD.a,element.PoleD.b,element.PoleP.a,element.PoleP.b);
    printf("kolejka_wrzuc:%i\n",kolejka_wrzuc(Q,element));
}
void test_zrzuc(kolejka * Q) {
    kolejka_element element;
    element.PoleD.a = 0;element.PoleD.b = 0;
    element.PoleP.a = 0;element.PoleP.b = 0;
    printf("kolejka_zrzuc:%i\n",kolejka_zrzuc(Q,&element));
    printf("Odczytalem ((%i,%i),(%i,%i))\n",element.PoleD.a,element.PoleD.b,element.PoleP.a,element.PoleP.b);
}
/*void test_zrzuc(kolejka * Q) {
    printf("zrzuc:%i\n",kolejka_zrzuc(Q));
}*/

int main(int argc, char ** argv) {
    kolejka Q;
    kolejka_inicjuj(&Q);
    srand(time(NULL));
    char kolejka_plik[MAX_SCIEZKA];
    //sprintf(kolejka_plik,KOLEJKA_FORMAT_SCIEZKI_PLIKU,(void *)(&Q));
    //sprintf(kolejka_plik,KOLEJKA_FORMAT_SCIEZKI_PLIKU);
    _kolejka_sciezka_do_pliku(&Q,kolejka_plik);
    printf("sciezka do pliku:%s\n",kolejka_plik);
    Q.tryb = 1; // Testujemy tryb z plikiem
    //printf("%s\n",kolejka_sciezka);
    printf("zrob plik:%i\n",_kolejka_zrob_plik(&Q));
    /*int i;
    for (i = 0;i < 100;i++) {
        switch (los(1,2)) {
            case 1:
                test_wrzuc(&Q);
                break;
            case 2:
                test_zrzuc(&Q);
                break;
        }
    }*/
    test_wrzuc(&Q);
    test_wrzuc(&Q);
    test_wrzuc(&Q);
    test_zrzuc(&Q);
    test_zrzuc(&Q);
    test_zrzuc(&Q);
    //printf("usun plik:%i\n",_kolejka_usun_plik(&Q));
    return 0;
}