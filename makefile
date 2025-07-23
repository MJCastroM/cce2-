# Variables
CFLAGS = -O3 -std=c++17
TARGET = rsdecode
SOURCES = rsdecode.cpp decoder.cpp gf256.c

# Regla por defecto
all: $(TARGET)

# Regla de compilación
$(TARGET): $(SOURCES)
	g++ $(CFLAGS) -o $(TARGET) $(SOURCES)

# Limpieza de archivos generados
clean:
	rm -f $(TARGET) *.o