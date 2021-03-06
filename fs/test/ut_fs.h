#include <iostream>
#include "gtest/gtest.h"

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"
#include "../src/find_visitor.h"
#include "../src/info_content_visitor.h"
#include "../src/find_node_by_pathname_visitor.h"
#include "../src/node_builder.h"

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

TEST(FileSystemTest, FindVisitorReuse)
{
    Node* test_data = new Folder("./test_data");
    Node* hello_out = new File("./test_data/hello.out");
    test_data->add(hello_out);
    NodeVisitor* findVisitor = new FindVisitor("hello.out");
    test_data->accept(findVisitor);
    ASSERT_EQ("./hello.out", findVisitor->findResult());
    hello_out->accept(findVisitor);
    ASSERT_EQ("hello.out", findVisitor->findResult());
}

TEST(FileSystemTest, NodeBuilder)
{
    NodeBuilder nodeBuilder;
    nodeBuilder.build("test_data/hello.cpp");
    ASSERT_EQ(92, nodeBuilder.getRoot()->size());
    nodeBuilder.build("test_data/hello");
    ASSERT_EQ(14, nodeBuilder.getRoot()->size());
}

TEST(FindNodeByPathnameVisitor, Link)
{
    Node* hello = new Link("./test_data/hello");
    vector<string>* names = new vector<string>{std::string("hello")};
    FindNodeByPathnameVisitor* visitor = new FindNodeByPathnameVisitor(names);
    hello->accept(visitor);
    ASSERT_EQ(hello, visitor->getNode());
}

TEST(FindNodeByPathnameVisitor, LinkInFolder)
{
    Node* test_data = new Folder ("./test_data");
    Node* hello = new Link("./test_data/hello");
    test_data->add(hello);
    vector<string>* names = new vector<string>{string("test_data"), string("hello")};
    FindNodeByPathnameVisitor* visitor = new FindNodeByPathnameVisitor(names);
    test_data->accept(visitor);
    ASSERT_EQ(hello, visitor->getNode());
}

TEST(FindNodeByPathnameVisitor, NonExistingFileInFileSystem)
{
    Node* test_data = new Folder("./test_data");
    vector<string>* names = new vector<string>{string("test_data"), string("helloWorld")};
    FindNodeByPathnameVisitor* visitor = new FindNodeByPathnameVisitor(names);
    test_data->accept(visitor);
    ASSERT_EQ(nullptr, visitor->getNode());
}
