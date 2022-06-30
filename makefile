FLAGS = -g -Wall -Wextra -Werror -std=c99

main: main.o utils.o tablahash.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c utils.h tablahash.h
	$(CC) -c $< $(FLAGS)

utils.o: utils.c utils.h
	$(CC) -c $< $(FLAGS)

tablahash.o: tablahash.c tablahash.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm main

.PHONY = clean