
OBJ_DIR=obj
SRC_DIR=src

SRC=$(wildcard $(SRC_DIR)/*.cpp)

COMP=g++

all:
ifeq ($(wildcard $(OBJ_DIR)/*),)
	mkdir $(OBJ_DIR)
endif
	g++ -c $(SRC)
	mv *.o $(OBJ_DIR)

clean:
	rm *.o
