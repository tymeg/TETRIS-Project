# Makefile dla gry TETRIS by TYMEG

CC=gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
# ogolne flagi kompilacji dla modulow

LFLAGS = -lm
# ogolne flagi konsolidacji programu

NAME = TETRIS 	# nazwa programu wynikowego
DEPS = blocks.h	  # nazwy plików nagłówkowych, z których korzysta każdy moduł 
OBJS = main.o game_state.o show.o   # nazwy wszystkich modułów (binarnych)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

game_state.o: game_state.c show.h $(DEPS)
	$(CC) $(CFLAGS) -c game_state.c -o game_state.o	

main.o: main.c game_state.h show.h $(DEPS)
	$(CC) $(CFLAGS) -c main.c -o main.o

show.o: show.c $(DEPS)
	$(CC) $(CFLAGS) -c show.c -o show.o

clean:
	rm -f $(OBJS) $(NAME)
