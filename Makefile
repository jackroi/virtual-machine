# Copyright © 2019 Giacomo Rosin

# The binary file generated by this Makefile is named vm.out
# All the file (.o / .d) generated by the compilation process are put into the build dir


CC = gcc
# CC = clang

# CFLAGS = -std=gnu89 -g3 -pedantic-errors -Wall -Wextra
CFLAGS = -std=gnu89 -g3 -pedantic-errors -Wall -Wextra -fsanitize=address -fsanitize=undefined

# Include path
INCLUDES = -I "./include"

# Final binary
BIN = vm.out

# Put all auto generated stuff to this build dir
BUILD_DIR = ./build

# Source code path
SOURCE_DIR = ./src

# List of all .c source files
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)

# All the .o files go to build dir
OBJECTS = $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o, $(SOURCES))

# Gcc/Clang will create this .d files containing dependencies
DEP = $(OBJECTS:%.o=%.d)


# Final binary - depends on all .o files
$(BIN) : $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@


# Include all .d files
-include $(DEP)


# Build all the object files from .c files
# The potential dependency on header files is covered
# by calling '-include $(DEP)'
# The -MMD flags additionaly creates a .d files
$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@


.PHONY : clean check

clean :
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN)

# Automated tests (probably not the best way do them)
check : $(BIN)
	$(CC) $(CFLAGS) test/automated-test/auto-test.c -o test.out
	./test.out
	rm -rf test.out
