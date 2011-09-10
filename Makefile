PROGS = Demo

all: $(PROGS)

Main.o: Main.cc
	gcc -Wall -c -o Main.o Main.cc

FortranFileStream.o: FortranFileStream.cc
	gcc -Wall -c -o FortranFileStream.o FortranFileStream.cc

FortranFileIO.o: FortranFileIO.F
	gcc -Wall -c -o FortranFileIO.o FortranFileIO.F

Demo: Main.o FortranFileStream.o FortranFileIO.o
	gcc -Wall -o Demo Main.o FortranFileStream.o FortranFileIO.o \
        -lstdc++ -lgfortran

clean:
	rm $(PROGS) *.o
