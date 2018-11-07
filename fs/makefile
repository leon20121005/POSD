.PHONY: clean

bin/hw5: test/ut_fs.cpp test/ut_fs.h src/file.h src/folder.h src/node.h src/node_visitor.h obj/find_visitor.o
ifeq ($(OS), Windows_NT)
	g++ obj/find_visitor.o $< -o $@ -lgtest
else
	g++ obj/find_visitor.o $< -o $@ -lgtest -lpthread
endif

obj/find_visitor.o: src/find_visitor.cpp src/find_visitor.h
ifeq ($(OS), Windows_NT)
	g++ -c $< -o $@ -lgtest
else
	g++ -c $< -o $@ -lgtest -lpthread
endif

clean:
	rm -f bin/*
	rm -f obj/*
