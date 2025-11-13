# ===== CONFIG =====
CXX := g++
CXXFLAGS := -O3 -Wall -std=c++17 -Iinclude -fPIC
SRC_DIR := src
BUILD_DIR := build
CLI_TARGET := english_cli

# ===== SOURCE FILES =====
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
CLI_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# ===== RULES =====
all: cli

# ---------------- CLI ----------------
cli: $(CLI_TARGET)

$(CLI_TARGET): $(CLI_OBJS) | $(BUILD_DIR)
	@echo "🔗 Linking CLI..."
	$(CXX) $(CLI_OBJS) -o $@ -lsqlite3
	@echo "✅ CLI build complete!"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "🧩 Compiling $< ..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ---------------- Backend ----------------
backend-deps:
	@echo "📦 Installing Python backend dependencies..."
	cd backend && pip install -r requirements.txt

backend: backend-deps
	@echo "🚀 Starting FastAPI backend..."
	cd backend && python main.py

# ---------------- Frontend ----------------
frontend-deps:
	@echo "📦 Installing frontend dependencies..."
	cd frontend && npm install --legacy-peer-deps

frontend-dev: frontend-deps
	@echo "🚀 Starting React frontend..."
	cd frontend && npm run dev

# ---------------- Full Stack ----------------
dev: backend frontend-dev

# ---------------- Database ----------------
init-db:
	@echo "🗃️ Initializing database..."
	python backend/init_database.py

# ---------------- Clean ----------------
clean:
	rm -rf $(BUILD_DIR) $(CLI_TARGET) frontend/node_modules frontend/dist
	@echo "🧹 Clean done."

.PHONY: all cli clean backend frontend-dev dev init-db backend-deps frontend-deps