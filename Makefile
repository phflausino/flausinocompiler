OBJECTS= ./build/compiler.o ./build/compiler_process.o ./build/utils/list.o ./build/lexer.o ./build/lex_process.o
INCLUDES= -I./

all: ${OBJECTS}
	gcc main.c ${INCLUDES} ${OBJECTS} -g -o ./flausinocc

./build/compiler.o: compiler.c
	gcc compiler.c ${INCLUDES} -g -o ./build/compiler.o -c 

./build/compiler_process.o: compiler_process.c
	gcc compiler_process.c ${INCLUDES} -g -o ./build/compiler_process.o -c

./build/lex_process.o: lex_process.c
	gcc lex_process.c ${INCLUDES} -g -o ./build/lex_process.o -c

./build/lexer.o: lexer.c
	gcc lexer.c ${INCLUDES} -g -o ./build/lexer.o -c

./build/utils/list.o: ./utils/list.c
	gcc ./utils/list.c ${INCLUDES} -g -o ./build/utils/list.o -c

clean:
	rm ./flausinocc
	rm -rf ${OBJECTS}

