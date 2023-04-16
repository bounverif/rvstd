WORKSPACE = $(PWD)
BUILD_DIRECTORY = /tmp/$(basename $(notdir ${WORKSPACE}))/build

all: configure build test

configure:
	cmake \
		-S $(WORKSPACE) \
		-B $(BUILD_DIRECTORY) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_BUILD_TYPE=RELEASE \
		-DENABLE_TESTS=ON
	ln -sf $(BUILD_DIRECTORY)/compile_commands.json $(WORKSPACE)/compile_commands.json

build:
	cmake --build $(BUILD_DIRECTORY)

purge:
	rm -rf $(BUILD_DIRECTORY)
	$(MAKE) configure

test: build
	ctest --test-dir $(BUILD_DIRECTORY) --output-on-failure

benchmark: configure build
	$(BUILD_DIRECTORY)/tests/rvstd_benchmarks

cbuild:
	DOCKER_BUILDKIT=1 docker build . \
	--file .devcontainer/Dockerfile \
	--tag bounverif/rvstd:latest

crun:
	docker run -it --rm -v $(PWD):/workspaces/rvstd bounverif/rvstd:latest

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
