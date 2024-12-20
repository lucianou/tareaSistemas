# Variables
CXX = g++
CXXFLAGS = -std=c++17 -I$(SRCDIR)/numeric -I$(SRCDIR)/text -I$(SRCDIR)/auth
OBJDIR = obj
BINDIR = .
SRCDIR = src
TARGETS = $(BINDIR)/main

# Archivos fuente
SRCS = $(SRCDIR)/main.cpp \
       $(SRCDIR)/numeric/numeric.cpp \
       $(SRCDIR)/text/text.cpp \
       $(SRCDIR)/auth/auth.cpp

# Archivos objeto (asegurándonos de que se coloquen correctamente en subdirectorios)
OBJS_MAIN = $(OBJDIR)/main.o \
            $(OBJDIR)/numeric/numeric.o \
            $(OBJDIR)/text/text.o \
            $(OBJDIR)/auth/auth.o

# Regla por defecto
all: $(BINDIR) $(OBJDIR) $(TARGETS)

# Regla para crear el ejecutable 'main' en $(BINDIR)
$(BINDIR)/main: $(OBJS_MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_MAIN)

# Reglas para compilar archivos fuente en objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@) # Crear el subdirectorio en obj si no existe
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	@echo "[CLN] Removing binary and object files"
	@rm -f $(BINDIR)/main  	# Elimina solo el binario
	@rm -f $(OBJDIR)/*.o       # Elimina solo los archivos .o, no el contenido completo del directorio

# Reglas para crear directorios si no existen
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)
