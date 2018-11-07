#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <sys/stat.h>
#include <map>
#include "node_visitor.h"

using namespace std;

class Node
{
    public:
        Node(const char* path):_path(path)
        {
            lstat(_path, &_st);
            vector<string>* splitResult = split(_path, "/");
            _nodeName = (*splitResult)[splitResult->size() - 1];
        }

        string name()
        {
            return _nodeName;
        }

        virtual void add(Node* node)
        {
            throw string("unable to add");
        }

        virtual string find(string nodeName) = 0;
        virtual void accept(NodeVisitor* nodeVisitor) = 0;

        static vector<string>* split(string s, string delimiter)
        {
            vector<string>* result = new vector<string>();
            for (int index = 0; index < s.size();)
            {
                result->push_back(s.substr(index, s.find(delimiter, index) - index));

                if (s.find(delimiter, index) == string::npos)
                {
                    break;
                }
                index = index + (s.find(delimiter, index) - index + delimiter.size());
            }
            return result;
        }
    private:
        const char* _path;
        struct stat _st;
        string _nodeName;
};

#endif
