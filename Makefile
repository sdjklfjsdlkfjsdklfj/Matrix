CXX = clang++
TARGET = bin
SRCS = main.cpp matrix.cpp

$(TARGET): $(SRCS) 
	$(CXX) -o $@ $^

 clean:
	rm -f $(TARGET)

