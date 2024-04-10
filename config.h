#ifndef CONFIG_IS_INCLUDED
#define CONFIG_IS_INCLUDED

#define MAX_SCIEZKA 500 // zakladamy, ze dlugosc sciezki do pliku nie przekroczy 500 znakow (tylko dla Windowsa)

#ifdef WIN32 /// Windows
#define OS_WINDOWS
#define TEMP_DIR "%Temp%\\" // Trzeba jeszcze rozwinac to do odpowiedniej wartosci
#else // Linux, MacOS, itp itd
#define OS_LINUX
#define TEMP_DIR "/tmp/"
#endif

#endif // CONFIG_IS_INCLUDED