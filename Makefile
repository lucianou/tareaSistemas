# Variables
CXX = g++
CXXFLAGS = -std=c++17 -I$(SRCDIR)/numeric -I$(SRCDIR)/text -I$(SRCDIR)/auth -I$(SRCDIR)/countWord
OBJDIR = obj
SRCDIR = src
TARGET = main

# Archivos fuente
SRCS = $(SRCDIR)/main.cpp \
       $(SRCDIR)/numeric/numeric.cpp \
       $(SRCDIR)/text/text.cpp \
       $(SRCDIR)/auth/auth.cpp \
	   $(SRCDIR)/countWord/countWord.cpp


# Archivos objeto
OBJS = $(OBJDIR)/main.o \
       $(OBJDIR)/numeric.o \
       $(OBJDIR)/text.o \
       $(OBJDIR)/auth.o \
	   $(OBJDIR)/countWord.o


# Regla por defecto
all: $(OBJDIR) $(TARGET)

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

$(OBJDIR)/auth.o: $(SRCDIR)/auth/auth.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/auth/auth.cpp -o $@

$(OBJDIR)/countWord.o: $(SRCDIR)/countWord/countWord.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/countWord/countWord.cpp -o $@

clean:
	@echo "[CLN] Removing binary and object files"
	@rm -f $(TARGET) $(OBJDIR)/*.o

# Regla para crear directorio de objetos
$(OBJDIR):
	mkdir -p $(OBJDIR)
