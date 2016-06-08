


CC = gcc
CFLAGS = -Wall -g
DEPS = globals.h

MCC_DEPS = mcc.o scanner.o errors.o dbuffer.o symtab.o parser.o emit.o 
MCV_DEPS = mcv.o
DRV_DEPS = scanner.o errors.o dbuffer.o symtab.o symdrv.o

.c.o:
	$(CC) -c $< $(CFLAGS) 

all: mcc mcv

mcv: $(MCV_DEPS)
	$(CC) -o $@ $^ $(CFLAGS) 

mcc: $(MCC_DEPS)
	$(CC) -o $@ $^ $(CFLAGS) 

symdrv: $(DRV_DEPS)
	$(CC) -o $@ $^ $(CFLAGS) 

scandrv: $(DRV_DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

clean   : 
	rm -rf *.o core mcc mcv
