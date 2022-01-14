BINARY_NAME := servidor

SRCS := main.cpp \
				Servidor.cpp \
				ManejadorCliente.cpp

INCLUDE_DIRS := .
BUILD_DIR := objs
OUTPUT_DIR := output

CXX := g++
CXXFLAGS := -I $(INCLUDE_DIRS)
LDFLAGS := -Wall -lpthread

OUTPUT := $(OUTPUT_DIR)/$(BINARY_NAME)
#SRC_OBJS := $(foreach obj, $(subst .cpp,.o,$(SRCS)), $(BUILD_DIR)/$(obj))
SRC_OBJS := $(foreach obj, $(notdir $(subst .cpp,.o,$(SRCS))), $(BUILD_DIR)/$(obj))

all: build

.PHONY: build

build: $(OUTPUT)

$(OUTPUT): $(SRC_OBJS) | $(OUTPUT_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(SRC_OBJS): | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(notdir $(subst .o,.cpp,$@)) -c -o $@

$(OUTPUT_DIR) $(BUILD_DIR):
	@mkdir -p $@

.PHONY: clean

clean:
	@rm -rf $(BUILD_DIR) $(OUTPUT_DIR)