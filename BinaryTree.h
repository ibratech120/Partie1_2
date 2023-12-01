#pragma once
#include <vector>
#include <stdexcept>

template <typename T>
class BinaryTree
{
private:
    int _depth;
    std::vector<std::vector<T> > _tree;

public:
    BinaryTree() : _depth(0)
    {}

    void setDepth(int depth)
    {
        _depth = depth;
        _tree.resize(_depth + 1);
        for (int i = 0; i <= _depth; ++i)
        {
            _tree[i].resize(i + 1);
        }
    }


    void setNode(int n, int i, T value)
    {
        if (n <= _depth && i <= n)
        {
            _tree[n][i] = value;
        }
        else
        {
            std::cerr << "Error: Invalid indices (n=" << n << ", i=" << i << "). Tree not modified." << std::endl;
        }
    }

    T getNode(int n, int i) const
    {
        return _tree[n][i];
    }

    void display() const
    {
        for (int i = 0; i <= _depth; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                std::cout << getNode(i, j) << " ";
            }
            std::cout << std::endl;
        }
        displayTree();
        std::cout << std::endl << "      " << std::endl;
    }


    void displayTree() const
    {
        for (int i = 0; i <= _depth; ++i)
        {
            for (int k = 0; k < _depth - i; ++k)
            {
                std::cout << "  ";
            }
            for (int j = 0; j <= i; ++j)
            {
                std::cout << getNode(i, j);
                if (j < i) std::cout << "   ";
            }
            std::cout << std::endl;
        }
    }

};
