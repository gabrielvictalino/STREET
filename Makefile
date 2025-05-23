# Compilador e flags
CC = gcc
CFLAGS = -Wall -std=c99 -O2 -Iinclude

# Nome do executável
EXECUTAVEL = street

# Arquivos fonte e objeto
SRC_DIR = src
SRC = $(SRC_DIR)/jogo.c \
      $(SRC_DIR)/player.c \
      $(SRC_DIR)/obstacle.c \
      $(SRC_DIR)/score.c \
      $(SRC_DIR)/mapa.c \
      $(SRC_DIR)/enemy.c \
      $(SRC_DIR)/predio.c

OBJ = $(SRC:.c=.o)

# Detecta o sistema operacional e ajusta as bibliotecas
ifeq ($(OS),Windows_NT)
    # Para Windows
    LDFLAGS = -lraylib -lwinmm -lgdi32
    EXECUTAVEL := $(EXECUTAVEL).exe
else
    # Para Linux
    LDFLAGS = -lraylib -lm -ldl -lpthread -lGL -lX11
endif

# Regra principal
all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJ)
    $(CC) -o $@ $^ $(LDFLAGS)

# Compilação dos .c para .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
    $(CC) $(CFLAGS) -c -o $@ $<

# Executar o jogo
run: $(EXECUTAVEL)
    ./$(EXECUTAVEL)

# Limpar arquivos compilados
clean:
    rm -f $(SRC_DIR)/*.o $(EXECUTAVEL)