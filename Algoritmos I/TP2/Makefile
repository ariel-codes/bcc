CC = g++
OPCOES = -std=c++14 -O3 -Wall

COMPILADOS = ./obj/
FONTES = ./src/

MAIN = Main
OBJ = $(patsubst $(FONTES)%.cc, $(COMPILADOS)%.o, $(wildcard $(FONTES)*.cc))

$(COMPILADOS)%.o: $(FONTES)%.cc
	$(CC) $(OPCOES) -c $< -o $@ -I./include/

all: $(OBJ)
	$(CC) $(OPCOES) -o ./tp02 $(OBJ)

clean:
	@rm -rf $(COMPILADOS)* ./tp02
