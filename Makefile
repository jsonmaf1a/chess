CXX = g++
SRC = $(wildcard src/*.cpp)
CXXFLAGS = -std=c++23 -MMD -MP -Iinclude
LDFLAGS = -lpthread -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-network
OBJ = $(SRC:src/%.cpp=lib/%.o)

MAKEFLAGS += --no-print-directory

PIECES_SRC = $(wildcard src/pieces/*.cpp)
SHARED_SRC = $(wildcard src/shared/*.cpp)
SHARED_UI_SRC = $(wildcard src/shared/ui/*.cpp)
MANAGERS_SRC = $(wildcard src/managers/*.cpp)
UTILS_SRC = $(wildcard src/shared/utils/*.cpp)
CONFIG_SRC = $(wildcard src/shared/config/*.cpp)

PIECES_OBJ = $(PIECES_SRC:src/pieces/%.cpp=lib/pieces/%.o)
SHARED_OBJ = $(SHARED_SRC:src/shared/%.cpp=lib/shared/%.o)
SHARED_UI_OBJ = $(SHARED_UI_SRC:src/shared/ui/%.cpp=lib/shared/ui/%.o)
MANAGERS_OBJ = $(MANAGERS_SRC:src/managers/%.cpp=lib/managers/%.o)
UTILS_OBJ = $(UTILS_SRC:src/shared/utils/%.cpp=lib/shared/utils/%.o)
CONFIG_OBJ = $(CONFIG_SRC:src/shared/config/%.cpp=lib/shared/config/%.o)

ALL_OBJ = $(CONFIG_OBJ) $(SHARED_OBJ) $(SHARED_UI_OBJ) $(UTILS_OBJ) $(MANAGERS_OBJ) $(PIECES_OBJ) $(OBJ)

BIN = bin/app
DEPS = $(ALL_OBJ:.o=.d)

.PHONY: all clean run

all: $(BIN)

$(BIN): $(ALL_OBJ) | build
	$(CXX) $(ALL_OBJ) -o $(BIN) $(LDFLAGS)

lib/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

lib/pieces/%.o: src/pieces/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p lib lib/pieces lib/shared lib/shared/ui lib/shared/config lib/managers bin

clean:
	$(RM) -vr lib bin $(BIN)

run: $(BIN)
	./$(BIN)

-include $(DEPS)
