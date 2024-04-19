
OBJ_DIR=obj
SRC_DIR=src

SRC=$(wildcard $(SRC_DIR)/*.cpp)

COMP=g++

all:
	@mkdir -p $(OBJ_DIR)
	g++ -c $(SRC)
	mv *.o $(OBJ_DIR)

clean:
	rm *.o
