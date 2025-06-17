BUILD_DIR := build
EXECUTABLE := $(BUILD_DIR)/cplotlib

.PHONY: all install

all: install

test:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -D CMAKE_BUILD_TYPE=Release .. && $(MAKE) -j

install:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -D CMAKE_BUILD_TYPE=Release .. && sudo $(MAKE) -j install