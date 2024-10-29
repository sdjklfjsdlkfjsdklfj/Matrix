CXX = clang++
CFLAGS = -O2 -Wall -std=c++14 -I.
SRCS = main.cpp matrix.cpp
TEST_SRCS = tests/test.cpp matrix.cpp
TARGET_DIR = bin
TARGET = $(TARGET_DIR)/release
TEST_TARGET = $(TARGET_DIR)/test

.PHONY: all bin clean run test valgrind help

all: $(TARGET)

$(TARGET): $(SRCS) | $(TARGET_DIR) 
	$(CXX) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_SRCS) | $(TARGET_DIR) 
	$(CXX) $(CFLAGS) -o $@ $^

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

valgrind: $(TEST_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_TARGET)
	
clean:
	$(RM) -r $(TARGET_DIR)

help:
	@echo "Available commands:"
	@echo "  all         - Build the main project"
	@echo "  run         - Run the built project"
	@echo "  test        - Run the tests"
	@echo "  valgrind    - Run tests with Valgrind"
	@echo "  clean       - Remove compiled files"
	@echo "  help        - Show this message"

