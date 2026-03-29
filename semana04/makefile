# Makefile 
CXX := g++

# Flags base
BASE_FLAGS := -std=c++17 -Wall -Wextra -Wpedantic
#CXXFLAGS := $(BASE_FLAGS)

# Sistema operativo (Windows / Linux / WSL)
ifeq ($(OS),Windows_NT)
    EXEEXT := .exe
    RM := del /Q
    MKDIR := mkdir
	VALGRIND := @echo "Valgrind no disponible en Windows"
else
    EXEEXT :=
    RM := rm -f
    MKDIR := mkdir -p
    VALGRIND := valgrind --leak-check=full --show-leak-kinds=all
endif


# Archivos fuente del directorio actual (local)
SRCS := $(wildcard *.cpp)
BASENAMES := $(basename $(SRCS))

# Build local (en la carpeta actual)
BUILD_DIR := build
NORMAL_DIR := $(BUILD_DIR)/normal
DEBUG_DIR  := $(BUILD_DIR)/debug
ASAN_DIR   := $(BUILD_DIR)/asan

# Ejecutables (uno por cada .cpp)
TARGETS := $(BASENAMES:%.cpp=%$(EXEEXT))


# Targets publicos
all: normal link-normal

normal: $(BASENAMES:%=$(NORMAL_DIR)/%$(EXEEXT))

debug:  $(BASENAMES:%=$(DEBUG_DIR)/%$(EXEEXT)) link-debug

asan:   $(BASENAMES:%=$(ASAN_DIR)/%$(EXEEXT)) link-asan

valgrind: debug
	$(VALGRIND) ./$(firstword $(TARGETS))



# Reglas de compilacion
$(NORMAL_DIR)/%$(EXEEXT): %.cpp
	$(MKDIR) $(NORMAL_DIR)
	$(CXX) $(BASE_FLAGS) $< -o $@

$(DEBUG_DIR)/%$(EXEEXT): %.cpp
	$(MKDIR) $(DEBUG_DIR)
	$(CXX) $(BASE_FLAGS) -g -O0 $< -o $@

$(ASAN_DIR)/%$(EXEEXT): %.cpp
	$(MKDIR) $(ASAN_DIR)
	$(CXX) $(BASE_FLAGS) -fsanitize=address -fno-omit-frame-pointer -g -O1 $< -o $@

# Enlace local (flujo clasico)
link-normal:
	$(RM) $(TARGETS)
	ln -s $(NORMAL_DIR)/$(firstword $(TARGETS)) $(firstword $(TARGETS))

link-debug:
	$(RM) $(TARGETS)
	ln -s $(DEBUG_DIR)/$(firstword $(TARGETS)) $(firstword $(TARGETS))

link-asan:
	$(RM) $(TARGETS)
	ln -s $(ASAN_DIR)/$(firstword $(TARGETS)) $(firstword $(TARGETS))

# Limpieza
clean:
	$(RM) $(TARGETS)
	$(RM) -r build
