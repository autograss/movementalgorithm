#include <iostream>
#include "node.hpp"

int main()
{
  Node *node = new Node(10);

  std::cout << "Ok!" << std::endl;

  delete node;
  return 0;
}
