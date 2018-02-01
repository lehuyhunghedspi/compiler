CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: scanner

scanner: scanner.o reader.o charcode.o token.o error.o
	${CC} scanner.o reader.o charcode.o token.o error.o -o scanner

reader.o: reader.c
	${CC} ${CFLAGS} reader.c

scanner.o: scanner.c
	${CC} ${CFLAGS} scanner.c

charcode.o: charcode.c
	${CC} ${CFLAGS} charcode.c

token.o: token.c
	${CC} ${CFLAGS} token.c

error.o: error.c
	${CC} ${CFLAGS} error.c
test:
	./scanner ../test/example1.kpl ./runresult/runresult1.txt
	./scanner ../test/example2.kpl ./runresult/runresult2.txt
	./scanner ../test/example3.kpl ./runresult/runresult3.txt
	./scanner ../test/example4.kpl ./runresult/runresult4.txt
	./scanner ../test/example5.kpl ./runresult/runresult5.txt
	./scanner ../test/example6.kpl ./runresult/runresult6.txt
	./scanner ../test/example7.kpl ./runresult/runresult7.txt
	./scanner ../test/example8.kpl ./runresult/runresult8.txt
clean:
	rm -f *.o *~

