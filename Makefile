PROGS = Demo

all: $(PROGS)

Main.o: Main.cc
	gcc -c -o Main.o Main.cc

FortranFileStream.o: FortranFileStream.cc
	gcc -c -o FortranFileStream.o FortranFileStream.cc

FortranFileIO.o: FortranFileIO.F
	gcc -c -o FortranFileIO.o FortranFileIO.F

Demo: Main.o FortranFileStream.o FortranFileIO.o
	gcc -o Demo Main.o FortranFileStream.o FortranFileIO.o \
        -lstdc++ -lgfortran

clean:
	rm $(PROGS) *.o
