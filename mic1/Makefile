CC = gcc
DEPS = globals.h
TARGET = mic1
TARGET_DEPS = driver.o alu.o control.o clock.o cpu.o datapath.o memory.o shifter.o 

all: $(TARGET_DEPS)
	$(CC) -o $(TARGET) $^

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<
	
clean:
	rm -rf $(TARGET)
	rm -rf *.o
