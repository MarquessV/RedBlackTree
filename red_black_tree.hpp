/**
 *  red_black_tree.hpp
 *  An implementation of a red black tree.
 *
 *  @author Marquess Valdez
 *  @version 1.0
 */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <cstddef> //for std::size_t
#include <vector>

using namespace std;

template <typename T>
class red_black_tree {
  private:
    class red_black_tree_node {
      public:
        T data;
        enum Color {red = 0, black = 1}; 
        Color color;
        red_black_tree_node *parent;
        red_black_tree_node *left;
        red_black_tree_node *right;

        // Default constructor
        red_black_tree_node() : color(red), parent(nullptr), left(nullptr), right(nullptr) {};
        // Construct a node with data, black by default since if a parent isn't known this will probably be used for the root.
        red_black_tree_node(const T& d) : data(d), color(red), parent(nullptr), left(nullptr), right(nullptr) {}
        // Construct a node with data and parent, red by default since this will probably be used for an insertion not at the root.
        red_black_tree_node(const T& d, red_black_tree_node *p) : data(d), color(red), parent(p), left(nullptr), right(nullptr) {};
        // Construct a node where everything is known.
        red_black_tree_node(const T& d, Color c, red_black_tree_node *p, red_black_tree_node *l, red_black_tree_node *r) : data(d), color(red), parent(p), left(l), right(r) {};

        inline T getData()
        {
          return this->data;
        }

        inline bool isBlack()
        {
          return this->color == black;
        }

        inline bool isRed()
        {
          return this->color == red;
        }

        inline void setBlack()
        {
          this->color = black;
        }

        inline void setRed()
        {
          this->color = red;
        }

        inline red_black_tree_node* getParent()
        {
          return this->parent;
        }

        inline red_black_tree_node* getSibling()
        {
          red_black_tree_node* p = this->getParent();
          if(p) {
            if(p->left == this) {
              return p->right;
            }
            return p->left;
          }
          return nullptr;
        }

        inline red_black_tree_node* getGrandparent()
        {
          if(this->parent) {
            return this->parent->parent;
          }
          return nullptr;
        }

        inline red_black_tree_node* getUncle()
        {
          red_black_tree_node* gp = this->getGrandparent();
          if(gp) {
            if(gp->left == this->parent) {
              return gp->right;
            }
            return gp->left;
          }
          return nullptr;
        }

        inline void rotateLeft()
        {
          if(this->right) {
            red_black_tree_node* nn = this->right;
            if(this->parent) {
              if(this->parent->left == this) {
                this->parent->left = nn; 
              } else {
                this->parent->right = nn;
              }
            }
            nn->parent = this->parent;
            this->parent = nn;
            this->right = nn->left;
            nn->left = this;
            if(this->right) {
              this->right->parent = this;
            }
          }
        }

        inline void rotateRight()
        {
          if(this->left) {
            red_black_tree_node* nn = this->left;
            if(this->parent) {
              if(this->parent->right == this) {
                this->parent->right = nn;
              } else {
                this->parent->left = nn;
              }
            }
            nn->parent = this->parent;
            this->parent = nn;
            this->left = nn->right;
            nn->right = this;
            if(this->left) {
              this->left->parent = this;
            }
          }
        }
       
        ~red_black_tree_node()
        {
          if(this->left) {
            delete this->left;
          }
          if(this->right) {
            delete this->right;
          }
          delete this;
        }
    };
    
    red_black_tree_node *root;
    size_t _size;

  public:
    red_black_tree() : root(nullptr), _size(0) {}

    red_black_tree(vector<T>& data)
    {
      root = nullptr;
      _size = 0;
      for(T d : data) {
        insert(d);
      } 
    }

    /**
     *  Inserts a single piece of data into the tree.
     *  @param d the data to insert. 
     *  @returns true if new node was created and inserted and 
     *  false if a node with the data already existed in tree.
     */
    bool insert(const T& d)
    {
      // First we find the position of the node.
      red_black_tree_node *node = root, *parent = nullptr;
      bool lastLeft;
      while(node) {
        parent = node;
        if(node->data == d) { // A node with the data already exists.
          return false;       // So we return false;
        } else if(node->data > d) {
          node = node->left;
          lastLeft = true;
        } else {
          node = node->right; 
          lastLeft = false;
        }
      }
      // Then we create the node.
      node = new red_black_tree_node(d, parent);
      _size++;
      if(parent && lastLeft) { // And set the children properly. Notice, we check for existence of the parent, in case
        parent->left = node;   // this node is the root node.
      }
      else if(parent) {
        parent->right = node;
      }
      insert_repair(node);    // Repair balance to the tree.
      return true;
    }

    void insert_repair(red_black_tree_node* node)
    {
      red_black_tree_node *parent = node->getParent();
      // Case 1: node is the root node, it must be set to black.
      if(!parent) {
        node->setBlack();
        root = node;
        return;
      }
      // Case 2: The parent of node is black, theres nothing to be done.
      if(parent->isBlack()) {
        return;
      }
      red_black_tree_node *grandparent = node->getGrandparent(), *uncle = node->getUncle();
      // Case 3: The parent is red and the uncle is black
      if(!uncle || uncle->isBlack()) {
        // Goal: Rotate parent into grandparent position
        // Part 1: If node is on the "inside" of the tree, we need to rotate it to the outside first.
        if(grandparent->left && node == grandparent->left->right) {
          parent->rotateLeft();
          node = node->right;
        } else if(grandparent->right && node == grandparent->right->left) {
          parent->rotateRight(); 
          node = node->left;
        }
        // Part 2: Now we can rotate the parent into place by rotating in the correct direction.
        if(node == parent->left) {
          grandparent->rotateRight(); // Parent is the left child of grandparent, so we rotate the grandparent right.
        } else {
          grandparent->rotateLeft();  // Parent is the right child of grandparent, so we rotate the grandparent left.
        }
        // Finally, we make the parent and grandparent the appropriate colors and return true.
        parent->setBlack();
        grandparent->setRed();
        if(grandparent == root) {
          root = parent;
        }
        return;
      }
      //Case 4: The parent and uncle are both red
      parent->setBlack();
      uncle->setBlack();
      grandparent->setRed();
    }

    /**
     *  Removes a single piece of data from the tree.
     *  @param d the data to remove.
     *  @returns true if the node with data was removed and false if a node with
     *  data didn't exist in the tree.
     */
    bool remove(const T& d)
    {
      //TODO
      return true;   
    }

    /**
     *  Checks if data is in the tree.
     *  @param d the data to find.
     *  @returns true if node with data was found and false otherwise.
     */
    inline bool find(const T& d)
    {
      red_black_tree_node* curr = root;
      while(curr) {
        if(curr->data == d) {
          return true;
        }
        if(curr->data > d) {
          curr = curr->left;
        }
        else {
          curr = curr->right;
        }
      }
      return false;
    }

    inline size_t size()
    {
      return _size;
    }

    ~red_black_tree() {
    }

};

#endif
