CC = gcc
TARGET = zad2

all:
	make run

run:
	$(CC) -Wall -I /home/sobiesia/gsl/include -c $(TARGET).c
	$(CC) -L/home/sobiesia/gsl/lib $(TARGET).o -lgsl -lgslcblas -lm -o $(TARGET)
	./$(TARGET) > results.txt

clean:
	rm -f $(TARGET) $(TARGET).o