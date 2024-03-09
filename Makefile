SHELL := /bin/bash
SOURCES = src/*.cc src/waveview/*.cc src/envtools/*.cc 
GCC_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system


all:
	mkdir -p build
	rm -rf build/*
	cp -r buildsource/* build/
	
	g++  -g -o build/dftex $(SOURCES) $(GCC_FLAGS)


clean:
	rm -rf build/*
