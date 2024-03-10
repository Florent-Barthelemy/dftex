SHELL := /bin/bash
SOURCES = src/*.cc src/waveview/*.cc src/envtools/*.cc 
GCC_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

STATIC_CHECKER := cppcheck

all: check
	mkdir -p build
	rm -rf build/*
	cp -r buildsource/* build/
	
	g++  -g -o build/dftex $(SOURCES) $(GCC_FLAGS)

.PHONY : check
check:
	mkdir -p cppcheck
	cppcheck --template vs --cppcheck-build-dir=cppcheck --enable=all --inconclusive src/

clean:
	rm -rf build/*
