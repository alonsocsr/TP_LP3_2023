#  -----------------------------------------
# |     SINGLE FILE COMPILATION SUPPORT     |
#  -----------------------------------------

CC := gcc
CFLAGS := -Wall -Wextra -lpthread

SRC_DIR := src
BUILD_DIR := build
SRCS := $(shell find $(SRC_DIR) -name "*.c")

# Get the chapter and listing number from the command-line argument
CHAPTER := $(firstword $(subst ., ,$(filter-out $@,$(MAKECMDGOALS))))
LISTING := $(lastword $(subst ., ,$(filter-out $@,$(MAKECMDGOALS))))

# Define the source and target paths
SRC_PATH := $(SRC_DIR)/Cap$(CHAPTER)/listing$(CHAPTER).$(LISTING).c
BUILD_PATH := $(BUILD_DIR)/Cap$(CHAPTER)/listing$(CHAPTER).$(LISTING).c

# Create the build directory structure and compile the specified listing
listing%:
	@mkdir -p $(BUILD_DIR)/Cap$(basename $*)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/Cap$(basename $*)/listing$* $(SRC_DIR)/Cap$(basename $*)/listing$*.c

# Add a new target to compile all listing files
all_files: $(SRCS)
	@for file in $(SRCS); do \
		dirname="$$(dirname $$file | sed 's|src/||g')"; \
		mkdir -p $(BUILD_DIR)/$$dirname; \
		filename=$$(basename --suffix=.c $$file); \
		$(CC) $(CFLAGS) -o $(BUILD_DIR)/$$dirname/$$filename $$file; \
	done

clean:
	rm -r build/
