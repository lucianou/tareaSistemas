# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Isrc/cache
OBJDIR = obj
SRCDIR = src
TARGET = main

# Archivos fuente y objeto
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/cache/cache.cpp
OBJS = $(OBJDIR)/main.o $(OBJDIR)/cache.o

# Regla por defecto
all: $(OBJDIR) $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Regla para compilar archivos fuente en objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar el core
$(OBJDIR)/cache.o: $(SRCDIR)/cache/cache.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/cache/cache.cpp -o $@

# Limpieza de archivos binarios y objeto
clean:
	@echo "[CLN] Removing binary and object files"
	@rm -f $(TARGET) $(OBJDIR)/*.o

# Crear el directorio de objetos si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)
