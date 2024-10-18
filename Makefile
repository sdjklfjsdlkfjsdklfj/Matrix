CXX = clang++
CFLAGS = -O2 -Wall -std=c++14
SRCS = main.cpp matrix.cpp
TARGET = bin

$(TARGET): $(SRCS) 
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

