CC = gcc
DEPS = globals.h variables.h util.h alu.h clock.h control.h shifter.h cpu.h memory.h
TARGET = mic1
TARGET_DEPS = util.o driver.o alu.o control.o clock.o cpu.o datapath.o memory.o shifter.o

all: $(TARGET_DEPS)
	$(CC) -o $(TARGET) $^

%.o: %.c %.h $(DEPS)
	$(CC) -c -o $@ $<

clean:
	rm -rf $(TARGET)
	rm -rf *.o
