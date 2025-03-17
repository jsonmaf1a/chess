CXX = clang++
SRC = $(wildcard src/*.cpp)
CXXFLAGS = -std=c++23
LDFLAGS = -lpthread -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-network
OBJ = $(SRC:src/%.cpp=lib/%.o)

PIECES_SRC = $(wildcard src/pieces/*.cpp)
SHARED_SRC = $(wildcard src/shared/*.cpp)
UTILS_SRC = $(wildcard src/shared/utils/*.cpp)
CONFIG_SRC = $(wildcard src/shared/config/*.cpp)

PIECES_OBJ = $(PIECES_SRC:src/pieces/%.cpp=lib/pieces/%.o)
SHARED_OBJ = $(SHARED_SRC:src/shared/%.cpp=lib/shared/%.o)
UTILS_OBJ = $(UTILS_SRC:src/shared/utils/%.cpp=lib/shared/utils/%.o)
CONFIG_OBJ = $(CONFIG_SRC:src/shared/config/%.cpp=lib/shared/config/%.o)

ALL_OBJ = $(OBJ) $(UTILS_OBJ) $(SHARED_OBJ) $(PIECES_OBJ) $(CONFIG_OBJ)

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
	mkdir -p lib lib/pieces lib/shared bin

clean:
	$(RM) -vr lib bin $(BIN)

run: $(BIN)
	./$(BIN)

-include $(DEPS)
