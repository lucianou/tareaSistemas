# Variables
CXX = g++
CXXFLAGS = -std=c++17 -I$(SRCDIR)/menu -I$(SRCDIR)/readFile 
OBJDIR = obj
SRCDIR = src
TARGET = main

# Archivos fuente
SRCS = $(SRCDIR)/main.cpp \
       $(SRCDIR)/menu/menu.cpp \
       $(SRCDIR)/readFile/readFile.cpp \

# Archivos objeto
OBJS = $(OBJDIR)/main.o \
       $(OBJDIR)/menu.o \
       $(OBJDIR)/readFile.o \

# Regla por defecto
all: $(OBJDIR) $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Regla para compilar archivos fuente en objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar archivos fuente en objetos dentro de subdirectorios
$(OBJDIR)/menu.o: $(SRCDIR)/menu/menu.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/menu/menu.cpp -o $@

$(OBJDIR)/readFile.o: $(SRCDIR)/readFile/readFile.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/readFile/readFile.cpp -o $@

clean:
	@echo "[CLN] Removing binary and object files"
	@rm -f $(TARGET) $(OBJDIR)/*.o

# Regla para crear directorio de objetos
$(OBJDIR):
	mkdir -p $(OBJDIR)
