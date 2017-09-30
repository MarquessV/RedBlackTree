#ifndef NODE_HPP
#define NODE_HPP

template <class T>
class node {
  private:
    node<T>* parent;      // Pointer to the parent of the node, null if no parent.
    node<T>* left;        // Pointer to the nodes left child.
    node<T>* right;       // Pointer to the nodes right child.
    bool isRed;           // Set to true to if the node is red and false if the node is black.
    T data;               // The data held by the node.

  public:
    node();                                               // Constructor for an empty node
    node(node<T>*, node<T>*, node<T>*, const T&);         // Constructor for a node with children and type
    node(node<T>*, node<T>*, node<T>*, bool, const T&);   // Constructor for a node with known color.
    bool toggleColor();                                   // Toggles color of node.
    T getData();                                          // Returns data in the node.
    bool isBlack();                                       // Returns true if the node is black.
};

template<class T>
node<T>::node() : parent(nullptr), left(nullptr), right(nullptr) {}

template<class T>
node<T>::node(node<T>* p, node<T>* l, node<T>* r, const T& d) : parent(p), left(l), right(r), data(d) {}

template<class T>
node<T>::node(node<T>* p, node<T>* l, node<T>* r, bool red, const T& d) : parent(p), left(l), right(r), isRed(red), data(d) {}

template<class T>
bool node<T>::toggleColor()
{
  return (isRed = !isRed);
}

template<class T>
T node<T>::getData()
{
  return data;
}

template<class T>
bool node<T>::isBlack()
{
  return !isRed;
}

#endif
