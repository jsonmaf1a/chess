CXX = g++
SRC = $(wildcard src/*.cpp)
CXXFLAGS = -std=c++23
LDFLAGS = -lpthread -lsfml-window -lsfml-graphics -lsfml-system
OBJ = $(SRC:src/%.cpp=lib/%.o)
BIN = bin/app
DEPFLAGS = -MMD -MP
DEPS = $(OBJ:.o=.d)

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJ) | build
	$(CXX) $(OBJ) -o $(BIN) $(LDFLAGS)

lib/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

build:
	mkdir -p lib bin

clean:
	$(RM) -vr lib bin $(BIN) $(OBJ)

run: $(BIN)
	./$(BIN)

-include $(DEPS)
