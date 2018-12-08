.PHONY: clean

all: clean dict obj/find_flattened_set_visitor.o bin/midterm2

bin/midterm2: test/ut_main.cpp test/ut_shape.cpp test/ut_set.cpp src/triangle.h src/element.h src/integer.h src/set.h src/element_iterator.h src/null_iterator.h obj/find_flattened_set_visitor.o
	g++ -std=c++11 obj/find_flattened_set_visitor.o $< -o $@ -lgtest -lpthread

obj/find_flattened_set_visitor.o: src/find_flattened_set_visitor.cpp src/find_flattened_set_visitor.h
	g++ -std=c++11 -c $< -o $@ -lpthread

dict:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*
