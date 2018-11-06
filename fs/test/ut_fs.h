#include <iostream>
#include "gtest/gtest.h"

#include "../src/file.h"
#include "../src/folder.h"

using namespace std;

TEST(FileSystemTest, Name)
{
    Folder* test_data = new Folder("./test_data");
    ASSERT_EQ("test_data", test_data->name());
}

TEST(FileSystemTest, FindFileSelf)
{
    File* hello_cpp = new File("./test_data/hello.cpp");
    ASSERT_EQ("hello.cpp", hello_cpp->find("hello.cpp"));
}

TEST(FileSystemTest, FindFolderSelf)
{
    Folder* test_data = new Folder("./test_data");
    ASSERT_EQ("", test_data->find("test_data"));
}

TEST(FileSystemTest, FindOneLayerPath)
{
    Folder* test_data = new Folder("./test_data");
    File* hello_cpp = new File("./test_data/hello.cpp");
    test_data->add(hello_cpp);
    ASSERT_EQ("./hello.cpp", test_data->find("hello.cpp"));
}

TEST(FileSystemTest, FindTwoLayersPath)
{
    Folder* test_data = new Folder("./test_data");
    Folder* folder = new Folder("./test_data/folder");
    File* hello_cpp = new File("./test_data/folder/hello.cpp");
    test_data->add(folder);
    folder->add(hello_cpp);
    ASSERT_EQ("./folder/hello.cpp", test_data->find("hello.cpp"));
}

TEST(FileSystemTest, FindMultiPath)
{
    Folder* test_data = new Folder("./test_data");
    File* hello_cpp = new File("./test_data/hello.cpp");
    Folder* folder = new Folder("./test_data/folder");
    File* hello_cpp2 = new File("./test_data/folder/hello.cpp");
    test_data->add(hello_cpp);
    test_data->add(folder);
    folder->add(hello_cpp2);
    ASSERT_EQ("./folder/hello.cpp\n./hello.cpp", test_data->find("hello.cpp"));
}

TEST(FileSystemTest, FindNoPath)
{
    Folder* test_data = new Folder("./test_data");
    ASSERT_EQ("", test_data->find("hello.cpp"));
}

TEST(FileSystemTest, FindNotSelf)
{
    File* hello_cpp = new File("./test_data/hello.cpp");
    ASSERT_EQ("", hello_cpp->find("hello.out"));
}

TEST(FileSystemTest, FindFolderInFolder)
{
    Folder* test_data = new Folder("./test_data");
    Folder* folder = new Folder("./test_data/folder");
    test_data->add(folder);
    ASSERT_EQ("./folder", test_data->find("folder"));
}

TEST(FileSystemTest, FindFileInComplicatedPath)
{
    Folder* test_data = new Folder("./test_data");
    Folder* folder = new Folder("./test_data/folder");
    File* hello_out = new File("./test_data/hello.out");
    File* hello_cpp = new File("./test_data/folder/hello.cpp");
    test_data->add(folder);
    test_data->add(hello_out);
    folder->add(hello_cpp);
    ASSERT_EQ("./folder/hello.cpp", test_data->find("hello.cpp"));
    ASSERT_EQ("./hello.cpp", folder->find("hello.cpp"));
}
