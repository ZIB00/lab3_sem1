TARGET = queue
PREFIX = /usr/local/bin

.PHONY: all clean install uninstall

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

main.o: main.c queue.h
	gcc -c main.c -o main.o

queue.o: queue.c queue.h
	gcc -c queue.c -o queue.o

$(TARGET): main.o queue.o
	gcc main.o queue.o -o $(TARGET)

install:
	install $(TARGET) $(PREFIX)

uninstall:
	rm -f $(PREFIX)/$(TARGET)
