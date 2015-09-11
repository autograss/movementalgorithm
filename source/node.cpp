#include "node.hpp"

Node::Node(int value, Node *prev, Node *next)
  {
    this->value = value;
    this->prev = prev;
    this->next = next;
  }
