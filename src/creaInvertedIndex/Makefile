# Variables
CXX = g++
CXXFLAGS = -std=c++17 
OBJDIR = obj
SRCDIR = src
TARGET = main
LDFLAGS = -lpthread   # Añadir el flag para vincular pthread

# Archivos fuente
SRCS =	$(SRCDIR)/main.cpp \

# Archivos objeto
OBJS =	$(OBJDIR)/main.o \


# Regla por defecto
all: $(OBJDIR) $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)   # Vincular pthread aquí

# Regla para compilar archivos fuente en objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar archivos fuente en objetos dentro de subdirectorios

# Limpieza de archivos binarios y objeto
clean:
	@echo "[CLN] Removing binary and object files"
	@rm -f $(TARGET) $(OBJDIR)/*.o

# Regla para crear directorio de objetos
$(OBJDIR):
	mkdir -p $(OBJDIR)
