all: hoofd.o koffiebord.o
	g++ -Wall -Wextra -o jemoeder koffiebord.o hoofd.o
koffiebord.o: koffiebord.cc koffiebord.h
	g++ -Wall -Wextra -c koffiebord.cc
hoofd.o: hoofd.cc koffiebord.h
	g++ -Wall -Wextra -c hoofd.cc
#	cd "u:\Semester1\ProgrammeerMethoden\Opdracht4\" && g++ hoofd.cc -Wall -Wextra -o hoofd && u:\Semester1\ProgrammeerMethoden\Opdracht4\hoofd
# 	cd $dir && g++ $fileName -Wall -Wextra -o $fileNameWithoutExt && $dir$fileNameWithoutExt