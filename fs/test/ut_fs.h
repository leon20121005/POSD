#include <iostream>
#include "gtest/gtest.h"

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/find_visitor.h"

using namespace std;

TEST(FileSystemTest, Name)
{
    Node* test_data = new Folder("./test_data");
    ASSERT_EQ("test_data", test_data->name());
}

TEST(FileSystemTest, FindFileSelf)
{
    Node* hello_cpp = new File("./test_data/hello.cpp");
    NodeVisitor* findVisitor = new FindVisitor("hello.cpp");
    hello_cpp->accept(findVisitor);
    ASSERT_EQ("hello.cpp", findVisitor->findResult());
}

TEST(FileSystemTest, FindFolderSelf)
{
    Node* test_data = new Folder("./test_data");
    NodeVisitor* findVisitor = new FindVisitor("test_data");
    test_data->accept(findVisitor);
    ASSERT_EQ("", findVisitor->findResult());
}

TEST(FileSystemTest, FindOneLayerPath)
{
    Node* test_data = new Folder("./test_data");
    Node* hello_cpp = new File("./test_data/hello.cpp");
    test_data->add(hello_cpp);
    NodeVisitor* findVisitor = new FindVisitor("hello.cpp");
    test_data->accept(findVisitor);
    ASSERT_EQ("./hello.cpp", findVisitor->findResult());
}

TEST(FileSystemTest, FindTwoLayersPath)
{
    Node* test_data = new Folder("./test_data");
    Node* folder = new Folder("./test_data/folder");
    Node* hello_cpp = new File("./test_data/folder/hello.cpp");
    test_data->add(folder);
    folder->add(hello_cpp);
    NodeVisitor* findVisitor = new FindVisitor("hello.cpp");
    test_data->accept(findVisitor);
    ASSERT_EQ("./folder/hello.cpp", findVisitor->findResult());
}

TEST(FileSystemTest, FindMultiPath)
{
    Node* test_data = new Folder("./test_data");
    Node* hello_cpp = new File("./test_data/hello.cpp");
    Node* folder = new Folder("./test_data/folder");
    Node* hello_cpp2 = new File("./test_data/folder/hello.cpp");
    test_data->add(hello_cpp);
    test_data->add(folder);
    folder->add(hello_cpp2);
    NodeVisitor* findVisitor = new FindVisitor("hello.cpp");
    test_data->accept(findVisitor);
    ASSERT_EQ("./folder/hello.cpp\n./hello.cpp", findVisitor->findResult());
}

TEST(FileSystemTest, FindNoPath)
{
    Node* test_data = new Folder("./test_data");
    NodeVisitor* findVisitor = new FindVisitor("hello.cpp");
    test_data->accept(findVisitor);
    ASSERT_EQ("", findVisitor->findResult());
}

TEST(FileSystemTest, FindNotSelf)
{
    Node* hello_cpp = new File("./test_data/hello.cpp");
    NodeVisitor* findVisitor = new FindVisitor("hello.out");
    hello_cpp->accept(findVisitor);
    ASSERT_EQ("", findVisitor->findResult());
}

TEST(FileSystemTest, FindFolderInFolder)
{
    Node* test_data = new Folder("./test_data");
    Node* folder = new Folder("./test_data/folder");
    test_data->add(folder);
    NodeVisitor* findVisitor = new FindVisitor("folder");
    test_data->accept(findVisitor);
    ASSERT_EQ("./folder", findVisitor->findResult());
}

TEST(FileSystemTest, FindFileInComplicatedPath)
{
    Node* test_data = new Folder("./test_data");
    Node* folder = new Folder("./test_data/folder");
    Node* hello_out = new File("./test_data/hello.out");
    Node* hello_cpp = new File("./test_data/folder/hello.cpp");
    test_data->add(folder);
    test_data->add(hello_out);
    folder->add(hello_cpp);
    NodeVisitor* findVisitor = new FindVisitor("hello.cpp");
    test_data->accept(findVisitor);
    NodeVisitor* findVisitor2 = new FindVisitor("hello.cpp");
    folder->accept(findVisitor2);
    ASSERT_EQ("./folder/hello.cpp", findVisitor->findResult());
    ASSERT_EQ("./hello.cpp", findVisitor2->findResult());
}
