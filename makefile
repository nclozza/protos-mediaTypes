COMPILER=gcc
OUTPUT_FILE=match
FILES=match.c validate.c queue.c
FLAGS=--pedantic -Wall
all:
	$(COMPILER) $(FLAGS) $(FILES) -o $(OUTPUT_FILE)
