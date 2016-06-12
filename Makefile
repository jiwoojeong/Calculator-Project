test : bignumbercal.o subcal.o bignumsub.o
	gcc -o test bignumbercal.o subcal.o bignumsub.o

bignumbercal.o : subcal.h bignumbercal.c
	gcc -c bignumbercal.c
subcal.o : subcal.h subcal.c
	gcc -c subcal.c
bignumsub.o : bignumsub.h bignumsub.c
	gcc -c bignumsub.c
