CXX = g++
SRC = $(wildcard src/*.cpp)
PIECES_SRC = $(wildcard src/pieces/*.cpp)
UTILS_SRC = $(wildcard src/utils/*.cpp)
CXXFLAGS = -std=c++23
LDFLAGS = -lpthread -lsfml-window -lsfml-graphics -lsfml-system
OBJ = $(SRC:src/%.cpp=lib/%.o)
PIECES_OBJ = $(PIECES_SRC:src/pieces/%.cpp=lib/pieces/%.o)
UTILS_OBJ = $(UTILS_SRC:src/utils/%.cpp=lib/utils/%.o)
ALL_OBJ = $(OBJ) $(UTILS_OBJ) $(PIECES_OBJ)
BIN = bin/app
DEPFLAGS = -MMD -MP
DEPS = $(ALL_OBJ:.o=.d)

.PHONY: all clean run

all: $(BIN)

$(BIN): $(ALL_OBJ) | build
	$(CXX) $(ALL_OBJ) -o $(BIN) $(LDFLAGS)

lib/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

lib/pieces/%.o: src/pieces/%.cpp | build
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

build:
	mkdir -p lib lib/pieces lib/utils bin

clean:
	$(RM) -vr lib bin $(BIN)

run: $(BIN)
	./$(BIN)

-include $(DEPS)
