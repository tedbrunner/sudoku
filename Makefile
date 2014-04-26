
all: sudoku

CC = g++
COPTS += -DGCC -DLINUX

LOPTS = -lstdc++ -lm -lpthread

SVR_CC_FILES = sudoku.cc
SVR_HH_FILES = sudoku.hh
SVR_OBJ_FILES= sudoku.o

sudoku: $(SVR_OBJ_FILES)
	$(CC) $(LOPTS) $(SVR_OBJ_FILES) -o sudoku

sudoku.o: $(SVR_CC_FILES) $(SVR_HH_FILES)
	$(CC) $(COPTS) -c sudoku.cc

clean:
	rm -f sudoku *.o




