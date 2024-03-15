# Name of the project
PROJ_NAME=game

BIN_FOLDER=bin

# .cpp files
C_SOURCE=$(wildcard ./src/*.cpp)

# .h files
H_SOURCE=$(wildcard ./src/*.h)

# Object files
OBJ=$(subst .cpp,.o,$(subst src,obj,$(C_SOURCE)))

# Compiler and linker
CC=g++

# Flags for compiler
CC_FLAGS=-c         \
         -std=c++17 \
         -pedantic  \
         -O3        \
# Flags for linker
CL_FLAGS=-std=c++17 \
         -O3        \
         -o         \

# Libraries
LIB=-lsfml-graphics -lsfml-window -lsfml-system

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#
all: objFolder binFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using G++ linker: $@'
	$(CC) $^ $(CL_FLAGS) ./$(BIN_FOLDER)/$@ $(LIB)
	@ echo 'Finished building binary: $@'
	@ echo ' '

./obj/%.o: ./src/%.cpp ./src/%.h
	@ echo 'Building target using G++ compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./obj/main.o: ./src/main.cpp $(H_SOURCE)
	@ echo 'Building target using G++ compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p obj

binFolder:
	@ mkdir -p $(BIN_FOLDER)

clean:
	@ $(RM) ./obj/*.o ./$(BIN_FOLDER)/$(PROJ_NAME) *~
	@ rmdir obj
	@ rmdir $(BIN_FOLDER)

.PHONY: all clean
