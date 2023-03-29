CC = gcc
TARGET = zad3

all:
	make run

run:
	$(CC) $(TARGET).c -o $(TARGET) -lgsl -lgslcblas -lm
	./$(TARGET) > result.txt

clean:
	rm -f $(TARGET)