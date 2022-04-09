## use to set a specific default executable
#DEFAULT_EXE=bin/main

## location of cxxtest
CXXTEST_HOME=extern/cxxtest-4.4

## external libraries
EXTERN_INCLUDES=extern/box2d-2.4.1/include extern/box2d-2.4.1/src
EXTERN_SOURCES=extern/box2d-2.4.1/include extern/box2d-2.4.1/src
ifeq ($(OS),Windows_NT)
       EXTERN_CXXFLAGS=-Wno-error=strict-aliasing -Wno-error=maybe-uninitialized -Wno-error=unused-but-set-variable -Wno-error=class-memaccess
else
       EXTERN_CXXFLAGS=-Wno-error=unused-variable
endif

## various options for possible build configurations
## comment in one of the following sets or add your own

CXXFLAGS_BASE=
LDFLAGS_BASE=

## for gprof
#CXXFLAGS_BASE:=$(CXXFLAGS_BASE) -O2 -pg
#LDFLAGS_BASE:=$(LDFLAGS_BASE) -pg

## the following should not need to change

## generic options
CXXFLAGS_BASE:=$(CXXFLAGS_BASE) -std=c++17 -Wall -pedantic-errors -Iinclude -Isrc $(EXTERN_CXXFLAGS)
LDFLAGS_BASE:=$(LDFLAGS_BASE) -std=c++17

## platform-specific options
ifeq ($(OS),Windows_NT)
	CXXFLAGS_BASE:=$(CXXFLAGS_BASE) -I/mingw64/include/SDL2
	LDFLAGS_BASE:=$(LDFLAGS_BASE) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	DOXYGEN=doxygen
else ifeq ($(shell sh -c 'uname'),Darwin)
	CXXFLAGS_BASE:=$(CXXFLAGS_BASE) -F/Library/Frameworks -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers
	LDFLAGS_BASE:=$(LDFLAGS_BASE) -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf
	ifneq ($(wildcard /Applications/Doxygen.app/Contents/Resources/doxygen),)
		DOXYGEN=/Applications/Doxygen.app/Contents/Resources/doxygen
	else
		DOXYGEN=doxygen
	endif
else
	CXXFLAGS_BASE:=$(CXXFLAGS_BASE) $(shell sh -c 'sdl2-config --cflags')
	LDFLAGS_BASE:=$(LDFLAGS_BASE) $(shell sh -c 'sdl2-config --libs') -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	DOXYGEN=doxygen
endif

## base files
BASE_SOURCE_FILES=$(shell sh -c '/usr/bin/find src/base -name "*.cpp" 2>/dev/null')
BASE_HEADER_FILES=$(shell sh -c '/usr/bin/find include/base -name "*.cpp" 2>/dev/null')

## graverunner files
GRAVERUNNER_EXE_SRC_FILES=$(shell sh -c '/usr/bin/find src/graverunner -name "main*.cpp" 2>/dev/null')
GRAVERUNNER_SOURCE_FILES=$(filter-out $(GRAVERUNNER_EXE_SRC_FILES),$(shell sh -c '/usr/bin/find src/graverunner $(EXTERN_SOURCES) -name "*.cpp" 2>/dev/null'))
GRAVERUNNER_HEADER_FILES=$(shell sh -c '/usr/bin/find include/graverunner src/graverunner -name "*.hpp" 2>/dev/null')
GRAVERUNNER_SOURCE_FILES+=$(BASE_SOURCE_FILES)
GRAVERUNNER_HEADER_FILES+=$(BASE_INCLUDE_FILES)
GRAVERUNNER_OBJ_FILES_RELEASE=$(GRAVERUNNER_SOURCE_FILES:%.cpp=build/obj/%.o)
GRAVERUNNER_OBJ_FILES_DEBUG=$(GRAVERUNNER_SOURCE_FILES:%.cpp=build/obj/%_d.o)
GRAVERUNNER_EXECUTABLE_RELEASE=$(patsubst src/%.cpp,bin/%,$(GRAVERUNNER_EXE_SRC_FILES))
GRAVERUNNER_EXECUTABLES_DEBUG=$(patsubst src/%.cpp,bin/%_d,$(GRAVERUNNER_EXE_SRC_FILES))
DEFAULT_EXE=$(word 1,$(GRAVERUNNER_EXECUTABLE_RELEASE))
DEFAULT_EXE_DEBUG=$(word 1,$(GRAVERUNNER_EXECUTABLES_DEBUG))


## breakout files
BREAKOUT_EXE_SRC_FILES=$(shell sh -c '/usr/bin/find src/breakout -name "main*.cpp" 2>/dev/null')
BREAKOUT_SOURCE_FILES=$(filter-out $(BREAKOUT_EXE_SRC_FILES),$(shell sh -c '/usr/bin/find src/breakout $(EXTERN_SOURCES) -name "*.cpp" 2>/dev/null'))
BREAKOUT_HEADER_FILES=$(shell sh -c '/usr/bin/find include/breakout src/breakout -name "*.hpp" 2>/dev/null')
BREAKOUT_SOURCE_FILES+=$(BASE_SOURCE_FILES)
BREAKOUT_HEADER_FILES+=$(BASE_INCLUDE_FILES)
BREAKOUT_OBJ_FILES_RELEASE=$(BREAKOUT_SOURCE_FILES:%.cpp=build/obj/%.o)
BREAKOUT_OBJ_FILES_DEBUG=$(BREAKOUT_SOURCE_FILES:%.cpp=build/obj/%_d.o)
BREAKOUT_EXECUTABLE_RELEASE=$(patsubst src/%.cpp,bin/%,$(BREAKOUT_EXE_SRC_FILES))
BREAKOUT_EXECUTABLES_DEBUG=$(patsubst src/%.cpp,bin/%_d,$(BREAKOUT_EXE_SRC_FILES))
DEFAULT_EXE=$(word 1,$(BREAKOUT_EXECUTABLE_RELEASE))
DEFAULT_EXE_DEBUG=$(word 1,$(BREAKOUT_EXECUTABLES_DEBUG))

## editor files
EDITOR_EXE_SRC_FILES=$(shell sh -c '/usr/bin/find src/editor -name "main*.cpp" 2>/dev/null')
EDITOR_SOURCE_FILES=$(filter-out $(EDITOR_EXE_SRC_FILES) $(GRAVERUNNER_EXE_SRC_FILES) $(BREAKOUT_EXE_SRC_FILES),$(shell sh -c '/usr/bin/find src/editor src/graverunner $(EXTERN_SOURCES) -name "*.cpp" 2>/dev/null'))
EDITOR_HEADER_FILES=$(shell sh -c '/usr/bin/find include include/editor src/editor -name "*.hpp" 2>/dev/null')
EDITOR_SOURCE_FILES+=$(BASE_SOURCE_FILES)
EDITOR_HEADER_FILES+=$(BASE_INCLUDE_FILES)
EDITOR_OBJ_FILES_RELEASE=$(EDITOR_SOURCE_FILES:%.cpp=build/obj/%.o)
EDITOR_OBJ_FILES_DEBUG=$(EDITOR_SOURCE_FILES:%.cpp=build/obj/%_d.o)
EDITOR_EXECUTABLE_RELEASE=$(patsubst src/%.cpp,bin/%,$(EDITOR_EXE_SRC_FILES))
EDITOR_EXECUTABLES_DEBUG=$(patsubst src/%.cpp,bin/%_d,$(EDITOR_EXE_SRC_FILES))


## test files
CXXTEST_GEN=$(CXXTEST_HOME)/bin/cxxtestgen
CXXTEST_INCLUDE=$(CXXTEST_HOME)

TEST_FILES=$(shell sh -c '/usr/bin/find test -name "*.cxxtest.hpp"')
TEST_SOURCE_FILES=$(TEST_FILES:test/%.cxxtest.hpp=build/test/%.cxxtest.cpp) build/test/runner.cpp
TEST_GRAVERUNNER_OBJ_FILES_RELEASE=$(TEST_SOURCE_FILES:.cpp=.o)
TEST_GRAVERUNNER_OBJ_FILES_DEBUG=$(TEST_SOURCE_FILES:.cpp=_d.o)

CXXFLAGS_BASE:=$(CXXFLAGS_BASE) -I$(CXXTEST_INCLUDE) $(EXTERN_INCLUDES:%=-I%) -D_TEST

## for optimization
CXXFLAGS_RELEASE:=$(CXXFLAGS_BASE) -O2 -DNDEBUG
LDFLAGS_RELEASE:=$(LDFLAGS_BASE)

## for gdb or valgrind
CXXFLAGS_DEBUG:=$(CXXFLAGS_BASE) -Og -ggdb -fno-inline -fno-omit-frame-pointer -D_DEBUG
LDFLAGS_DEBUG:=$(LDFLAGS_BASE)



## rules

all: doc graverunner graverunner_d breakout breakout_d tests tests_d

everything: doc graverunner graverunner_d breakout breakout_d tests tests_d


doc: $(GRAVERUNNER_HEADER_FILES) $(GRAVERUNNER_SOURCE_FILES) Makefile
	$(DOXYGEN)


breakout: $(BREAKOUT_EXECUTABLE_RELEASE)

breakout_d: $(BREAKOUT_EXECUTABLES_DEBUG)


graverunner: $(GRAVERUNNER_EXECUTABLE_RELEASE)

graverunner_d: $(GRAVERUNNER_EXECUTABLES_DEBUG)

editor: $(EDITOR_EXECUTABLE_RELEASE)

editor_d: $(EDITOR_EXECUTABLES_DEBUG)

tests: bin/test

tests_d: bin/test_d



run: $(DEFAULT_EXE)
	$(DEFAULT_EXE)

run_d: $(DEFAULT_EXE_DEBUG)
	$(DEFAULT_EXE_DEBUG)

run-tests: bin/test
	bin/test

run-tests_d: bin/test_d
	bin/test_d



$(GRAVERUNNER_EXECUTABLE_RELEASE): bin/%: build/obj/src/%.o $(GRAVERUNNER_OBJ_FILES_RELEASE)
	mkdir -p $(dir $@)
	g++  $^ $(LDFLAGS_RELEASE) -o $@

$(GRAVERUNNER_EXECUTABLES_DEBUG): bin/%: build/obj/src/%.o $(GRAVERUNNER_OBJ_FILES_DEBUG)
	mkdir -p $(dir $@)
	g++  $^ $(LDFLAGS_DEBUG) -o $@

build/obj/%.o: %.cpp $(GRAVERUNNER_HEADER_FILES) Makefile
	mkdir -p $(dir $@)
	g++ -c $< $(CXXFLAGS_RELEASE) -o $@

build/obj/%_d.o: %.cpp $(GRAVERUNNER_HEADER_FILES) Makefile
	mkdir -p $(dir $@)
	g++ -c $< $(CXXFLAGS_DEBUG) -o $@


$(BREAKOUT_EXECUTABLE_RELEASE): bin/%: build/obj/src/%.o $(BREAKOUT_OBJ_FILES_RELEASE)
	mkdir -p $(dir $@)
	g++  $^ $(LDFLAGS_RELEASE) -o $@

$(BREAKOUT_EXECUTABLES_DEBUG): bin/%: build/obj/src/%.o $(BREAKOUT_OBJ_FILES_DEBUG)
	mkdir -p $(dir $@)
	g++  $^ $(LDFLAGS_DEBUG) -o $@

build/obj/%.o: %.cpp $(BREAKOUT_HEADER_FILES) Makefile
	mkdir -p $(dir $@)
	g++ -c $< $(CXXFLAGS_RELEASE) -o $@

build/obj/%_d.o: %.cpp $(BREAKOUT_HEADER_FILES) Makefile
	mkdir -p $(dir $@)
	g++ -c $< $(CXXFLAGS_DEBUG) -o $@



$(EDITOR_EXECUTABLE_RELEASE): bin/%: build/obj/src/%.o $(EDITOR_OBJ_FILES_RELEASE)
	mkdir -p $(dir $@)
	g++  $^ $(LDFLAGS_RELEASE) -o $@

$(EDITOR_EXECUTABLES_DEBUG): bin/%: build/obj/src/%.o $(EDITOR_OBJ_FILES_DEBUG)
	mkdir -p $(dir $@)
	g++  $^ $(LDFLAGS_DEBUG) -o $@

build/obj/%.o: %.cpp $(EDITOR_HEADER_FILES) Makefile
	mkdir -p $(dir $@)
	g++ -c $< $(CXXFLAGS_RELEASE) -o $@

build/obj/%_d.o: %.cpp $(EDITOR_HEADER_FILES) Makefile
	mkdir -p $(dir $@)
	g++ -c $< $(CXXFLAGS_DEBUG) -o $@

ifneq ($(wildcard $(CXXTEST_HOME)),)


bin/test: $(TEST_GRAVERUNNER_OBJ_FILES_RELEASE) $(GRAVERUNNER_OBJ_FILES_RELEASE)
	mkdir -p $(dir $@)
	g++  $^ $(LDFLAGS_RELEASE) -o $@

bin/test_d: $(TEST_GRAVERUNNER_OBJ_FILES_DEBUG) $(GRAVERUNNER_OBJ_FILES_DEBUG)
	mkdir -p $(dir $@)
	g++  $^ $(LDFLAGS_DEBUG) -o $@

build/test/%.o: build/test/%.cpp $(GRAVERUNNER_HEADER_FILES) Makefile
	mkdir -p $(dir $@)
	g++ -c $< $(CXXFLAGS_RELEASE) -o $@

build/test/%_d.o: build/test/%.cpp $(GRAVERUNNER_HEADER_FILES) Makefile
	mkdir -p $(dir $@)
	g++ -c $< $(CXXFLAGS_DEBUG) -o $@

.PRECIOUS: build/test/%.cxxtest.cpp
build/test/%.cxxtest.cpp: test/%.cxxtest.hpp
	mkdir -p $(dir $@)
	$(CXXTEST_GEN) --part --error-printer $< -o $@

build/test/runner.cpp:
	mkdir -p $(dir $@)
	$(CXXTEST_GEN) --root --error-printer -o $@

else

bin/test:
	@echo "Cannot find CxxTest to build tests."
	false

endif

clean:
	rm -rf bin/ build/ doc/ *.gcda *.gcno *.gcov gmon.out