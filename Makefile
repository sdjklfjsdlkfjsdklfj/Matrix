CXX = clang++
CFLAGS = -O2 -Wall -std=c++14 -I.
SRCS = main.cpp matrix.cpp
TARGET = bin/release
TEST_SRCS = tests/test.cpp matrix.cpp
TEST_TARGET = bin/test

all: $(TARGET)

$(TEST_TARGET): $(TEST_SRCS) | bin
	$(CXX) $(CFLAGS) -o $@ $^

$(TARGET): $(SRCS) | bin
	$(CXX) $(CFLAGS) -o $@ $^

bin:
	mkdir bin

clean:
	rm -f $(TARGET) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)
