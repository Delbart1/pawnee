# Fichier Makefile racine

# Variable contenant tous les répertoires.

FOLDERS=webserver

.PHONY: all &(FOLDERS)

# Make sans argument

all: $(FOLDERS)

# Lancement de make dans webserver

webserver:
	make -C webserver
