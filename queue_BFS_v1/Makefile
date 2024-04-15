# v1 (proba otwarcia tego samego pliku w 2 roznych miejscach i trybach, aby raz odczytywac a raz zapisywac - NIE UDALO SIE)
queue_BFS_tester: queue_BFS
	gcc -Wall --pedantic -ggdb queue_BFS_tester.c queue_BFS.c -o queue_BFS_tester.out
	rm *.o
queue_BFS: maze_storage.h config.h #maze_storage.h (bo Pole), config.h (TEMP_DIR, ...)
	gcc -Wall --pedantic -c queue_BFS.c
maze_storage.h:
	cp -f ./../maze_storage.h .
config.h:
	cp -f ./../config.h .