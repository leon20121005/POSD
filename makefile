.PHONY: clean

hw2: test/ut_main.cpp test/ut_shape.cpp test/ut_sort.cpp src/shape.h src/circle.h src/rectangle.h src/triangle.h src/sort.h
	g++ test/ut_main.cpp -o hw2 -lgtest -lpthread

clean:
	rm hw2
