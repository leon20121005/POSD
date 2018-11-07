#include <iostream>
#include "gtest/gtest.h"

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/find_visitor.h"

using namespace std;

TEST(FileSystemTest, Name)
{
    Folder* test_data = new Folder("./test_data");
    ASSERT_EQ("test_data", test_data->name());
}

TEST(FileSystemTest, FindFileSelf)
{
    File* hello_cpp = new File("./test_data/hello.cpp");
    FindVisitor* findVisitor = new FindVisitor("hello.cpp");
    hello_cpp->accept(findVisitor);
    ASSERT_EQ("hello.cpp", findVisitor->findResult());
}

TEST(FileSystemTest, FindFolderSelf)
{
    Folder* test_data = new Folder("./test_data");
    FindVisitor* findVisitor = new FindVisitor("test_data");
    test_data->accept(findVisitor);
    ASSERT_EQ("", findVisitor->findResult());
}

TEST(FileSystemTest, FindOneLayerPath)
{
    Folder* test_data = new Folder("./test_data");
    File* hello_cpp = new File("./test_data/hello.cpp");
    test_data->add(hello_cpp);
    FindVisitor* findVisitor = new FindVisitor("hello.cpp");
    test_data->accept(findVisitor);
    ASSERT_EQ("./hello.cpp", findVisitor->findResult());
}

TEST(FileSystemTest, FindTwoLayersPath)
{
    Folder* test_data = new Folder("./test_data");
    Folder* folder = new Folder("./test_data/folder");
    File* hello_cpp = new File("./test_data/folder/hello.cpp");
    test_data->add(folder);
    folder->add(hello_cpp);
    FindVisitor* findVisitor = new FindVisitor("hello.cpp");
    test_data->accept(findVisitor);
    ASSERT_EQ("./folder/hello.cpp", findVisitor->findResult());
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
    FindVisitor* findVisitor = new FindVisitor("hello.cpp");
    test_data->accept(findVisitor);
    ASSERT_EQ("./folder/hello.cpp\n./hello.cpp", findVisitor->findResult());
}

TEST(FileSystemTest, FindNoPath)
{
    Folder* test_data = new Folder("./test_data");
    FindVisitor* findVisitor = new FindVisitor("hello.cpp");
    test_data->accept(findVisitor);
    ASSERT_EQ("", findVisitor->findResult());
}

TEST(FileSystemTest, FindNotSelf)
{
    File* hello_cpp = new File("./test_data/hello.cpp");
    FindVisitor* findVisitor = new FindVisitor("hello.out");
    hello_cpp->accept(findVisitor);
    ASSERT_EQ("", findVisitor->findResult());
}

TEST(FileSystemTest, FindFolderInFolder)
{
    Folder* test_data = new Folder("./test_data");
    Folder* folder = new Folder("./test_data/folder");
    test_data->add(folder);
    FindVisitor* findVisitor = new FindVisitor("folder");
    test_data->accept(findVisitor);
    ASSERT_EQ("./folder", findVisitor->findResult());
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
    FindVisitor* findVisitor = new FindVisitor("hello.cpp");
    test_data->accept(findVisitor);
    FindVisitor* findVisitor2 = new FindVisitor("hello.cpp");
    folder->accept(findVisitor2);
    ASSERT_EQ("./folder/hello.cpp", findVisitor->findResult());
    ASSERT_EQ("./hello.cpp", findVisitor2->findResult());
}
