OBJECTS= ./build/compiler.o ./build/compiler_process.o
INCLUDES= -I./

all: ${OBJECTS}
	gcc main.c ${INCLUDES} ${OBJECTS} -g -o ./flausinocc

./build/compiler.o: compiler.c
	gcc compiler.c ${INCLUDES} -g -o ./build/compiler.o -c 

./build/compiler_process.o: compiler_process.c
	gcc compiler_process.c ${INCLUDES} -g -o ./build/compiler_process.o -c

clean:
	rm ./flausinocc
	rm -rf ${OBJECTS}
