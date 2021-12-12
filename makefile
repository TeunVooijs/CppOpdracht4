all: hoofd.o koffiebord.o # stapel.o
	g++ -Wall -Wextra -o jemoeder koffiebord.o hoofd.o
koffiebord.o: koffiebord.cc koffiebord.h # stapel.h
	g++ -Wall -Wextra -c koffiebord.cc
hoofd.o: hoofd.cc koffiebord.h # stapel.h
	g++ -Wall -Wextra -c hoofd.cc
# stapel.o: stapel.cc koffiebord.h stapel.h
# 	g++ -Wall -Wextra -c stapel.cc