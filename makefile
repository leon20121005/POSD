.PHONY: clean

hw1: ut_shape.cpp circle.h rectangle.h triangle.h
	g++ ut_shape.cpp -o hw1 -lgtest -lpthread

clean:
	rm hw1
