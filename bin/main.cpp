#include <iostream>
#include "libs/bst.h"

using namespace BinarySearchTree;

int main() {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    for (auto elem : bst) {
        std::cout << elem << ' ';
    }
    return 0;
}