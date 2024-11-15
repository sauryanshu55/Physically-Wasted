# Variables
BUILD_DIR = cmake/build

# Targets
all: configure build

configure:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ../..

build:
	cd $(BUILD_DIR) && make

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all
