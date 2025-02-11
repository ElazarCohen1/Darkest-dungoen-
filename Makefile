# Variables
MLVC = C:\Users\elaza\OneDrive\Bureau\mlv-2.0.2\MLV
ZIPFILE =  L2S3.Projet.COHEN_ELAZAR.zip
SRCS = $(wildcard *.c)           # Trouve tous les fichiers .c dans le répertoire
OBJS = $(SRCS:.c=.o)             # Génère la liste des fichiers .o correspondants
HEADER = $(wildcard *.h)
TARGET = projet                    	# Nom de l'exécutable final

CC = clang
CFLAGS = -Wall -std=c17  -g
 # Options de lien et Inclut MLVC dans les chemins d'inclusion
#pour le wsl 
#LDFLAGS = -I $(MLVC)  -L$(MLVC) -lMLV  

#pour linux
LDFLAGS = -lMLV

# Règle par défaut (compilation complète)
all: $(TARGET)

# Règle pour l'exécutable
# $@ : le nom de la cible (TARGET)
# $^ : la listes des dependances (tout les fichier objet)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^   

# compiler les fichiers objets
# $< : la premiere dependance 
#on cree un fichier o pour chaque fichier c 
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour créer un fichier ZIP
zip: clean
	zip -r $(ZIPFILE) $(SRCS) $(HEADER) save.txt rapport.pdf Makefile image font

# Nettoyer les fichiers générés
clean:
	rm -f $(OBJS) $(TARGET) 

# Nettoyage complet (le fichier zip en plus)
distclean: clean
	rm -f $(ZIPFILE)
