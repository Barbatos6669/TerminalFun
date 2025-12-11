# Makefile for Raspberry Pi Monitor

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
TARGET = monitor
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)

install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

.PHONY: all clean run install uninstall
