# Variables
CXX = g++
CXXFLAGS = -std=c++17 -I$(SRCDIR)/numeric -I$(SRCDIR)/text
OBJDIR = obj
SRCDIR = src
TARGET = main


# Archivos fuente
SRCS = $(SRCDIR)/main.cpp \
       $(SRCDIR)/numeric/numeric.cpp \
       $(SRCDIR)/text/text.cpp

# Archivos objeto
OBJS = $(OBJDIR)/main.o \
       $(OBJDIR)/numeric.o \
       $(OBJDIR)/text.o

# Regla por defecto
all: clean $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Regla para compilar archivos fuente en objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar archivos fuente en objetos dentro de subdirectorios
$(OBJDIR)/numeric.o: $(SRCDIR)/numeric/numeric.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/numeric/numeric.cpp -o $@

$(OBJDIR)/text.o: $(SRCDIR)/text/text.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/text/text.cpp -o $@

# Regla para limpiar archivos de construcción
clean:
	@echo "[CLN] Removing binary files"
	@rm -f $(TARGET) *.o
# Regla para crear directorios necesarios
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Dependencias
$(TARGET): $(OBJDIR) 
