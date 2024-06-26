#ifndef CONFIG_IS_INCLUDED
#define CONFIG_IS_INCLUDED

#define MAX_SCIEZKA 500 // zakladamy, ze dlugosc sciezki do pliku nie przekroczy 500 znakow (tylko dla Windowsa)

//#define MAX_CHUNKI_PIERW 3 // w sumie max 9 chunkow
#define MAX_CHUNKI_PIERW 1

#define MAX_A_B 1024 // maksimum z mozliwych wymiarow labiryntu - max(a,b).

#define MAX_MAZE_STORAGE 393217 // okolo, moze wiecej lub mniej aby przechowac caly labirynt na raz
// 393217 * 8 == 3145736 > 3145728 == 1024*1024*3

//#define MAX_MAZE_STORAGE 98305 // jesli przyjmiemy ze chunk ma maksymalny rozmiar 512x512
// 98305 * 8 == 786440 > 786432 == 512*512*3

#define MAX_KOLEJKA (2*MAX_A_B+1)

#ifdef WIN32 /// Windows
#define OS_WINDOWS
#define TEMP_DIR "%Temp%\\" // Trzeba jeszcze rozwinac to do odpowiedniej wartosci
#else // Linux, MacOS, itp itd
#define OS_LINUX
#define TEMP_DIR "/tmp/"
#endif

#endif // CONFIG_IS_INCLUDED