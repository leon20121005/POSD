.PHONY: clean

bin/hw5: test/ut_fs.cpp test/ut_fs.h src/file.h src/folder.h src/node.h
ifeq ($(OS), Windows_NT)
	g++ $< -o $@ -lgtest
else
	g++ $< -o $@ -lgtest -lpthread
endif

clean:
	rm -f bin/*
