HEADERS = shm_header.h

default: sharedmemory_writer 

sharedmemory_writer.o: sharedmemory_writer.c $(HEADERS)
	gcc -c -D_REENTRANT sharedmemory_writer.c -lpthread -o sharedmemory_writer.o -lm

sharedmemory_reader.o: sharedmemory_reader.c $(HEADERS)
	gcc -c -D_REENTRANT sharedmemory_reader.c -lpthread -o sharedmemory_reader.o -lm

sharedmemory_writer: sharedmemory_writer.o
	gcc -D_REENTRANT sharedmemory_writer.o -lpthread -o sharedmemory_writer -lm

sharedmemory_reader: sharedmemory_reader.o
	gcc -D_REENTRANT sharedmemory_reader.o -lpthread -o sharedmemory_reader -lm

clean:
	-rm -f sharedmemory_writer.o
	-rm -f sharedmemory_writer
	-rm -f sharedmemory_reader.o
	-rm -f sharedmemory_reader
