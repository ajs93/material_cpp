EXAMPLES := array \
						vector \
						deque \
						list \
						map

OUTPUT_DIR := $(CURDIR)/output

all: build

.PHONY: build

build: | $(OUTPUT_DIR)
	@for e in $(EXAMPLES); do \
		echo "Building $$e..."; \
		$(MAKE) -C $$e clean; \
		$(MAKE) -C $$e build OUTPUT_DIR=$(OUTPUT_DIR); \
		echo "Built!"; \
	done

$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

.PHONY: clean

clean:
	@for e in $(EXAMPLES); do \
		$(MAKE) -C $$e clean; \
	done
	rm -rf $(OUTPUT_DIR)
	@echo -e "Cleaned"