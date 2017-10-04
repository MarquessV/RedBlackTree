#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "node.hpp"
#include <vector>

#include <iostream>

using namespace std;

template <class T>
class red_black_tree {
  public:
    node<T>* root;
    unsigned int sze;
    red_black_tree();
    red_black_tree(T&);
    red_black_tree(vector<T>&);

    unsigned int size();

    node<T>* parent(node<T>*);
    node<T>* grandparent(node<T>*);
    node<T>* uncle(node<T>*);

    node<T>* find(T&);
    void rotate_left(node<T>*);
    void rotate_right(node<T>*);
    node<T>* insert_repair_tree(node<T>*);
    node<T>* insert(T&);
    bool remove(T&);
};

template<class T>
red_black_tree<T>::red_black_tree() : root(nullptr), sze(0) {}

template<class T>
red_black_tree<T>::red_black_tree(T& d)
{
  root = new node<T>*(d);
  sze = 1; 
}

template<class T>
red_black_tree<T>::red_black_tree(vector<T>& data)
{
  root = nullptr;
  sze = 0;
  for(T d : data) {
    insert(d);
  }
}

template<class T>
unsigned int red_black_tree<T>::size()
{
  return sze;
}

template<class T>
node<T>* red_black_tree<T>::parent(node<T>* child)
{
  if(child) {
    return child->parent;
  }
  return nullptr;
}

template<class T>
node<T>* red_black_tree<T>::grandparent(node<T>* child)
{
  if(child && child->parent) {
    return child->parent->parent;
  }
  return nullptr;
}

template<class T>
node<T>* red_black_tree<T>::uncle(node<T>* child)
{
  node<T>* gp = grandparent(child);
  if(gp) {
    if(gp->left == parent(child)) {
      return gp->right;
    }
    return gp->left;
  }
  return nullptr;
}

template<class T>
node<T>* red_black_tree<T>::find(T& target)
{
  node<T>* curr = root;
  while(curr != nullptr && curr->data != target) {
    if(target > curr->data) {
      curr = curr->right;
    }
    else {
      curr = curr->left;
    }
  }
  return curr;
}

template<class T>
void red_black_tree<T>::rotate_left(node<T>* n)
{
  node<T>* newnode = n->right;
  n->right = newnode->left;
  newnode->left = n;
  newnode->parent = n->parent;
  n->parent = newnode;
}

template<class T>
void red_black_tree<T>::rotate_right(node<T>* n)
{
  node<T>* newnode = n->left;
  n->left = newnode->right;
  newnode->right = n;
  newnode->parent = n->parent;
  n->parent = newnode;
}

template<class T>
node<T>* red_black_tree<T>::insert_repair_tree(node<T>* n)
{
  node<T>* p = parent(n);
  //case1: n is root, it must be black.
  if(!p) {
    n->isRed = false;
    root = n;
    return n;
  }
  //case2: parent is black - nothing needs to be done.
  if(p->isBlack()) {
    return n;
  }
  node<T>* u = uncle(n);
  node<T>* gp = n->parent->parent;
  //case3: parent is red, uncle doesn't exist
  if(p->isRed && (!u || u->isBlack())) {
    if(p == gp->left) {
      if(n == p->left) {
        p->parent = gp->parent;
        p->right = gp;
        if(gp->parent) {
          if(gp->parent->left == gp) {
            gp->parent->left = p;
          }
          else {
            gp->parent->right = p;
          }
        }
        gp->parent = p;
        gp->left = nullptr;    
        p->isRed = false;
        gp->isRed = true;
        insert_repair_tree(p);
      }
      else {
        n->left = p;
        n->right = gp;
        n->parent = gp->parent;
        if(gp->parent) {
          if(gp->parent->left == gp) {
            gp->parent->left = p;
          }
          else {
            gp->parent->right = p;
          }
        }
        gp->parent = p->parent = n;
        gp->left = p->right = nullptr;
        gp->isRed = true;
        n->isRed = false;
        insert_repair_tree(n);
      }
    }
    else {
      if(n == p->left) {
        n->left = gp;
        p->parent = gp->parent;
        if(gp->parent) {
          if(gp->parent->left == gp) {
            gp->parent->left = p;
          }
          else {
            gp->parent->right = p;
          }
        }
        gp->parent = n;
        gp->right = nullptr;
        p->isRed = false;
        gp->isRed = true;
        insert_repair_tree(gp);
      }
      else {
        p->left = gp;
        p->parent = gp->parent;
        if(gp->parent) {
          if(gp->parent->left == gp) {
            gp->parent->left = p;
          }
          else {
            gp->parent->right = p;
          }
        }
        gp->parent = p;
        gp->right = nullptr;
        p->isRed = false;
        gp->isRed = true;
        insert_repair_tree(p);
      }
    }
    return n;
  }
  //case4: parent is red, uncle is black
  if(false) {
    if(n == gp->left->right) {
      rotate_left(p);
      n = n->left;
    }
    else if(n == gp->right->left) {
      rotate_right(p);
      n = n->right;
    }
    if(n == p->left) {
      rotate_right(gp);
    }
    else {
      rotate_left(gp);
    }
    p->isRed = false;
    gp->isRed = true;
  } 
  //case5: parent is red, uncle is red
  else {
    p->isRed = false;
    u->isRed = false;
    gp->isRed = true;
    insert_repair_tree(gp); 
    return n;
  }
}


template<class T>
node<T>* red_black_tree<T>::insert(T& data)
{
  if(!root) {
    sze++;
    return (root = new node<T>(data));
  } 
  node<T>* curr = root;
  node<T>* pred = root;
  bool wentRight;
  while(curr) {
    if(data == curr->data) {
      return curr;
    }
    pred = curr;
    if(data > curr->data) {
      curr = curr->right;
      wentRight = true;
    }
    else {
      curr = curr->left;
      wentRight = false;
    }
  }
  curr = new node<T>(pred, data);
  if(wentRight) {
    pred->right = curr;
  }
  else {
    pred->left = curr;
  }
  insert_repair_tree(curr);
  sze++;
  return curr;
}

template<class T>
bool red_black_tree<T>::remove(T& target)
{
  //TODO
  return true;
}


#endif
