# --- Variables ---
CC = gcc                  # Compilador
CFLAGS = -Wall -g         # Opciones de compilación
AR = ar                   # Herramienta para biblioteca
ARFLAGS = rcs             # Flags para crear lib estática

# --- Archivos ---
TARGET = main             # Ejecutable final
LIB = libprimo.a          # Biblioteca estática
OBJS = primo.o            # Objetos de la biblioteca

# --- Reglas ---

# Regla por defecto: compilar todo
all: $(TARGET)

# Compilar el ejecutable principal
$(TARGET): main.c $(LIB)
	$(CC) $(CFLAGS) main.c -L. -lprimo -o $(TARGET)

# Crear la biblioteca estática
$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

# Compilar el objeto primo.o
primo.o: primo.c primo.h
	$(CC) $(CFLAGS) -c primo.c

# Limpiar archivos compilados
clean:
	rm -f $(TARGET) $(OBJS) $(LIB)

# Forzar recompilación total
rebuild: clean all
