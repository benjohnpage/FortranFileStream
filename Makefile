PROGS = Demo

all: $(PROGS)

FortranFileStream.o: FortranFileStream.cc
	gcc -c -o FortranFileStream.o FortranFileStream.cc

FortranFileIO.o: FortranFileIO.F
	gcc -c -o FortranFileIO.o FortranFileIO.F

Demo: Main.o FortranFileStream.o FortranFileIO.o
	gcc -o Demo Main.o FortranFileStream.o FortranFileIO.o \
        -lstdc++ -lgfortran

clean:
	rm $(PROGS) *.o
