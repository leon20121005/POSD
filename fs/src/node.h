#ifndef NODE_H
#define NODE_H

#include <sys/stat.h>
#include <vector>
#include <string>
#include <map>
#include "node_visitor.h"

class Node
{
    public:
        Node(const char* path):_path(path)
        {
            lstat(_path, &_st);
            std::vector<std::string>* splitResult = split(_path, "/");
            _nodeName = (*splitResult)[splitResult->size() - 1];
        }

        std::string name()
        {
            return _nodeName;
        }

        int size() const
        {
            return _st.st_size;
        }

        virtual void add(Node* node)
        {
            throw std::string("unable to add");
        }

        virtual void accept(NodeVisitor* nodeVisitor) = 0;

        static std::vector<std::string>* split(std::string s, std::string delimiter)
        {
            std::vector<std::string>* result = new std::vector<std::string>();
            for (int index = 0; index < s.size();)
            {
                result->push_back(s.substr(index, s.find(delimiter, index) - index));

                if (s.find(delimiter, index) == std::string::npos)
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
        std::string _nodeName;
};

#endif
