BUILD_DIR = cmake/build
BIN_DIR = bin/
LIB_DIR = lib/

all: configure build test

configure:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ../..

build:
	cd $(BUILD_DIR) && make -j$(nproc)

test:
	cd $(BUILD_DIR)/tests/ && ctest

clean:
	rm -rf $(BUILD_DIR) ${BIN_DIR} ${LIB_DIR}

rebuild: clean all

