# Nombre del ejecutable
TARGET = main

# Carpetas
INCLUDE_DIR = include
SRC_DIR = src

# Compilador y banderas
CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -std=c++17

# Archivos fuente
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/frequency.cpp \
          $(SRC_DIR)/HuffmanTree.cpp \
          $(SRC_DIR)/HuffmanUtils.cpp \
          $(SRC_DIR)/HuffmanCodes.cpp \
          $(SRC_DIR)/HuffmanEncoder.cpp \
          $(SRC_DIR)/HuffmanDecoder.cpp \
          $(SRC_DIR)/CompressedIO.cpp

# Archivos objeto (reemplaza .cpp por .o)
OBJECTS = $(SOURCES:.cpp=.o)

# Regla por defecto
all: $(TARGET)

# Cómo compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Cómo compilar cada archivo .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: all clean
