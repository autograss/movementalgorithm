#ifndef NODE_HPP
#include <cstddef>

class Node
{
public:
  Node(int value, Node *prev = NULL, Node *next = NULL);

  int value;
  Node *prev;
  Node *next;
};

#endif
