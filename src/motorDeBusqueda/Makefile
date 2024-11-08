# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Isrc/motorDeBusqueda
OBJDIR = obj
SRCDIR = src
TARGET = main

# Archivos fuente y objeto
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/motorDeBusqueda/motorDeBusqueda.cpp
OBJS = $(OBJDIR)/main.o $(OBJDIR)/motorDeBusqueda.o

# Regla por defecto
all: $(OBJDIR) $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Regla para compilar archivos fuente en objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar el core
$(OBJDIR)/motorDeBusqueda.o: $(SRCDIR)/motorDeBusqueda/motorDeBusqueda.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/motorDeBusqueda/motorDeBusqueda.cpp -o $@

# Limpieza de archivos binarios y objeto
clean:
	@echo "[CLN] Removing binary and object files"
	@rm -f $(TARGET) $(OBJDIR)/*.o

# Crear el directorio de objetos si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)
