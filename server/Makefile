CXX = g++
CXXFLAGS = -static -O2 -std=c++17 -Iinclude
LIBS = -lssl -lcrypto -lpthread

TARGET = ../bin/servidor
SRC = servidor.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)
