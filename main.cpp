#include <iostream>
#include "BinarySearchTree.h"

int main() {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(8);
    tree.insert(1);
    tree.insert(6);
    tree.print();
    BinarySearchTree<int> tree2;
    tree2.insert(6);
    tree2.insert(5);
    tree2.insert(3);
    tree2.insert(7);
    tree2.insert(2);
    tree2.insert(4);
    tree2.insert(8);
    tree2.insert(1);
    tree2.print();
    std::cout << tree.isSimilar(tree2) << '\n';
    tree.remove(2);
    tree.print();
    tree.remove(7);
    tree.print();
    tree.remove(5);
    tree.print();
    std::cout << tree.remove(100) << '\n';
    std::cout << tree.getHeight() << '\n';
    tree.inorderWalk();
    tree.inorderWalkIterative();
    std::cout << tree.getNumberOfNodes() << '\n';
    tree.walkByLevels();
    return 0;
}