.PHONY: clean

hw2: test/ut_shape.cpp src/shape.h src/circle.h src/rectangle.h src/triangle.h src/sort.h
	g++ test/ut_shape.cpp -o hw2 -lgtest -lpthread

clean:
	rm hw2
