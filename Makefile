PROJECT_NAME = http

SRC_P = ./src/
BUILD_P = ./build/

SRC_FILES = $(wildcard $(SRC_P)*.cpp)
OBJ_FILES = $(patsubst $(SRC_P)%.cpp, $(BUILD_P)%.o, $(SRC_FILES))

run: clear libs
	g++ main.cpp -o $(PROJECT_NAME).elf -L./ -lhttp
	./$(PROJECT_NAME).elf

libs: $(OBJ_FILES)
	ar crs lib$(PROJECT_NAME).a $(OBJ_FILES)

$(BUILD_P)%.o: $(SRC_P)%.cpp
	g++ -c $? -o $@

clear:
	rm -f lib$(PROJECT_NAME).a
	rm -f $(BUILD_P)*.o
	rm -f $(PROJECT_NAME).elf
