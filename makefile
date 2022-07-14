FLAGS = -g -Wall -Wextra -Werror -std=c99

main: main.o sugerencias.o tablahash.o slist.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c sugerencias.h tablahash.h slist.h
	$(CC) -c $< $(FLAGS)

sugerencias.o: sugerencias.c sugerencias.h tablahash.h
	$(CC) -c $< $(FLAGS)

tablahash.o: tablahash.c tablahash.h slist.h
	$(CC) -c $< $(FLAGS)	

slist.o: slist.c slist.h
	$(CC) -c $< $(FLAGS)	

clean:
	rm *.o
	rm main

.PHONY = clean