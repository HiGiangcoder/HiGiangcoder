# ===== CONFIG =====
CXX := g++
CXXFLAGS := -O3 -Wall -std=c++17 -Iinclude -fPIC
SRC_DIR := src
BUILD_DIR := build
CLI_TARGET := english_cli
PYBIND_TARGET := englishapp$(shell python3-config --extension-suffix)

# Python include & lib
PYTHON_INCLUDE := $(shell python3-config --includes)
PYTHON_LDFLAGS := $(shell python3-config --ldflags)

# ===== SOURCE FILES =====
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# Object files for CLI (exclude python_bindings.cpp)
CLI_SRCS := $(filter-out $(SRC_DIR)/python_bindings.cpp,$(SRCS))
CLI_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CLI_SRCS))

# Object file for pybind11
PYBIND_SRC := $(SRC_DIR)/python_bindings.cpp
PYBIND_OBJ := $(BUILD_DIR)/python_bindings.o

# ===== RULES =====
all: cli pybind

# ---------------- CLI ----------------
cli: $(CLI_TARGET)

$(CLI_TARGET): $(CLI_OBJS) | $(BUILD_DIR)
	@echo "🔗 Linking CLI..."
	$(CXX) $(CLI_OBJS) -o $@ -lsqlite3
	@echo "✅ CLI build complete!"

# ---------------- Pybind11 ----------------
pybind: $(PYBIND_TARGET)

$(PYBIND_TARGET): $(CLI_OBJS) $(PYBIND_OBJ) | $(BUILD_DIR)
	@echo "🔗 Linking Python module..."
	$(CXX) -shared $(CLI_OBJS) $(PYBIND_OBJ) -o $@ $(PYTHON_LDFLAGS) -lsqlite3
	@echo "✅ Python module build complete!"

$(PYBIND_OBJ): $(PYBIND_SRC) | $(BUILD_DIR)
	@echo "🧩 Compiling Python bindings..."
	$(CXX) $(CXXFLAGS) $(PYTHON_INCLUDE) -c $< -o $@

# ---------------- General compile rule ----------------
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "🧩 Compiling $< ..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---------------- Build directory ----------------
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ---------------- Clean ----------------
clean:
	rm -rf $(BUILD_DIR) $(CLI_TARGET) $(PYBIND_TARGET)
	@echo "🧹 Clean done."

# ---------------- Run CLI ----------------
run: cli
	./$(CLI_TARGET)

.PHONY: all cli pybind clean run
