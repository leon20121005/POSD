#include "node.h"
#include "node_iterator.h"

class Folder: public Node
{
    public:
        friend class FindVisitor;

        class FolderIterator: public NodeIterator
        {
            public:
                FolderIterator(Folder* folder):_folder(folder)
                {
                }

                void first()
                {
                    _iter = _folder->_children.begin();
                }

                Node* currentItem()
                {
                    if (this->isDone())
                    {
                        throw std::string("no current item");
                    }
                    return _iter->second;
                }

                void next()
                {
                    if (this->isDone())
                    {
                        throw std::string("moving past the end");
                    }
                    _iter++;
                }

                bool isDone()
                {
                    return _iter == _folder->_children.end();
                }
            private:
                Folder* _folder;
                std::map<std::string, Node*>::iterator _iter;
        };

        Folder(const char* path):Node(path)
        {
        }

        void add(Node* node)
        {
            _children.insert(std::pair<std::string, Node*>(node->name(), node));
        }

        void accept(NodeVisitor* nodeVisitor)
        {
            nodeVisitor->visitFolder(this);
        }

        NodeIterator* createIterator()
        {
            return new FolderIterator(this);
        }
    private:
        std::map<std::string, Node*> _children;
};
