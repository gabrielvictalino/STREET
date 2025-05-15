CC=gcc
CFLAGS=-Wall -std=c99 -O2 -Iinclude
LDFLAGS=-lraylib -lm -ldl -lpthread -lGL -lX11

FONTES=src/jogo.c src/player.c src/obstacle.c src/score.c
OBJETOS=$(FONTES:.c=.o)
EXECUTAVEL=street

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJETOS) $(EXECUTAVEL)
