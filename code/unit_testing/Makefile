UNAME=$(shell uname)

CCFLAGS=-Wall -O3 -std=gnu99
CC=gcc

all: unitt

unitt: main.o button.o lcd.o led.o params.o physics.o slider.o ctest.h unittests.o
	$(CC) $(LDFLAGS) main.o button.o lcd.o led.o params.o physics.o slider.o unittests.o -o unit_testing

remake: clean all

%.o: %.c ctest.h
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -f unit_testing *.o
