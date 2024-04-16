OPAL: file_check solver_BFS solution_output error_messages
#	gcc main.c solver_BFS.c queue_BFS.c chunkenizer.c chunk_manager.c maze_storage.c RLE_decompressor.c solution_output.c file_check.c error_messages.c -Wall --pedantic -lm -ggdb
	gcc main.c solver_BFS.o queue_BFS.o chunkenizer.o chunk_manager.o maze_storage.o RLE_decompressor.o solution_output.o file_check.o error_messages.o -Wall --pedantic -lm
file_check: decompressor config.h
	gcc -Wall --pedantic -c file_check.c
decompressor:
	gcc -Wall --pedantic -c RLE_decompressor.c
config.h:
#	nie musimy tu nic robic
	: 
solver_BFS: queue_BFS chunk_manager chunkenizer maze_storage
	gcc -Wall --pedantic -c solver_BFS.c
queue_BFS: maze_storage config.h # maze_storage.h (bo Pole)
	gcc -Wall --pedantic -c queue_BFS.c
maze_storage: config.h
	gcc -Wall --pedantic -c maze_storage.c
chunk_manager: chunkenizer maze_storage
	gcc -Wall --pedantic -c chunk_manager.c
chunkenizer: maze_storage
	gcc -Wall --pedantic -c chunkenizer.c
solution_output: maze_storage config.h
	gcc -Wall --pedantic -c solution_output.c
error_messages:
	gcc -Wall --pedantic -c error_messages.c
maze_storage_tester: #maze_storage komilujemy tutaj prz testowaniu
	gcc -Wall --pedantic -ggdb maze_storage_tester.c maze_storage.c -o maze_storage_tester.out
#	gcc -Os maze_storage_tester.c maze_storage.c -o maze_storage_tester.out