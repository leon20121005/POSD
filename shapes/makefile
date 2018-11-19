.PHONY: clean

bin/hw3: test/ut_main.cpp test/ut_shape.cpp test/ut_sort.cpp src/shape.h src/circle.h src/rectangle.h src/triangle.h src/sort.h src/main.cpp
	g++ -std=c++11 src/main.cpp -o bin/hw3

clean:
ifeq (${OS}, Windows_NT)
	rm bin/hw3.exe
else
	rm bin/hw3
endif
