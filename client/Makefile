CXX = g++
CXXFLAGS = -O2 -std=c++17

# Librerías necesarias
LIBS = -lcurl -lssl -lcrypto

TARGET = ../bin/client
SRC = cliente.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)
