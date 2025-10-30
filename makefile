# Compilador
CXX = g++
# Opciones de compilación
CXXFLAGS = -Wall -Wextra -std=c++17 -finput-charset=UTF-8 -fexec-charset=UTF-8

# Archivos fuente y objetos
SRC = main.cpp archivo.cpp cambios.cpp linea.cpp version.cpp versionnumber.cpp
OBJ = $(SRC:.cpp=.o)

# Ejecutable final
TARGET = programa

# Regla principal
all: $(TARGET)

# Cómo generar el ejecutable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Regla genérica para compilar cada .cpp a .o
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza
clean:
	rm -f $(OBJ) $(TARGET)

# Limpieza total (por si acaso)
fclean: clean

# Reconstruir todo
rebuild: fclean all
