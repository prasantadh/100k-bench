binaries=create_files create_processes create_threads launch_programs mem_alloc

.PHONY: all
all: $(binaries)

create_files: create_files.c
	gcc create_files.c -o $@

create_processes: create_processes.c
	gcc create_processes.c -o $@

create_threads: create_threads.c
	gcc create_threads.c -o $@

launch_programs: launch_programs.c
	gcc launch_programs.c -o $@

mem_alloc: mem_alloc.c
	gcc mem_alloc.c -o $@

clean:
	rm -rf $(binaries)
