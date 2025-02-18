PROJECT_SOURCE_DIR := $(PWD)
PROJECT_BUILD_DIR := /tmp/rvstd/build
CMAKE_BUILD_TYPE := Release

all: configure build test

set-project-dir:
	$(eval PROJECT_SOURCE_DIR := $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST))))))

configure: set-project-dir
	cmake \
		-S $(PROJECT_SOURCE_DIR) \
		-B $(PROJECT_BUILD_DIR) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
		-DENABLE_TESTS=ON
	ln -sf $(PROJECT_BUILD_DIR)/compile_commands.json $(PROJECT_SOURCE_DIR)/compile_commands.json

build: configure
	cmake --build $(PROJECT_BUILD_DIR)

purge:
	rm -rf $(PROJECT_BUILD_DIR)
	$(MAKE) configure

test: build
	ctest --test-dir $(PROJECT_BUILD_DIR) --output-on-failure

install: build
	cmake --install $(PROJECT_BUILD_DIR)

local_install: build
	cmake --install $(PROJECT_BUILD_DIR) --prefix ~/.local

benchmark: configure build
	$(PROJECT_BUILD_DIR)/tests/rvstd_benchmarks

coverage:
	cmake \
		-S $(PROJECT_SOURCE_DIR) \
		-B $(PROJECT_BUILD_DIR) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_BUILD_TYPE=COVERAGE \
		-DBUILD_TESTING=ON
	ln -sf $(PROJECT_BUILD_DIR)/compile_commands.json $(PROJECT_SOURCE_DIR)/compile_commands.json
	cmake --build $(PROJECT_BUILD_DIR)
	ctest --test-dir $(PROJECT_BUILD_DIR)
	gcovr $(PROJECT_BUILD_DIR) -r $(WORKSPACE) -e $(PROJECT_SOURCE_DIR)/tests --print-summary

.PHONY: all configure build test benchmark coverage install local_install purge
