OPAL: file_check solver_BFS solution_output error_messages
	:
file_check: decompressor config.h
	:
decompressor:
	:
config.h:
#	nie musimy tu nic robic
	: 
solver_BFS: queue_BFS chunk_manager chunkenizer maze_storage
	:
queue_BFS: maze_storage config.h # maze_storage.h (bo Pole)
	gcc -Wall --pedantic -c queue_BFS.c
maze_storage: config.h
	:
chunk_manager: chunkenizer maze_storage
	:
chunkenizer: maze_storage
	:
solution_output: maze_storage config.h
	:
error_messages:
	: