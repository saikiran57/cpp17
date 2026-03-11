/**
 * @file narray.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-12
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief
 * N array data structure
 *
 */
class Node : public std::enable_shared_from_this<Node>
{
public:
    Node(std::string_view name) : value(name) {}

    std::shared_ptr<Node> add_child(std::string_view name)
    {
        auto child = std::make_shared<Node>(name);
        child->parent = shared_from_this();  // safe way to assign shared pointer to weak pointer
        children.push_back(child);
        return child;
    }

    void print()
    {
        if (auto p = parent.lock()) std::cout << p->value << "-->";
        for (auto& child : children)
        {
            std::cout << child->value << "-->";
            child->print();
        }
    }

    std::string value;
    std::weak_ptr<Node> parent;  // In order to avoid cyclic dependency we must use weak pointer
    std::vector<std::shared_ptr<Node>> children;
};

void print_tree_impl(const std::shared_ptr<Node>& node, const std::string& prefix, bool is_last)
{
    std::cout << prefix;

    if (!prefix.empty())
    {
        std::cout << (is_last ? "└── " : "├── ");
    }

    std::cout << node->value << "\n";

    // Prepare next indentation prefix
    std::string next_prefix = prefix + (is_last ? "    " : "│   ");

    for (size_t i = 0; i < node->children.size(); ++i)
    {
        print_tree_impl(node->children[i], next_prefix, i + 1 == node->children.size());
    }
}

// Main print function
void print_tree(const std::shared_ptr<Node>& root)
{
    print_tree_impl(root, "", true);
}

int main()
{
    auto root = std::make_shared<Node>(".");

    auto a = root->add_child("A");
    auto b = root->add_child("B");
    auto c = b->add_child("C");
    auto d = b->add_child("D");
    auto e = c->add_child("E");

    print_tree(root);
}