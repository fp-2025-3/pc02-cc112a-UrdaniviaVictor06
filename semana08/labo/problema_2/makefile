# ===============================
# COMPILADOR
# ===============================

CXX := g++                     # Compilador que vamos a usar (C++)

# ===============================
# FLAGS BASE
# ===============================

BASE_FLAGS := -std=c++17 -Wall -Wextra -Wpedantic
# -std=c++17        → estándar de C++
# -Wall -Wextra     → activa advertencias importantes
# -Wpedantic        → fuerza código más estricto y estándar

# ===============================
# SISTEMA OPERATIVO
# ===============================

ifeq ($(OS),Windows_NT)        # Si estamos en Windows
    EXEEXT := .exe             # Extensión de ejecutables
    RM := del /Q               # Comando para borrar archivos
    MKDIR := mkdir             # Comando para crear carpetas
    VALGRIND := @echo "Valgrind no disponible en Windows"
else                           # Si estamos en Linux / WSL
    EXEEXT :=                  # En Linux no hay extensión
    RM := rm -f                # Comando para borrar
    MKDIR := mkdir -p          # Crear carpeta si no existe
    VALGRIND := valgrind --leak-check=full --show-leak-kinds=all
endif

# ===============================
# ARCHIVOS FUENTE Y OBJETO
# ===============================

SRCS := $(wildcard *.cpp)
# Detecta automáticamente todos los archivos .cpp

OBJS := $(SRCS:.cpp=.o)
# Convierte cada .cpp en .o
# Ej: main.cpp → main.o

# ===============================
# DIRECTORIOS DE BUILD
# ===============================

BUILD_DIR := build             # Carpeta principal de compilación
NORMAL_DIR := $(BUILD_DIR)/normal
DEBUG_DIR  := $(BUILD_DIR)/debug
ASAN_DIR   := $(BUILD_DIR)/asan

TARGET := app                  # Nombre del ejecutable final

# ===============================
# TARGETS PÚBLICOS
# ===============================

.PHONY: all normal debug asan clean valgrind
# .PHONY indica que estos no son archivos reales

all: normal
# Cuando el usuario escribe "make"
# se ejecuta el target normal

# ===============================
# COMPILACIÓN NORMAL
# ===============================

normal: $(NORMAL_DIR)/$(TARGET)$(EXEEXT)
# Para cumplir "normal", debe existir el ejecutable final

$(NORMAL_DIR)/$(TARGET)$(EXEEXT): $(OBJS)
	$(MKDIR) $(NORMAL_DIR)
	$(CXX) $(BASE_FLAGS) $^ -o $@
# $^ = todos los .o
# $@ = nombre del archivo objetivo (app)
# Aquí se realiza el ENLACE (linking)

# ===============================
# COMPILACIÓN DEBUG
# ===============================

debug: $(DEBUG_DIR)/$(TARGET)$(EXEEXT)

$(DEBUG_DIR)/$(TARGET)$(EXEEXT): $(OBJS)
	$(MKDIR) $(DEBUG_DIR)
	$(CXX) $(BASE_FLAGS) -g -O0 $^ -o $@
# -g    → incluye información de depuración
# -O0   → desactiva optimización (mejor para debug)

# ===============================
# COMPILACIÓN CON ASAN
# ===============================

asan: $(ASAN_DIR)/$(TARGET)$(EXEEXT)

$(ASAN_DIR)/$(TARGET)$(EXEEXT): $(OBJS)
	$(MKDIR) $(ASAN_DIR)
	$(CXX) $(BASE_FLAGS) -fsanitize=address -fno-omit-frame-pointer -g -O1 $^ -o $@
# -fsanitize=address → activa AddressSanitizer
# -fno-omit-frame-pointer → mejora trazas de errores
# -g → mantiene info de debug

# ===============================
# REGLA PARA GENERAR .o
# ===============================

%.o: %.cpp
	$(CXX) $(BASE_FLAGS) -c $< -o $@
# -c → compila pero NO enlaza
# $< → archivo fuente actual
# $@ → archivo objeto generado

# ===============================
# VALGRIND
# ===============================

valgrind: debug
	$(VALGRIND) ./$(DEBUG_DIR)/$(TARGET)$(EXEEXT)
# Primero compila en debug
# Luego ejecuta con Valgrind





# Targets for run
# Ejecutar normal
run: normal
	./$(NORMAL_DIR)/$(TARGET)$(EXEEXT)

# Ejecutar debug
rundebug: debug
	./$(DEBUG_DIR)/$(TARGET)$(EXEEXT)

# Ejecutar asan
runasan: asan
	./$(ASAN_DIR)/$(TARGET)$(EXEEXT)


# ===============================
# LIMPIEZA
# ===============================

clean:
	$(RM) *.o
	$(RM) -r build
# Borra objetos y carpeta build


# g++ -c Persona.cpp
# g++ -c main.cpp

# g++ Persona.o main.o -o app

# make debug
# ./build/debug/app

# make valgrind