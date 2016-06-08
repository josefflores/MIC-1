CC = gcc
CFLAGS = -std=c99 -D_POSIX_SOURCE
TARGET = masm
TARGET_DEPS =  mic1symasm.o lex.yy.o

all: $(TARGET_DEPS)
	$(CC) -o $(TARGET) $^ $(CFLAGS)
	
%.o: %.c
	$(CC) $(CFLAGS) -c -g $^

lex.yy.c: mic1symasm.ll
	flex $^

#test: $(TARGET)
#	./$(TARGET) < ../examples/adder.asm
#	./$(TARGET) -s < ../examples/adder.asm
#	./$(TARGET) -o < ../examples/adder.asm

clean:
	rm -rf $(TARGET) 
	rm -rf lex.yy.c
	rm -rf *.o 	
