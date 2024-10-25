# Variables
CXX = g++
CXXFLAGS = -std=c++17 -I$(SRCDIR)/planificador
OBJDIR = obj
SRCDIR = src
TARGET = main
LDFLAGS = -lpthread   # Añadir el flag para vincular pthread

# Archivos fuente y objetos
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/planificador/planificador.cpp
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Regla por defecto
all: $(OBJDIR)/planificador $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)   # Vincular pthread aquí

# Regla para compilar cualquier archivo fuente en su objeto correspondiente
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)/planificador
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorios necesarios en obj
$(OBJDIR)/planificador:
	mkdir -p $(OBJDIR)/planificador

# Limpieza de archivos binarios y objeto
clean:
	@echo "[CLN] Removing binary and object files"
	@rm -f $(TARGET) $(OBJDIR)/*.o $(OBJDIR)/planificador/*.o

# Regla para crear directorio de objetos
$(OBJDIR):
	mkdir -p $(OBJDIR)
