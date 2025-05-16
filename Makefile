# Compilador e flags
CC = gcc
CFLAGS = -Wall -std=c99 -O2 -Iinclude

# Arquivos
OBJETOS = src/jogo.o src/player.o src/obstacle.o src/score.o src/mapa.o
EXECUTAVEL = street

# Regra principal
$(EXECUTAVEL): $(OBJETOS)
	$(CC) -o $(EXECUTAVEL) $(OBJETOS) -lraylib -lm -ldl -lpthread -lGL -lX11

# Regras para cada .o
src/jogo.o: src/jogo.c include/player.h include/obstacle.h include/score.h include/mapa.h
	$(CC) $(CFLAGS) -c -o src/jogo.o src/jogo.c

src/player.o: src/player.c include/player.h
	$(CC) $(CFLAGS) -c -o src/player.o src/player.c

src/obstacle.o: src/obstacle.c include/obstacle.h
	$(CC) $(CFLAGS) -c -o src/obstacle.o src/obstacle.c

src/score.o: src/score.c include/score.h
	$(CC) $(CFLAGS) -c -o src/score.o src/score.c

src/mapa.o: src/mapa.c include/mapa.h
	$(CC) $(CFLAGS) -c -o src/mapa.o src/mapa.c

# Limpar arquivos compilados
clean:
	rm -f src/*.o $(EXECUTAVEL)
