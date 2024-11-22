# Variables
CXX = g++
CXXFLAGS = -std=c++17 -I$(SRCDIR)/distribuidor
OBJDIR = obj
SRCDIR = src
TARGET = main
LDFLAGS = -lpthread   # Añadir el flag para vincular pthread

# Archivos fuente
SRCS =	$(SRCDIR)/main.cpp \
		$(SRCDIR)/distribuidor/distribuidor.cpp \

# Archivos objeto
OBJS =	$(OBJDIR)/main.o \
		$(OBJDIR)/distribuidor.o \

# Regla por defecto
all: $(OBJDIR) $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)   # Vincular pthread aquí

# Regla para compilar archivos fuente en objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar archivos fuente en objetos dentro de subdirectorios
$(OBJDIR)/distribuidor.o: $(SRCDIR)/distribuidor/distribuidor.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/distribuidor/distribuidor.cpp -o $@

# Limpieza de archivos binarios y objeto
clean:
	@echo "[CLN] Removing binary and object files"
	@rm -f $(TARGET) $(OBJDIR)/*.o

# Regla para crear directorio de objetos
$(OBJDIR):
	mkdir -p $(OBJDIR)
