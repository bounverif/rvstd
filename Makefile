WORKSPACE = $(PWD)
BUILD_DIRECTORY = /tmp/rvstd/build

all: configure build test

configure:
	cmake \
		-S $(WORKSPACE) \
		-B $(BUILD_DIRECTORY) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_BUILD_TYPE=RELEASE \
		-DENABLE_TESTS=ON
	ln -sf $(BUILD_DIRECTORY)/compile_commands.json $(WORKSPACE)/compile_commands.json

build: configure
	cmake --build $(BUILD_DIRECTORY)

purge:
	rm -rf $(BUILD_DIRECTORY)
	$(MAKE) configure

test: build
	ctest --test-dir $(BUILD_DIRECTORY) --output-on-failure

install: build
	cmake --install $(BUILD_DIRECTORY)

benchmark: configure build
	$(BUILD_DIRECTORY)/tests/rvstd_benchmarks

coverage:
	cmake \
		-S $(WORKSPACE) \
		-B $(BUILD_DIRECTORY) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_BUILD_TYPE=COVERAGE \
		-DENABLE_TESTS=ON
	ln -sf $(BUILD_DIRECTORY)/compile_commands.json $(WORKSPACE)/compile_commands.json
	cmake --build $(BUILD_DIRECTORY)
	ctest --test-dir $(BUILD_DIRECTORY)
	gcovr $(BUILD_DIRECTORY) -r $(WORKSPACE) -e $(WORKSPACE)/tests --print-summary

.PHONY: all configure build test benchmark coverage
