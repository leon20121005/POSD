.PHONY: clean

all: clean dict bin/midterm2

bin/midterm2: test/ut_main.cpp test/ut_shape.cpp test/ut_set.cpp src/triangle.h src/element.h src/integer.h src/set.h
	g++ -std=c++11 $< -o $@ -lgtest -lpthread

dict:
	mkdir -p bin

clean:
	rm -f bin/*
