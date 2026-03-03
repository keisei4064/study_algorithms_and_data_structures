CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
TARGET := test_bgl

.PHONY: all run png clean

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run: $(TARGET)
	./$(TARGET)

png: run
	dot -Tpng graph.dot -o graph.png
	@echo "Wrote graph.png"

clean:
	rm -f $(TARGET) graph.dot graph.png
