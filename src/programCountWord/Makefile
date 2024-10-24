# Variables
CXX = g++
CXXFLAGS = -std=c++17 -I$(SRCDIR)/countWord -I$(SRCDIR)/countWordT -I$(SRCDIR)/readFile
OBJDIR = obj
SRCDIR = src
TARGET = main
LDFLAGS = -lpthread   # Añadir el flag para vincular pthread

# Archivos fuente
SRCS =	$(SRCDIR)/main.cpp \
		$(SRCDIR)/countWord/countWord.cpp \
		$(SRCDIR)/countWordT/countWordT.cpp \
		$(SRCDIR)/readFile/readFile.cpp \

# Archivos objeto
OBJS =	$(OBJDIR)/main.o \
		$(OBJDIR)/countWord.o \
		$(OBJDIR)/countWordT.o \
		$(OBJDIR)/readFile.o \

# Regla por defecto
all: $(OBJDIR) $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)   # Vincular pthread aquí

# Regla para compilar archivos fuente en objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar archivos fuente en objetos dentro de subdirectorios
$(OBJDIR)/countWord.o: $(SRCDIR)/countWord/countWord.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/countWord/countWord.cpp -o $@

$(OBJDIR)/countWordT.o: $(SRCDIR)/countWordT/countWordT.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/countWordT/countWordT.cpp -o $@

$(OBJDIR)/readFile.o: $(SRCDIR)/readFile/readFile.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/readFile/readFile.cpp -o $@

# Limpieza de archivos binarios y objeto
clean:
	@echo "[CLN] Removing binary and object files"
	@rm -f $(TARGET) $(OBJDIR)/*.o

# Regla para crear directorio de objetos
$(OBJDIR):
	mkdir -p $(OBJDIR)
