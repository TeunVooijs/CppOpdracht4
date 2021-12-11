all: hoofd.o koffiebord.o
	g++ -Wall -Wextra -o jemoeder koffiebord.o hoofd.o
koffiebord.o: koffiebord.cc koffiebord.h
	g++ -Wall -Wextra -c koffiebord.cc
hoofd.o: hoofd.cc koffiebord.h
	g++ -Wall -Wextra -c hoofd.cc
