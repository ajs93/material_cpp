SRCS := main.cpp
BUILD_DIR := objs
OUTPUT_DIR := output

CXX := g++
CXXFLAGS := 
LDFLAGS := -Wall

OUTPUT := $(OUTPUT_DIR)/array
SRC_OBJS := $(foreach obj, $(subst .cpp,.o,$(SRCS)), $(BUILD_DIR)/$(obj))

.PHONY: build

build: $(OUTPUT)

$(OUTPUT): $(SRC_OBJS) | $(OUTPUT_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(SRC_OBJS): $(SRCS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -c -o $@

$(OUTPUT_DIR) $(BUILD_DIR):
	@mkdir -p $@

.PHONY: clean

clean:
	@rm -rf $(BUILD_DIR) $(OUTPUT_DIR)